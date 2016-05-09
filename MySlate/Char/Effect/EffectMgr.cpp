
#include "MySlate.h"
#include "EffectMgr.h"

#include "../Res/ResMgr.h"
#include "../Res/Infos/BehavInfo.h"
#include "./Effects/BehavData.h"
#include "./Effects/BehavElem.h"
#include "../MyChar.h"
#include "../MyBullet.h"

static int32 gEffectUuid = 1;
static int32 IdGeneratorEffect()
{      
	if (gEffectUuid == 65534)
	{
		gEffectUuid = 1;
	}

	return gEffectUuid++;
} 

static const int32 gSceneEffectId = (1 << 4) + 1;

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
			//延时可见
			if (effBind.mHasDelay)
			{
				effBind.mDelayTimer -= DeltaTime;
				if (effBind.mDelayTimer < 0.f)
				{
					effBind.mPsComp->CustomTimeDilation = 1.f;
					effBind.mPsComp->SetVisibility(true);
					effBind.mHasDelay = false;
				}
			}

			//总时长到了自动回收，为场景特效服务
			if (effBind.mHasTotal)
			{
				if (effBind.mTotalTimer < 0.f)
				{
					//TODO: 销毁场景特效

					effBind.mTotalTimer = false;

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
		FBehavInfo* tmpPtr = nullptr;
		for (auto Iter : dataTab->RowMap)
		{
			tmpPtr = (FBehavInfo*)(Iter.Value);
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			UBehavData* behav1 = NewObject<UBehavData>(UBehavData::StaticClass());
			behav1->mId = tmpPtr->mId;

			CopyEffInfoToData(tmpPtr->mAtkEffVec, behav1->mAtkEffVec);
			CopyEffInfoToData(tmpPtr->mBltEffVec, behav1->mBltEffVec);
			CopyEffInfoToData(tmpPtr->mTarEffVec, behav1->mTarEffVec);
			CopyEffInfoToData(tmpPtr->mSceEffVec, behav1->mSceEffVec);

			CopyShkInfoToData(tmpPtr->mAtkShkVec, behav1->mAtkShkVec);
			CopyShkInfoToData(tmpPtr->mBltShkVec, behav1->mBltShkVec);
			CopyShkInfoToData(tmpPtr->mTarShkVec, behav1->mTarShkVec);
			CopyShkInfoToData(tmpPtr->mSceShkVec, behav1->mSceShkVec);


			behav1->AddToRoot();
			mBehavMap.Add(behav1->mId, behav1);
			UE_LOG(EffectLogger, Warning, TEXT("--- UBehavData load over, key:%d"), tmpPtr->mId);
		}
	}
}

void UEffectMgr::CopyEffInfoToData(TArray<FEffElemInfo>& _info, TArray<UEffDataElem*>& _dstVec)
{
	FEffElemInfo* elem = nullptr;
	UEffDataElem* effElem = nullptr;
	for (int32 i = 0; i < _info.Num(); ++i)
	{
		elem = &_info[i];

		effElem = NewObject<UEffDataElem>(UEffDataElem::StaticClass());
		effElem->mResId = elem->mResId;
		effElem->mOwnType = elem->mOwnType;
		effElem->mFollowType = elem->mFollowType;
		effElem->mBindPoint = elem->mBindPoint;
		effElem->mDelayTime = elem->mDelayTime;
		effElem->mLoc = elem->mLoc;
		effElem->mScale = elem->mScale;
		effElem->mRotate = elem->mRotate;

		effElem->AddToRoot();
		_dstVec.Add(effElem);
		UE_LOG(EffectLogger, Warning, TEXT("--- resId:%d, bindPoint:%s"), elem->mResId, *elem->mBindPoint);
	}
}

void UEffectMgr::CopyShkInfoToData(TArray<FShakeInfo>& _info, TArray<UShakeElem*>& _dstVec)
{
	FShakeInfo* shakerElem = nullptr;
	UShakeElem* elem = nullptr;
	for (int32 i = 0; i < _info.Num(); ++i)
	{
		shakerElem = &_info[i];

		elem = NewObject<UShakeElem>(UShakeElem::StaticClass());
		elem->mA = shakerElem->mA;
		elem->mW = shakerElem->mW;
		elem->mTime = shakerElem->mTime;
		elem->mIsX = shakerElem->mIsX;
		elem->mOwnType = shakerElem->mOwnType;

		elem->AddToRoot();
		_dstVec.Add(elem);
		UE_LOG(EffectLogger, Warning, TEXT("--- shake, time:%f"), shakerElem->mTime);
	}
}

UBehavData* UEffectMgr::GetBehav(int32 _key)
{
	UBehavData** behav = mBehavMap.Find(_key);
	return behav != nullptr ? *behav : nullptr;
}

void UEffectMgr::AttachBehav(AMyChar* _tarChar, EOwnType _ownType, AMyBullet* _tarBullet, int32 _behavDataId)
{
	UBehavData* behavData = GetBehav(_behavDataId);
	if (behavData == nullptr)
	{
		UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehavData, behavData == nullptr, id:%d"), _behavDataId);
		return;
	}

	int32 groupId = ::IdGeneratorEffect(); //本次行为数据的识别id

	//------------- char
	if (_tarChar != nullptr)
	{
		TArray<UEffDataElem*> effectVec = _ownType == EOwnType::Self ? behavData->mAtkEffVec : behavData->mTarEffVec;
		TArray<UShakeElem*> shakeVec = _ownType == EOwnType::Self ? behavData->mAtkShkVec : behavData->mTarShkVec;
		//StrArr.Append(Arr, ARRAY_COUNT(Arr));
		for (UEffDataElem* effect : effectVec)
		{
			UParticleSystem* ps = UResMgr::GetInstance()->GetParticle(effect->mResId);
			if (ps == nullptr )
			{
				UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehavData, ps == nullptr, resId:%d"), effect->mResId);
				continue;
			}

			effect = effect->Clone();
			effect->mGroupId = groupId;
			UParticleSystemComponent* psComp = nullptr;
			if (effect->mFollowType == EFollowType::Follow) //跟随char
			{
				USceneComponent* dstComp = nullptr;
				if (effect->mBindPoint.Len() > 0) //绑定骨骼
				{
					dstComp = _tarChar->GetMesh();
				}
				else //没绑定骨骼则绑定char的capsule组件
				{
					dstComp = _tarChar->GetCapsuleComponent();
				}
				psComp = UGameplayStatics::SpawnEmitterAttached(ps
						, _tarChar->GetMesh()
						, FName(*(effect->mBindPoint))
						, effect->mLoc
						, effect->mRotate);
				if (psComp != nullptr)
				{
					psComp->SetRelativeScale3D(effect->mScale);
				}
			}
			else if (effect->mFollowType == EFollowType::UnFollow) //不跟随，相对char当前transform进行偏移，scale除外
			{
				FTransform srcTran = _tarChar->GetTransform();
				FTransform dstTran(effect->mRotate + srcTran.Rotator(), effect->mLoc + srcTran.GetTranslation(), effect->mScale);
				psComp = UGameplayStatics::SpawnEmitterAtLocation(
						GWorld
						, ps
						, dstTran);
			}
			else
			{
				UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehav, mFollowType == %d"), (int32)effect->mFollowType);
			}

			if (psComp != nullptr)
			{
				effect->SetActor(_tarChar);
				effect->SetData(psComp);
				effect->Start();
			}
		}

		for (UShakeElem* shake: shakeVec)
		{
			shake = shake->Clone();
			shake->mGroupId = groupId;
			shake->SetActor(_tarChar);
			shake->Start();
		}
	}

	//------------- bullet
	if (_tarBullet != nullptr)
	{
		TArray<UEffDataElem*> effectVec = behavData->mBltEffVec;
		TArray<UShakeElem*> shakeVec = behavData->mBltShkVec;

		for (UEffDataElem* effect : effectVec)
		{
			if (effect->mFollowType == EFollowType::UnFollow) //子弹特效一般都是跟随
			{
				UParticleSystem* ps = UResMgr::GetInstance()->GetParticle(effect->mResId);
				if (ps == nullptr)
				{
					UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehavData, ps == nullptr, resId:%d"), effect->mResId);
					continue;
				}

				 UParticleSystemComponent* psComp = UGameplayStatics::SpawnEmitterAttached(ps
						, _tarBullet->GetRootComponent() //绑道子弹根组件
						, FName(*(effect->mBindPoint))
						, effect->mLoc
						, effect->mRotate);
				if (psComp != nullptr)
				{
					effect = effect->Clone();
					effect->mGroupId = groupId;
					psComp->SetRelativeScale3D(effect->mScale);
					effect->SetActor(_tarChar);
					effect->SetData(psComp);
					effect->Start();
				}
			}
			else
			{
				UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehav, bullet mFollowType != EFollowType::UnFollow"));
			}
		}

		for (UShakeElem* shake : shakeVec)
		{
			shake = shake->Clone();
			shake->mGroupId = groupId;
			shake->SetActor(_tarBullet);
			shake->Start();
		}
	}

	//------------- scene
	TArray<UEffDataElem*> effectVec = behavData->mSceEffVec;
	TArray<UShakeElem*> shakeVec = behavData->mSceShkVec;

	for (UEffDataElem* effect : effectVec)
	{
		effect = effect->Clone();
		effect->mGroupId = groupId;
	}

	for (UShakeElem* shake : shakeVec)
	{
		shake = shake->Clone();
		shake->mGroupId = groupId;
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
				UE_LOG(EffectLogger, Warning, TEXT("--- AMyChar::DetachEffect, effectId:%d"), tmp.mEffData->mResId);

				if (effBinds->Num() == 0)
				{
					mEffectBindMap.Remove(_targetId);
				}
			}
		}
	}
}

UShakeElem* UEffectMgr::TestShake(AMyChar* _actor, int32 _id)
{
	UBehavData* behavData = GetBehav(_id);
	if (behavData != nullptr)
	{
		TArray<UShakeElem*>& shakeVec = behavData->GetTestShake();
		if (shakeVec.Num() > 0)
		{
			UShakeElem* shake = shakeVec[0]->Clone();
			shake->SetActor(_actor);
			shake->Start();
			return shake;
		}
	}

	return nullptr;
}

FEffectBind::FEffectBind(UEffDataElem* _effData, int32 _uuId, UParticleSystemComponent* _psComp)
{

}
