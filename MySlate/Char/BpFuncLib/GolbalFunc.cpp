// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "GolbalFunc.h"

#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/SkillMgr.h"
#include "Char/CharMgr.h"
#include "Kismet/KismetMathLibrary.h"
#include "Char/Skill/Function/FuncFactory.h"
#include "BaseDatas/BaseDataMgr.h"

USkillDataMgr*	UGolbalFunc::gSkillDataMgr = nullptr;
USkillMgr*		UGolbalFunc::gSkillMgr = nullptr;
UCharMgr*		UGolbalFunc::gCharMgr = nullptr;
UFuncFactory*	UGolbalFunc::gFunctionMgr = nullptr;
UBaseDataMgr*	UGolbalFunc::gBaseDataMgr = nullptr;

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
	gSkillDataMgr->InitFakeDate();
	gSkillMgr = USkillMgr::GetInstance();
	gCharMgr = UCharMgr::GetInstance();
	gFunctionMgr = UFuncFactory::GetInstance();
	gFunctionMgr->InitFuncAndFilters();
	gBaseDataMgr = UBaseDataMgr::GetInstance();
	gBaseDataMgr->InitFakeData();
}

void UGolbalFunc::DestroyMgrs()
{
	USkillDataMgr::ReleaseInstance();
	USkillMgr::ReleaseInstance();
	UCharMgr::ReleaseInstance();
	UFuncFactory::ReleaseInstance();
	UBaseDataMgr::ReleaseInstance();
	gSkillDataMgr = nullptr;
	gSkillMgr = nullptr;
	gCharMgr = nullptr;
	gFunctionMgr = nullptr;
	gBaseDataMgr = nullptr;
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
	str.ParseIntoArray(params, TEXT(","), true);

	for (int32 i = 0; i < params.Num(); ++i)
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- index:%d, value:%s"), i, *params[i]);
	}

}

void UGolbalFunc::TestForceGC()
{
	GWorld->GetWorld()->ForceGarbageCollection(true);
}

void UGolbalFunc::TestStrContains(FString _str)
{
	bool b = _str.Contains(TEXT("%"));
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- TestStrContains result:%d"), (int32)b);
}

