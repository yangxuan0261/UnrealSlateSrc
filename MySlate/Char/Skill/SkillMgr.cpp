
#include "MySlate.h"
#include "SkillMgr.h"

#include "./Common/CommonHeader.h"
#include "./Effect/UBehavData.h"
#include "../MyChar.h"
#include "../Res/ResMgr.h"

static int32 gEffectUuid = 1;
static int32 IdGeneratorEffect()
{
	return gEffectUuid++;
}

USkillMgr::USkillMgr() : Super()
{

}

USkillMgr::~USkillMgr()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillMgr::~USkillMgr"));
}

void USkillMgr::BeginDestroy()
{

	UE_LOG(SkillLogger, Warning, TEXT("--- USkillMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void USkillMgr::Tick(float DeltaTime)
{
	//特效剩余时间
	//for (FEffectBind& effBind : mEffects)
	//{
	//	effBind.mLeftTime -= DeltaTime;
	//}
}

bool USkillMgr::IsTickable() const
{
	return true;
}

TStatId USkillMgr::GetStatId() const
{
	return TStatId();
}

UBehavData* USkillMgr::GetBehaviorData(int32 _id)
{
	UBehavData** bPtr = mBehaviorDataMap.Find(_id);
	if (bPtr == nullptr)
	{
		*bPtr = LoadBehaviorData(_id);
		if (*bPtr != nullptr)
			mBehaviorDataMap.Add(_id, *bPtr);
	}
	return *bPtr;
}

//相同特效id只存放时间最长的
TArray<int32> USkillMgr::AttachBehavData(AMyChar* _target, int32 _behavDataId, float _time)
{
	TArray<int32> dstEffUuids;
	UBehavData* behavData = GetBehaviorData(_behavDataId);
	if (behavData == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::AttachBehavData, behavData == nullptr, id:%d"), _behavDataId);
		return TArray<int32>();
	}

	TArray<UEffDataElem*>& elems = behavData->GetEffElems(); //表现数据中的特效集
	int targetId = _target->GetUuid();
	TArray<FEffectBind>* effs = mEffectBindMap.Find(targetId);
	if (effs != nullptr)
	{
		FEffectBind* dstEff = nullptr;
		UEffDataElem* ele = nullptr;
		int32 len = elems.Num();
		for (int32 i = 0; i< len; ++i)
		{
			ele = elems[i];

			//绑定位置和特效id相同，只为其续命，不spwan新的粒子组件
			FEffectBind* dstEff = effs->FindByPredicate([&](const FEffectBind& tmp)->bool {
				return tmp.mEffData->mId == ele->mId && tmp.mEffData->mBindPoint == ele->mBindPoint;
			});

			bool needSpwan = true;
			if (dstEff != nullptr)
			{
				if (_time >= dstEff->mLeftTime)
				{
					int32 newUuid = ::IdGeneratorEffect();
					dstEff->mUuId = newUuid; //换个新id，让老的找不到
					dstEff->mUuId = _time; //续命
					dstEffUuids.Add(newUuid);
					needSpwan = false;
				}
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

void USkillMgr::CreateEffBind(AMyChar* _target, UEffDataElem* _ele, float _time, TArray<FEffectBind>& _bindArr, TArray<int32>& _dstUuids)
{
	UParticleSystem* ps = UResMgr::GetInstance()->GetParticle(_ele->mId);
	auto psComp = ps != nullptr ?
		UGameplayStatics::SpawnEmitterAttached(ps
			, _target->GetMesh()
			, FName(*(_ele->mBindPoint))
			, _ele->mLoc
			, _ele->mRotate) : nullptr;

	if (ps != nullptr && psComp != nullptr)
	{
		psComp->SetRelativeScale3D(_ele->mScale);
		int32 newUuid = ::IdGeneratorEffect();
		_dstUuids.Add(newUuid);

		//TODO 遍历中增加可能有问题，待验证
		_bindArr.Add(FEffectBind(_ele, _time, newUuid));
	}
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillMgr::AttachBehavData, eff == null, id:%d"), _ele->mId);
	}
}

void USkillMgr::DetachEffect(int32 _targetId, const TArray<int32>& _effuuids)
{
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
				UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::DetachEffect, effectId:%d"), tmp.mEffData->mId);
			}
		}
	}
}

void USkillMgr::CharDeathNotify(AMyChar* _char)
{

}

UBehavData* USkillMgr::LoadBehaviorData(int32 _id)
{

	return nullptr;
}
