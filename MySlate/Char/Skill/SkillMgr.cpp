
#include "MySlate.h"
#include "SkillMgr.h"

#include "./Common/CommonHeader.h"
#include "../MyChar.h"
#include "./Template/SkillTemplate.h"
#include "./Template/BufflTemplate.h"
#include "./SkillTypes.h"
#include "../Res/ResMgr.h"
#include "../Res/Infos/SkillInfo.h"
#include "../Res/Infos/BuffInfo.h"
#include "../Res/Infos/BehavInfo.h"
#include "./Pk/PkMsg.h"
#include "../Comp/MyCharDataComp.h"
#include "./Pk/FightData.h"

USkillMgr::USkillMgr() : Super()
{

}

USkillMgr::~USkillMgr()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillMgr::~USkillMgr"));
}

void USkillMgr::BeginDestroy()
{
	for (TMap<int32, USkillTemplate*>::TConstIterator iter = mSkillTempMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mSkillTempMap.Empty();

	for (TMap<int32, UBufflTemplate*>::TConstIterator iter = mBuffTempMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mBuffTempMap.Empty();

	UE_LOG(SkillLogger, Warning, TEXT("--- USkillMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void USkillMgr::Tick(float DeltaTime)
{

}

bool USkillMgr::IsTickable() const
{
	return false;
}

TStatId USkillMgr::GetStatId() const
{
	return TStatId();
}

void USkillMgr::CharDeathNotify(AMyChar* _char)
{

}

USkillTemplate * USkillMgr::GetSkillTemplate(int32 _skillId)
{
	USkillTemplate** tempPtr = mSkillTempMap.Find(_skillId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}

UBufflTemplate * USkillMgr::GetBuffTemplate(int32 _buffId)
{
	UBufflTemplate** tempPtr = mBuffTempMap.Find(_buffId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}

void USkillMgr::LoadSkillData()
{
	UDataTable* dataTab = UResMgr::GetInstance()->GetInfoTable(EInfoType::Skill);
	if (dataTab != nullptr)
	{
		FSkillInfo* tmpPtr = nullptr;
		for (auto Iter : dataTab->RowMap)
		{
			tmpPtr = (FSkillInfo*)(Iter.Value);
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
			skill1->mId = tmpPtr->mId;
			skill1->mName = tmpPtr->mName;
			skill1->mDescr = tmpPtr->mDescr;
			skill1->mAttackDist = tmpPtr->mAttackDist;
			skill1->mSkillType = tmpPtr->mSkillType;
			skill1->mAnimType = tmpPtr->mAnimType;
			skill1->mBehavId = tmpPtr->mBehavId;

			//bullet info
			skill1->mBltElem->mCoolDown = tmpPtr->mBltInfo.mCoolDown;
			skill1->mBltElem->mLockedType = tmpPtr->mBltInfo.mLockedType;
			skill1->mBltElem->mTolerance = tmpPtr->mBltInfo.mTolerance;
			skill1->mBltElem->mBulletSpeed = tmpPtr->mBltInfo.mBulletSpeed;
			skill1->mBltElem->mFlyDist = tmpPtr->mBltInfo.mFlyDist;
			skill1->mBltElem->mAttachPoint = tmpPtr->mBltInfo.mAttachPoint;
			skill1->mBltElem->mLoc = tmpPtr->mBltInfo.mLoc;
			skill1->mBltElem->mScale = tmpPtr->mBltInfo.mScale;
			skill1->mBltElem->mRotate = tmpPtr->mBltInfo.mRotate;

			for (const FBulletMeshInfo& mesh : tmpPtr->mBltInfo.mMeshVec)
			{
				skill1->mBltElem->mMeshVec.Add(FBulletMeshData(
					mesh.mResId
					,mesh.mLoc
					,mesh.mScale
					,mesh.mRotate
				));
			}

			skill1->mFilterStr = tmpPtr->mFilterStr;
			skill1->mBeforeSkillStr = tmpPtr->mBeforeSkillStr;
			skill1->mBeforePkStr = tmpPtr->mBeforePkStr;
			skill1->mBeforeEvnsStr = tmpPtr->mBeforeEvnsStr;
			skill1->mEndEvnsStr = tmpPtr->mEndEvnsStr;
			skill1->mEndPkStr = tmpPtr->mEndPkStr;
			skill1->mEndSkillStr = tmpPtr->mEndSkillStr;

			skill1->AddToRoot();
			mSkillTempMap.Add(skill1->mId, skill1);
			UE_LOG(ResLogger, Warning, TEXT("--- key:%d, name:%s"), tmpPtr->mId, *tmpPtr->mName);
		}
	}
	else
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::LoadSkillData, dataTab is nullptr"));
	}
}

void USkillMgr::LoadBuffData()
{
	UDataTable* dataTab = UResMgr::GetInstance()->GetInfoTable(EInfoType::Buff);
	if (dataTab != nullptr)
	{
		FBuffInfo* tmpPtr = nullptr;
		for (auto Iter : dataTab->RowMap)
		{
			tmpPtr = (FBuffInfo*)(Iter.Value);
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			UBufflTemplate* buff1 = NewObject<UBufflTemplate>(UBufflTemplate::StaticClass());
			buff1->mId = tmpPtr->mId;
			buff1->mName = tmpPtr->mName;
			buff1->mDescr = tmpPtr->mDescr;
			buff1->mBuffTime = tmpPtr->mBuffTime;
			buff1->mCanDisperse = tmpPtr->mCanDisperse;
			buff1->mCanAdd = tmpPtr->mCanAdd;
			buff1->mInterType = tmpPtr->mInterType;
			buff1->mInterTime = tmpPtr->mInterTime;
			buff1->mBehavDataId = tmpPtr->mBehavDataId;
			buff1->mAttrsStr = tmpPtr->mAttrsStr;
			buff1->mBeforePkStr = tmpPtr->mBeforePkStr;
			buff1->mEndPkStr = tmpPtr->mEndPkStr;

			buff1->AddToRoot();
			mBuffTempMap.Add(buff1->mId, buff1);
			UE_LOG(ResLogger, Warning, TEXT("--- key:%d, name:%s"), tmpPtr->mId, *tmpPtr->mName);
		}
	}
	else
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::LoadSkillData, dataTab is nullptr"));
	}
}

//根据计算类型 _type，对每个单位目标的各种计算公式
float USkillMgr::FormulaPk(UPkMsg* _msg, EFormulaPkType _type)
{
	UFightData* atkData = _msg->GetAttackerData();
	UFightData* tarData = _msg->GetCurrTarget()->mTarget->GetDataComp()->GetFigthData();

	float ret = 0.f;
	if (_type == EFormulaPkType::Dodge)
	{
		ret = 0.f; //暂时所有都不闪避
	}
	else if (_type == EFormulaPkType::Damage)
	{
		ret = atkData->GetAttackPhy();
	}
	else
	{

	}
	return ret;
}
