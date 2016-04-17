// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkMsg.h"

#include "Char/CharMgr.h"
#include "Char/MyChar.h"
#include "../Template/SkillTemplate.h"
#include "../Utils/SkillDataMgr.h"

UPkMsg::UPkMsg() : Super()
{
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
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::~UPkMsg"));
	if (mAttackerData != nullptr)
	{
		mAttackerData->RemoveFromRoot();
		mAttackerData = nullptr;
	}
	for (int32 i = 0; i < mTargetArr.Num(); ++i)
	{
		mTargetArr[i]->RemoveFromRoot();
	}
	mTargetArr.Empty();
}

void UPkMsg::SetData(USkillTemplate* _skillTemp, const FVector& _targetLoc, int32 _attackerId, int32 _targetId /* = 0 */)
{
	mSkillTemp = _skillTemp;
	if (mSkillTemp)
	{
		mSkillId = mSkillTemp->mId;
		mTargetLoc = _targetLoc;
		mTarget = UCharMgr::GetInstance()->GetChar(_targetId);
	}
}

void UPkMsg::AddTarget(AMyChar* _char)
{
	UParam* param = NewObject<UParam>(UParam::StaticClass());
	param->AddToRoot();
	param->mTarget = _char;
	mTargetArr.Add(param);
}

void UPkMsg::ExeNullDlg()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::ExeNullDlg"));
	mSetNullDlg.ExecuteIfBound();
}

//-------------------------------- UParam Begin

UParam::UParam()
{
	mFightData = nullptr;
	mTarget = nullptr;
}

UParam::~UParam()
{
	if (mFightData)
	{
		mFightData->RemoveFromRoot();
		mFightData = nullptr;
	}
}

void UParam::Init()
{
	mFightData = NewObject<UFightData>(UFightData::StaticClass());
	mFightData->AddToRoot();
}
