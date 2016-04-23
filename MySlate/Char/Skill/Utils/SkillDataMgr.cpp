// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillDataMgr.h"

#include "Common/CommonHeader.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillTypes.h"

USkillDataMgr::USkillDataMgr() : Super()
{

}

USkillDataMgr::~USkillDataMgr()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::~USkillDataMgr"));
}

void USkillDataMgr::BeginDestroy()
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

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::BeginDestroy"));
	Super::BeginDestroy();
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
	skill1->mTolerance = 5.f;
	skill1->mBulletSpeed = 400.f;
	skill1->mFlyDist = 0.f;
	skill1->mSkillType = ESkillType::Normal;
	skill1->mFilterStr = TEXT("circle,0,-1,500");
	skill1->mAttachPoint = TEXT("BulletPos");
	skill1->mAnimType = EAnimType::Skill_1;
	mSkillTempMap.Add(skill1->mId, skill1);

	USkillTemplate* skill2 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill2->AddToRoot();
	skill2->mId = 10002;
	skill2->mName = TEXT("Skill2 Name");
	skill2->mDescr = TEXT("Skill2 Descr");
	skill2->mCoolDown = 7.f;
	skill2->mAttackDist = 50.f;
	skill2->mTolerance = 5.f;
	skill2->mBulletSpeed = 5.f;
	skill2->mFlyDist = 0.f;
	skill2->mSkillType = ESkillType::Initiative;
	skill2->mFilterStr = TEXT("circle,0,-1,200");
	skill2->mAttachPoint = TEXT("rhand");
	skill2->mAnimType = EAnimType::Skill_2;
	mSkillTempMap.Add(skill2->mId, skill2);

	USkillTemplate* skill3 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill3->AddToRoot();
	skill3->mId = 10003;
	skill3->mName = TEXT("Skill3 Name");
	skill3->mDescr = TEXT("Skill3 Descr");
	skill3->mCoolDown = 5.f;
	skill3->mAttackDist = 80.f;
	skill3->mTolerance = 5.f;
	skill3->mBulletSpeed = 5.f;
	skill3->mFlyDist = 0.f;
	skill3->mSkillType = ESkillType::Initiative;
	skill3->mFilterStr = TEXT("circle,0,-1,200");
	skill3->mAttachPoint = TEXT("lhand");
	skill3->mAnimType = EAnimType::Skill_3;
	mSkillTempMap.Add(skill3->mId, skill3);
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


