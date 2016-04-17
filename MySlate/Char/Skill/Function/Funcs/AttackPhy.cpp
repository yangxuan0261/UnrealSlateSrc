// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AttackPhy.h"

UAttackPhy::UAttackPhy() : Super()
{
	mValue = 0.f;
	mOwner = 1; //攻击者
	mLimitId = -1; //不限制技能
}

UAttackPhy::~UAttackPhy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::~UAttackPhy"));
}

UAttackPhy* UAttackPhy::CreateFunction(const FString& _key)
{
	UAttackPhy* func = NewObject<UAttackPhy>(UAttackPhy::StaticClass());
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UAttackPhy::Clone()
{
	return CreateFunction(mKey);
}

void UAttackPhy::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 3)
	{
		CheckPercent(_params[0]);
		mOwner = FCString::Atoi(*_params[1]);
		mLimitId = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- UAttackPhy::Parser, params num < 2"));
	}
}
