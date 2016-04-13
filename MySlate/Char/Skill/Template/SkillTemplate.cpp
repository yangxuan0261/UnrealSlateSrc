// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillTemplate.h"

// Sets default values
USkillTemplate::USkillTemplate() : Super()
{
	mId = -1;
	mName = TEXT("Default SkillName");
	mDescr = TEXT("Default SkillDescr");
	mCoolDown = 5.f;
	mAttackDist = 10.f;
	mSkillType = ESkillType::Normal;
	mfilter = "";
}

USkillTemplate::~USkillTemplate()
{

}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforeSkill()
{
	return mBeforeSkillEvns;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforePk()
{
	return mBeforePk;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforeEvns()
{
	return mBeforeEvns;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndEvns()
{
	return mEndEvns;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndPk()
{
	return mEndPk;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndSkill()
{
	return mEndSkillEvns;
}

