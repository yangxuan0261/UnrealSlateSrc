
#include "MySlate.h"
#include "EffectMgr.h"

#include "../Res/ResMgr.h"
#include "../Res/Infos/BehavInfo.h"
#include "./Effects/UBehavData.h"
#include "../MyChar.h"

static int32 gEffectUuid = 1;
static int32 IdGeneratorEffect()
{      
	return gEffectUuid++;
}

FEffectBind::FEffectBind()
{

}

FEffectBind::FEffectBind(UEffDataElem* _effData, int32 _lefTtime, int32 _uuId, UParticleSystemComponent* _psComp)
{
	mEffData = _effData;
	mLeftTimer = _lefTtime;
	mUuId = _uuId;
	mPsComp = _psComp;
	if (_effData != nullptr)
	{
		mDelayTimer = _effData->mDelayTime;
		mHasDelay = mDelayTimer > 0.f ? true : false;
	}
	else
	{
		UE_LOG(EffectLogger, Error, TEXT("--- FEffectBind::FEffectBind, _effData == nullptr"));
	}
}

//------------------------- UEffectMgr Begin -----------------------
UEffectMgr::UEffectMgr()
{

}

UEffectMgr::~UEffectMgr()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UEffectMgr::~UEffectMgr"));
}

void UEffectMgr::BeginDestroy()
{
	for (TMap<int32, UBehavData*>::TConstIterator iter = mBehavMap.CreateConstIterator(); iter; ++iter)
	{
		for (UEffDataElem* elem : iter->Value->mEffElemVec)
		{
			elem->RemoveFromRoot();
			elem->ConditionalBeginDestroy();
		}
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mBehavMap.Empty();

	UE_LOG(EffectLogger, Warning, TEXT("--- UEffectMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UEffectMgr::Tick(float DeltaTime)
{
	//特效剩余时间
	for (auto Iter = mEffectBindMap.CreateIterator(); Iter; ++Iter)
	{
		for (FEffectBind& effBind : Iter->Value)
		{
			effBind.mLeftTimer -= DeltaTime;

			//延时可见
			if (effBind.mHasDelay)
			{
				effBind.mDelayTimer -= DeltaTime;
				if (effBind.mDelayTimer < 0.f)
				{
					effBind.mPsComp->SetVisibility(true);
					effBind.mHasDelay = false;
				}
			}
		}
	}
}

bool UEffectMgr::IsTickable() const
{
	return true;
}

TStatId UEffectMgr::GetStatId() const
{
	return TStatId();
}

void UEffectMgr::loadBehavInfo()
{
	UDataTable* dataTab = UResMgr::GetInstance()->GetInfoTable(EInfoType::Behav);
	if (dataTab != nullptr)
	{
		//dataTab->FindRow
		FBehavInfo* tmpPtr = nullptr;
		for (auto Iter : dataTab->RowMap)
		{
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			tmpPtr = (FBehavInfo*)(Iter.Value);
			UBehavData* behav1 = NewObject<UBehavData>(UBehavData::StaticClass());
			behav1->mId = tmpPtr->mId;

			FEffElemInfo* elem = nullptr;
			for (int32 i = 0; i<tmpPtr->mEffectVec.Num(); ++i)
			{
				elem = &tmpPtr->mEffectVec[i];

				UEffDataElem* effElem = NewObject<UEffDataElem>(UEffDataElem::StaticClass());
				effElem->mResId = elem->mResId;
				effElem->mEffectType = elem->mEffectType;
				effElem->mBindPoint = elem->mBindPoint;
				effElem->mDelayTime = elem->mDelayTime;
				effElem->mLoc = elem->mLoc;
				effElem->mScale = elem->mScale;
				effElem->mRotate = elem->mRotate;

				effElem->AddToRoot();
				behav1->mEffElemVec.Add(effElem);
				UE_LOG(EffectLogger, Warning, TEXT("--- resId:%d, bindPoint:%s"), elem->mResId, *elem->mBindPoint);
			}

			behav1->AddToRoot();
			mBehavMap.Add(behav1->mId, behav1);
			UE_LOG(EffectLogger, Warning, TEXT("--- key:%d, effNum:%d"), tmpPtr->mId, tmpPtr->mEffectVec.Num());
		}
	}
}

UBehavData* UEffectMgr::GetBehav(int32 _key)
{
	UBehavData** behav = mBehavMap.Find(_key);
	return behav != nullptr ? *behav : nullptr;
}

//循环特效，相同特效id只存放时间最长的，_time < 0.f表示不是循环特效，不需要主动释放
TArray<int32> UEffectMgr::AttachBehavData(AMyChar* _target, int32 _behavDataId, float _time /* = -1.f */)
{
	TArray<int32> dstEffUuids;
	UBehavData* behavData = UEffectMgr::GetInstance()->GetBehav(_behavDataId);
	if (behavData == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::AttachBehavData, behavData == nullptr, id:%d"), _behavDataId);
		return TArray<int32>();
	}

	bool isOnce = _time > 0.f ? false : AttachBehavDataOnce(_target, behavData);
	if (isOnce)
	{
		return dstEffUuids;
	}

	TArray<UEffDataElem*>& elems = behavData->GetEffElems(); //表现数据中的特效集
	int targetId = _target->GetUuid();
	TArray<FEffectBind>* effs = mEffectBindMap.Find(targetId);
	if (effs != nullptr)
	{
		FEffectBind* dstEff = nullptr;
		UEffDataElem* ele = nullptr;
		int32 len = elems.Num();
		for (int32 i = 0; i < len; ++i)
		{
			ele = elems[i];

			//有绑定位置，且特效资源id相同，只为其续命，不spwan新的粒子组件
			FEffectBind* dstEff = effs->FindByPredicate([&](const FEffectBind& tmp)->bool {
				return tmp.mEffData->mResId == ele->mResId
					&& tmp.mEffData->mBindPoint.Len() > 0
					&& tmp.mEffData->mBindPoint == ele->mBindPoint;
			});

			bool needSpwan = true; //-1:之前不存在，
			if (dstEff != nullptr)
			{
				if (_time >= dstEff->mLeftTimer)
				{
					int32 newUuid = ::IdGeneratorEffect();
					dstEff->mUuId = newUuid; //换个新id，让老的找不到
					dstEff->mLeftTimer = _time; //续命
					dstEff->mDelayTimer = _time; //续命
					dstEffUuids.Add(newUuid);
				}

				needSpwan = false;
			}

			if (needSpwan)
			{
				CreateEffBind(_target, ele, _time, *effs, dstEffUuids);
			}
		}
	}
	else
	{
		TArray<FEffectBind> newBinds;
		for (UEffDataElem* ele : elems)
		{
			CreateEffBind(_target, ele, _time, newBinds, dstEffUuids);
		}

		mEffectBindMap.Add(targetId, newBinds);
	}

	return dstEffUuids;
}

//一次性特效
bool UEffectMgr::AttachBehavDataOnce(AMyChar* _target, UBehavData* _behavData)
{
	TArray<FEffectBind> tmpA;
	TArray<int32> tmpB;

	TArray<UEffDataElem*>& elems = _behavData->GetEffElems(); //表现数据中的特效集
	UEffDataElem* ele = nullptr;
	for (int32 i = 0; i < elems.Num(); ++i)
	{
		ele = elems[i];
		CreateEffBind(_target, ele, 0.f, tmpA, tmpB, false);
	}
	return true;
}

void UEffectMgr::CreateEffBind(AMyChar* _target, UEffDataElem* _ele, float _time, TArray<FEffectBind>& _bindArr, TArray<int32>& _dstUuids, bool _isDurable /* = true */)
{
	if (_ele == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::CreateEffBind, _ele == nullptr"));
		return;
	}

	UParticleSystem* ps = UResMgr::GetInstance()->GetParticle(_ele->mResId);
	UParticleSystemComponent* psComp = nullptr;

	psComp = ps != nullptr ?
		UGameplayStatics::SpawnEmitterAttached(ps
			, _target->GetMesh()
			, FName(*(_ele->mBindPoint))
			, _ele->mLoc
			, _ele->mRotate) : nullptr;

	if (ps != nullptr && psComp != nullptr)
	{
		if (_ele->mDelayTime > 0.f) //延时可见
		{
			psComp->SetVisibility(false);
		}
		else
		{
			psComp->SetVisibility(true);
		}

		psComp->SetRelativeScale3D(_ele->mScale);

		if (_isDurable)
		{
			int32 newUuid = ::IdGeneratorEffect();
			_dstUuids.Add(newUuid);

			//TODO 遍历中增加可能有问题，待验证
			_bindArr.Add(FEffectBind(_ele, _time, newUuid, psComp));
		}
	}
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::AttachBehavData, eff == null, resId:%d"), _ele->mResId);
	}
}

void UEffectMgr::DetachEffect(int32 _targetId, const TArray<int32>& _effuuids)
{
	if (_effuuids.Num() == 0)
	{
		return;
	}

	TArray<FEffectBind>* effBinds = mEffectBindMap.Find(_targetId);
	if (effBinds != nullptr)
	{
		FEffectBind* findEff = nullptr;
		for (int32 delId : _effuuids)
		{
			findEff = effBinds->FindByPredicate([&](const FEffectBind& tmp)->bool {
				return tmp.mUuId == delId;
			});

			if (findEff != nullptr)
			{
				FEffectBind tmp = *findEff;
				tmp.mPsComp->DetachFromParent();
				tmp.mPsComp->DestroyComponent();
				effBinds->Remove(tmp);
				UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::DetachEffect, effectId:%d"), tmp.mEffData->mResId);

				if (effBinds->Num() == 0)
				{
					mEffectBindMap.Remove(_targetId);
				}
			}
		}
	}
}

TArray<int32> UEffectMgr::AttachBehavData2(AMyChar* _target, int32 _behavDataId, float _time /*= -1.f*/)
{
	TArray<int32> dstEffUuids;
	UBehavData* behavData = UEffectMgr::GetInstance()->GetBehav(_behavDataId);
	if (behavData == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::AttachBehavData, behavData == nullptr, id:%d"), _behavDataId);
		return TArray<int32>();
	}

	bool isOnce = _time > 0.f ? false : AttachBehavDataOnce(_target, behavData);
	if (isOnce)
	{
		return dstEffUuids;
	}

	TArray<UEffDataElem*>& elems = behavData->GetEffElems(); //表现数据中的特效集
	int targetId = _target->GetUuid();
	TArray<FEffectBind>* effs = mEffectBindMap.Find(targetId);
	if (effs != nullptr)
	{
		FEffectBind* dstEff = nullptr;
		for (int32 i = 0; i < elems.Num(); ++i)
		{
			CreateEffBind(_target, elems[i], _time, *effs, dstEffUuids);
		}
	}
	else
	{
		TArray<FEffectBind> newBinds;
		for (UEffDataElem* ele : elems)
		{
			CreateEffBind(_target, ele, _time, newBinds, dstEffUuids);
		}

		mEffectBindMap.Add(targetId, newBinds);
	}

	return dstEffUuids;
}