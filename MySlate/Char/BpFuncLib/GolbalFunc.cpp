// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "GolbalFunc.h"

#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/SkillMgr.h"
#include "Char/CharMgr.h"
#include "Kismet/KismetMathLibrary.h"
#include "Char/Skill/Function/FunctionFactory.h"

DECLARE_LOG_CATEGORY_EXTERN(UGolbalFuncLogger, Log, All);
DEFINE_LOG_CATEGORY(UGolbalFuncLogger)

USkillDataMgr*	UGolbalFunc::gSkillDataMgr = nullptr;
USkillMgr*		UGolbalFunc::gSkillMgr = nullptr;
UCharMgr*		UGolbalFunc::gCharMgr = nullptr;
UFunctionFactory*	UGolbalFunc::gFunctionMgr = nullptr;

// Sets default values
//UGolbalFunc::UGolbalFunc(const UGolbalFunc& ObjectInitializer) : Super(ObjectInitializer)
UGolbalFunc::UGolbalFunc() : Super()
{
	
}

UGolbalFunc::~UGolbalFunc()
{

}

void UGolbalFunc::InitMgrs()
{
	gSkillDataMgr = USkillDataMgr::GetInstance();
	gSkillMgr = USkillMgr::GetInstance();
	gCharMgr = UCharMgr::GetInstance();
	gFunctionMgr = UFunctionFactory::GetInstance();
	gFunctionMgr->InitFuncAndFilters();
}

void UGolbalFunc::DestroyMgrs()
{
	USkillDataMgr::ReleaseInstance();
	USkillMgr::ReleaseInstance();
	UCharMgr::ReleaseInstance();
	UFunctionFactory::ReleaseInstance();
	gSkillDataMgr = nullptr;
	gSkillMgr = nullptr;
	gCharMgr = nullptr;
	gFunctionMgr = nullptr;
}

void UGolbalFunc::TurnForward(AActor* _actor, const FVector& _targetLoc)
{
	FRotator rota = UKismetMathLibrary::FindLookAtRotation(_actor->GetActorLocation(), _targetLoc);
	_actor->SetActorRotation(rota);
}

void UGolbalFunc::TestStrSplit()
{
	FString str = TEXT("aaa,bbb,,ccc,ddd");
	TArray<FString> params;
	str.ParseIntoArray(params, TEXT(","), false);

	for (int32 i = 0; i < params.Num(); ++i)
	{
		UE_LOG(UGolbalFuncLogger, Warning, TEXT("--- index:%d, value:%s"), i, *params[i]);
	}

}

void UGolbalFunc::TestForceGC()
{
	GWorld->GetWorld()->ForceGarbageCollection(true);
}

