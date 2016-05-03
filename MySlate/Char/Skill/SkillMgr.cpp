
#include "MySlate.h"
#include "SkillMgr.h"

#include "./Common/CommonHeader.h"
#include "../Effect/Effects/UBehavData.h"
#include "../Effect/EffectMgr.h"
#include "../MyChar.h"
#include "./Template/SkillTemplate.h"
#include "./Template/BufflTemplate.h"
#include "./SkillTypes.h"
#include "../Res/ResMgr.h"
#include "../Res/Infos/SkillInfo.h"
#include "../Res/Infos/BuffInfo.h"
#include "../Res/Infos/BehavInfo.h"

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
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			tmpPtr = (FSkillInfo*)(Iter.Value);
			USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
			skill1->mId = tmpPtr->mId;
			skill1->mName = tmpPtr->mName;
			skill1->mDescr = tmpPtr->mDescr;
			skill1->mCoolDown = tmpPtr->mCoolDown;
			skill1->mLockedType = tmpPtr->mLockedType;
			skill1->mAttackDist = tmpPtr->mAttackDist;
			skill1->mTolerance = tmpPtr->mTolerance;
			skill1->mBulletSpeed = tmpPtr->mBulletSpeed;
			skill1->mFlyDist = tmpPtr->mFlyDist;
			skill1->mSkillType = tmpPtr->mSkillType;
			skill1->mAttachPoint = tmpPtr->mAttachPoint;
			skill1->mAnimType = tmpPtr->mAnimType;
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
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			tmpPtr = (FBuffInfo*)(Iter.Value);
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
