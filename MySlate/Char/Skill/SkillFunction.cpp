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
}

USkillFunction::~USkillFunction()
{
	UE_LOG(UCoolDownLogger222, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillTemplate->mId);
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

