
#include "MySlate.h"
#include "EffectMgr.h"

#include "../Res/ResMgr.h"
#include "../Res/Infos/BehavInfo.h"
#include "./Effects/BehavData.h"
#include "./Effects/BehavElem.h"
#include "./Effects/EffectElem.h"
#include "./Effects/ShakeElem.h"
#include "../MyChar.h"
#include "../MyBullet.h"
#include "../MyScene.h"
#include "../Skill/Template/SkillTemplate.h"

static int32 gEffectUuid = 1;
static int32 IdGeneratorEffect()
{      
	if (gEffectUuid == 65534)
	{
		gEffectUuid = 1;
	}

	return gEffectUuid++;
} 

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

int32 UEffectMgr::AttachBehav(AMyChar* _tarChar, EOwnType _ownType, AMyBullet* _tarBullet, int32 _behavDataId)
{
	UBehavData* behavData = GetBehav(_behavDataId);
	if (behavData == nullptr)
	{
		UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehavData, behavData == nullptr, id:%d"), _behavDataId);
		return 0;
	}

	int32 groupId = ::IdGeneratorEffect(); //本次行为数据的识别id
	TArray<UBehavElem*> allElem;

	auto BindShakeFunc = [&](UShakeElem* _shake, IBehavInterface* _target)->void {
		UShakeElem* shake = _shake->Clone();
		shake->mGroupId = groupId;
		shake->SetActor(_target);
		shake->Start();
		allElem.Add(shake);
	};

	auto BindEffectFunc = [&](UEffDataElem* _effect, IBehavInterface* _tar1, AActor* _tar2)->void {
		UParticleSystem* ps = UResMgr::GetInstance()->GetParticle(_effect->mResId);
		if (ps == nullptr)
		{
			UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachBehavData, ps == nullptr, resId:%d"), _effect->mResId);
			return;
		}

		UParticleSystemComponent* psComp = nullptr;
		if (_effect->mFollowType == EFollowType::Follow) //跟随
		{
			USceneComponent* dstComp = nullptr;
			if (_effect->mBindPoint.Len() > 0) //绑定骨骼，人物特殊处理
			{
				AMyChar* myChar = Cast<AMyChar>(_tar1);
				dstComp = myChar != nullptr ? myChar->GetMesh() : nullptr;
			}
			else //绑定root组件
			{
				dstComp = _tar2->GetRootComponent();
			}
			psComp = UGameplayStatics::SpawnEmitterAttached(ps
				, dstComp
				, FName(*(_effect->mBindPoint))
				, _effect->mLoc
				, _effect->mRotate);
			if (psComp != nullptr)
			{
				psComp->SetRelativeScale3D(_effect->mScale);
			}
		}
		else if (_effect->mFollowType == EFollowType::UnFollow) //不跟随，相对char当前transform进行偏移，scale除外
		{
			FTransform srcTran = _tar2->GetTransform();
			FTransform dstTran(_effect->mRotate + srcTran.Rotator(), _effect->mLoc + srcTran.GetTranslation(), _effect->mScale);
			psComp = UGameplayStatics::SpawnEmitterAtLocation(
				GWorld
				, ps
				, dstTran);
		}

		if (psComp != nullptr)
		{
			_effect = _effect->Clone();
			_effect->mGroupId = groupId;
			_effect->SetActor(_tar1);
			_effect->SetData(psComp);
			_effect->Start();
			allElem.Add(_effect);
		}
	};

	//------------- char 人物特效
	if (_tarChar != nullptr)
	{
		TArray<UEffDataElem*> effectVec = _ownType == EOwnType::Self ? behavData->mAtkEffVec : behavData->mTarEffVec;
		TArray<UShakeElem*> shakeVec = _ownType == EOwnType::Self ? behavData->mAtkShkVec : behavData->mTarShkVec;

		for (UEffDataElem* effect : effectVec)
		{
			BindEffectFunc(effect, _tarChar, _tarChar);
		}

		for (UShakeElem* shake: shakeVec)
		{
			BindShakeFunc(shake, _tarChar);
		}

		_tarChar->AddBehavElem(groupId, allElem);
	}

	//------------- bullet 子弹特效
	if (_tarBullet != nullptr)
	{
		allElem.Empty();
		TArray<UEffDataElem*> effectVec = behavData->mBltEffVec;
		TArray<UShakeElem*> shakeVec = behavData->mBltShkVec;

		for (UEffDataElem* effect : effectVec)
		{
			BindEffectFunc(effect, _tarBullet, _tarBullet);
		}

		for (UShakeElem* shake : shakeVec)
		{
			BindShakeFunc(shake, _tarBullet);
		}

		_tarBullet->AddBehavElem(groupId, allElem);
	}

	//------------- scene 场景特效
	TArray<UEffDataElem*> effectVec = behavData->mSceEffVec;
	TArray<UShakeElem*> shakeVec = behavData->mSceShkVec;
	AMyScene* myScene = gGetScene();

	allElem.Empty();
	for (UEffDataElem* effect : effectVec)
	{
		BindEffectFunc(effect, myScene, myScene);
	}

	for (UShakeElem* shake : shakeVec)
	{
		BindShakeFunc(shake, _tarBullet);
	}

	myScene->AddBehavElem(groupId, allElem);
	return groupId;
}

void UEffectMgr::DetachBehav(IBehavInterface* _actor, int32 _groupId)
{
	if (_actor != nullptr)
	{
		_actor->RemoveBehavElemAll(_groupId);
	}
}

void UEffectMgr::AttachMesh(AMyBullet* _bullet, USkillTemplate* _skillTemp)
{
	const TArray<FBulletMeshData>& meshVec = _skillTemp->mBltElem->mMeshVec;
	if (meshVec.Num() == 0)
	{
		return;
	}

	TArray<UStaticMeshComponent*> newMeshVec;
	for (int32 i = 0; i < meshVec.Num(); i++)
	{
		const FBulletMeshData& mesh = meshVec[i];
		UStaticMesh* staticMesh = UResMgr::GetInstance()->GetStaticMesh(mesh.mResId);
		if (staticMesh == nullptr)
		{
			UE_LOG(EffectLogger, Error, TEXT("--- UEffectMgr::AttachMesh, mesh == nullptr, resId:%d"), mesh.mResId);
			continue;
		}

		UStaticMeshComponent* meshComp = NewObject<UStaticMeshComponent>(_bullet, TEXT("BulletStaticMeshComponent"));
		meshComp->RegisterComponent();
		meshComp->AttachTo(_bullet->GetRootComponent()); //绑定mesh到子弹身上
		meshComp->SetStaticMesh(staticMesh);
		meshComp->SetRelativeLocation(mesh.mLoc);
		meshComp->SetRelativeScale3D(mesh.mScale);
		meshComp->SetRelativeRotation(mesh.mRotate);
		newMeshVec.Add(meshComp);
	}
	_bullet->SetMeshComp(newMeshVec);
}

UShakeElem* UEffectMgr::TestShake(AMyChar* _actor, int32 _id)
{
	UBehavData* behavData = GetBehav(_id);
	if (behavData != nullptr)
	{
		TArray<UBehavElem*> addVec;
		TArray<UShakeElem*>& shakeVec = behavData->GetTestShake();
		if (shakeVec.Num() > 0)
		{
			UShakeElem* shake = shakeVec[0]->Clone();
			shake->mGroupId = ::IdGeneratorEffect();
			shake->SetActor(_actor);
			shake->Start();
			addVec.Add(shake);
			_actor->AddBehavElem(shake->mGroupId, addVec);

			return shake;
		}
	}

	return nullptr;
}
