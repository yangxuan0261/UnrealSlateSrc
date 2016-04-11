// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

DECLARE_LOG_CATEGORY_EXTERN(USkillFuncLogger, Log, All);
DEFINE_LOG_CATEGORY(USkillFuncLogger)

// Sets default values
USkillFunction::USkillFunction() : Super()
{
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mSkillId = -1;
}

USkillFunction::~USkillFunction()
{
	UE_LOG(UCoolDownLogger222, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{

}

