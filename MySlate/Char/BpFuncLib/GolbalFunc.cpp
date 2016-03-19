// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "GolbalFunc.h"

#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/SkillMgr.h"
#include "Char/Skill/CoolDown/CoolDownMgr.h"

USkillDataMgr*	UGolbalFunc::gSkillDataMgr		= nullptr;
USkillMgr*		UGolbalFunc::gSkillMgr			= nullptr;
UCoolDownMgr*	UGolbalFunc::gCoolDownMgr		= nullptr;

// Sets default values
UGolbalFunc::UGolbalFunc() : Super()
{
	gSkillDataMgr = USkillDataMgr::GetInstance();
	gSkillMgr = USkillMgr::GetInstance();
	gCoolDownMgr = UCoolDownMgr::GetInstance();
}

UGolbalFunc::~UGolbalFunc()
{
	USkillDataMgr::ReleaseInstance();
	USkillMgr::ReleaseInstance();
	UCoolDownMgr::ReleaseInstance();
	gSkillDataMgr = nullptr;
	gSkillMgr = nullptr;
	gCoolDownMgr = nullptr;
}

int32 UGolbalFunc::TestSingleton()
{
	return USkillDataMgr::GetInstance()->GetTestNum();
}

