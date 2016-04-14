// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkPorcess.h"

DECLARE_LOG_CATEGORY_EXTERN(UPkPorcessLogger, Log, All);
DEFINE_LOG_CATEGORY(UPkPorcessLogger)

#include "PkMsg.h"
#include "char/MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Template/SkillTemplate.h"

// Sets default values
UPkPorcess::UPkPorcess() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
}

UPkPorcess::~UPkPorcess()
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
	}
}

void UPkPorcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
	}
	mPkMsg = _pkMsg;
	mPkMsg->AddToRoot();
}

void UPkPorcess::Run()
{

}

bool UPkPorcess::CheckCanPk()
{
	return false;
}

void UPkPorcess::FilterVS()
{
	UAbsFilter* filter = nullptr;
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	if (skillTemp)
	{
		filter = skillTemp->GetFilter();
	}

	if ( filter != nullptr)
	{
		filter->Filter(mPkMsg);
	}
}

void UPkPorcess::RunBeforePk()
{
}

void UPkPorcess::RunBeforeSkill()
{
}

void UPkPorcess::PkLogic()
{
}

void UPkPorcess::RunEndSkill()
{

}

void UPkPorcess::RunEndPk()
{

}

void UPkPorcess::PkPrice()
{

}
