// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "GolbalFunc.h"

#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/SkillMgr.h"
#include "Char/CharMgr.h"

USkillDataMgr*	UGolbalFunc::gSkillDataMgr = nullptr;
USkillMgr*		UGolbalFunc::gSkillMgr = nullptr;
UCharMgr*		UGolbalFunc::gCharMgr = nullptr;

// Sets default values
//UGolbalFunc::UGolbalFunc(const UGolbalFunc& ObjectInitializer) : Super(ObjectInitializer)
UGolbalFunc::UGolbalFunc() : Super()
{
	
}

UGolbalFunc::~UGolbalFunc()
{

}

void UGolbalFunc::InitMgrs()
{
	gSkillDataMgr = USkillDataMgr::GetInstance();
	gSkillMgr = USkillMgr::GetInstance();
	gCharMgr = UCharMgr::GetInstance();
}

void UGolbalFunc::DestroyMgrs()
{
	USkillDataMgr::ReleaseInstance();
	USkillMgr::ReleaseInstance();
	UCharMgr::ReleaseInstance();
	gSkillDataMgr = nullptr;
	gSkillMgr = nullptr;
	gCharMgr = nullptr;
}

int32 UGolbalFunc::TestSingleton()
{
	return 123;
}

