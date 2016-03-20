// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillDataMgr.h"

#include "Common/CommonHeader.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"

DECLARE_LOG_CATEGORY_EXTERN(SkillDataMgrLogger, Log, All);
DEFINE_LOG_CATEGORY(SkillDataMgrLogger)

// Sets default values
USkillDataMgr::USkillDataMgr() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
}

USkillDataMgr::~USkillDataMgr()
{

}

void USkillDataMgr::InitFakeDate()
{
	USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill1->AddToRoot();
	skill1->mId = 10001;
	skill1->mName = TEXT("Skill1 Name");
	skill1->mDescr = TEXT("Skill1 Descr");
	skill1->mCoolDown = 3.f;
	mSkillTempMap.Add(skill1->mId, skill1);

	USkillTemplate* skill2 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill2->AddToRoot();
	skill2->mId = 10002;
	skill2->mName = TEXT("Skill2 Name");
	skill2->mDescr = TEXT("Skill2 Descr");
	skill2->mCoolDown = 7.f;
	mSkillTempMap.Add(skill2->mId, skill2);
}

USkillTemplate * USkillDataMgr::GetSkillTemplate(int32 _skillId)
{
	USkillTemplate** tempPtr = mSkillTempMap.Find(_skillId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}

UBufflTemplate * USkillDataMgr::GetBuffTemplate(int32 _buffId)
{
	UBufflTemplate** tempPtr = mBuffTempMap.Find(_buffId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}


