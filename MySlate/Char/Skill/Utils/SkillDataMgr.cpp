// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillDataMgr.h"

#include "Common/CommonHeader.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillTypes.h"


DECLARE_LOG_CATEGORY_EXTERN(SkillDataMgrLogger, Log, All);
DEFINE_LOG_CATEGORY(SkillDataMgrLogger)

// Sets default values
USkillDataMgr::USkillDataMgr() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
}

USkillDataMgr::~USkillDataMgr()
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
}

void USkillDataMgr::InitFakeDate()
{
	USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill1->AddToRoot();
	skill1->mId = 10001;
	skill1->mName = TEXT("Skill1 Name");
	skill1->mDescr = TEXT("Skill1 Descr");
	skill1->mCoolDown = 3.f;
	skill1->mAttackDist = 100.f;
	skill1->mSkillType = ESkillType::Normal;
	skill1->mFilterStr = TEXT("lock,-1");
	skill1->mAttachPoint = TEXT("");
	mSkillTempMap.Add(skill1->mId, skill1);

	USkillTemplate* skill2 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill2->AddToRoot();
	skill2->mId = 10002;
	skill2->mName = TEXT("Skill2 Name");
	skill2->mDescr = TEXT("Skill2 Descr");
	skill2->mCoolDown = 7.f;
	skill2->mAttackDist = 50.f;
	skill2->mSkillType = ESkillType::Initiative;
	skill1->mFilterStr = TEXT("circle,-1,-1,200");
	skill1->mAttachPoint = TEXT("rhand");
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


