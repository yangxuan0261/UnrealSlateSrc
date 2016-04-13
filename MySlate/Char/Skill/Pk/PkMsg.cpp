// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkMsg.h"

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
}

UPkMsg::~UPkMsg()
{
	
}

