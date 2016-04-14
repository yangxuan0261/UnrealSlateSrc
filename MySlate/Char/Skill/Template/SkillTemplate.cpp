// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillTemplate.h"
#include "../Function/FunctionFactory.h"

// Sets default values
USkillTemplate::USkillTemplate() : Super()
{
	mId = -1;
	mName = TEXT("Default SkillName");
	mDescr = TEXT("Default SkillDescr");
	mCoolDown = 5.f;
	mAttackDist = 10.f;
	mSkillType = ESkillType::Normal;
	mFilterStr = "";
	mFilter = nullptr;
}

USkillTemplate::~USkillTemplate()
{
	if (mFilter != nullptr)
	{
		mFilter->RemoveFromRoot();
	}
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

UAbsFilter* USkillTemplate::GetFilter()
{
	if (mFilter == nullptr)
	{
		SetFilter(mFilterStr);
	}
	return mFilter;
}

void USkillTemplate::SetFilter(const FString& _filterStr)
{
	mFilterStr = _filterStr;
	if (mFilter != nullptr)
	{
		mFilter->RemoveFromRoot();
	}
	if (mFilterStr.Len() == 0)
	{
		mFilterStr = Filter_Lock; //默认锁定目标
	}
	mFilter = UFunctionFactory::GetInstance()->createFilter(mFilterStr);
	mFilter->AddToRoot();
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndSkill()
{
	return mEndSkillEvns;
}

