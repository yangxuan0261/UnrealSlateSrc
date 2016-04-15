// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"

// Sets default values
USkillFunction::USkillFunction() : Super()
{
	mSkillId = -1;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);
	if (mPkMsg)
	{
		mPkMsg->RemoveFromRoot();
	}
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = _skillTemp->mId;
	mType = _skillTemp->mSkillType;

}

void USkillFunction::ShootBegin()
{
	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();
}

void USkillFunction::ShootEnd()
{

}

