// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkMsg.h"

#include "Char/CharMgr.h"
#include "Char/MyChar.h"
#include "../Template/SkillTemplate.h"
#include "../Utils/SkillDataMgr.h"

DECLARE_LOG_CATEGORY_EXTERN(UPkMsgLogger, Log, All);
DEFINE_LOG_CATEGORY(UPkMsgLogger)

// Sets default values
UPkMsg::UPkMsg() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
	mCanLog = false;
	mSkillId = 0;					
	mSkillLogicType = ESkillAttackType::ATTACK_PHY;
	mAttackerId = 0;				
	mTargetId = 0;
	mAttackerData = nullptr;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mSkillTemp = nullptr;
}

UPkMsg::~UPkMsg()
{
	if (mAttackerData != nullptr)
	{
		mAttackerData->RemoveFromRoot();
	}
}

void UPkMsg::Init()
{
	mAttackerData = NewObject<UFightData>(UFightData::StaticClass());
	mAttackerData->AddToRoot();
}

void UPkMsg::SetData(int32 _skillId, const FVector& _targetLoc, int32 _attackerId, int32 _targetId /* = 0 */)
{
	USkillTemplate* skillTemp = USkillDataMgr::GetInstance()->GetSkillTemplate(_skillId);
	mSkillTemp = skillTemp != nullptr ? skillTemp : nullptr;
	if (mSkillTemp)
	{
		mSkillId = _skillId;
		mTargetLoc = _targetLoc;
		mAttacker = UCharMgr::GetInstance()->GetChar(_attackerId);
		mTarget = UCharMgr::GetInstance()->GetChar(_targetId);

	}
}

void UPkMsg::AddTarget(AMyChar* _char)
{
	UParam* param = NewObject<UParam>(UParam::StaticClass());
	param->mTargetId = _char->GetUuid();
	mTargetArr.Add(param);
}

//-------------------------------- UParam Begin

UParam::UParam()
{
	mFightData = nullptr;
	mTargetId = 0;
}

UParam::~UParam()
{
	if (mFightData)
	{
		mFightData->RemoveFromRoot();
	}
}

void UParam::Init()
{
	mFightData = NewObject<UFightData>(UFightData::StaticClass());
	mFightData->AddToRoot();
}
