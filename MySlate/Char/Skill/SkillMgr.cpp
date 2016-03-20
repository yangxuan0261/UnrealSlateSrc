// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillMgr.h"

#include "Common/CommonHeader.h"

DECLARE_LOG_CATEGORY_EXTERN(SkillMgrLogger, Log, All);
DEFINE_LOG_CATEGORY(SkillMgrLogger)

// Sets default values
USkillMgr::USkillMgr() : Super()
{
	mCounter = 0.f;
}
USkillMgr::~USkillMgr()
{

}

void USkillMgr::Tick(float DeltaTime)
{
	mCounter += DeltaTime;
	//UE_LOG(SkillMgrLogger, Warning, TEXT("--- USkillMgr::Tick:%f"), mCounter);
}

bool USkillMgr::IsTickable() const
{
	return true;
}

TStatId USkillMgr::GetStatId() const
{
	return TStatId();
}