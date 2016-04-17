// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "Attack.h"

UAttack::UAttack() : Super()
{
	mValue = 0.f;
	mOwner = 1; //攻击者
	mLimitId = -1; //不限制技能
}

UAttack::~UAttack()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttack::~UAttack"));
}

UAttack* UAttack::CreateFunction(const FString& _key)
{
	UAttack* func = NewObject<UAttack>(UAttack::StaticClass());
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UAttack::Clone()
{
	return CreateFunction(mKey);
}

void UAttack::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 3)
	{
		CheckPercent(_params[0]);
		mOwner = FCString::Atoi(*_params[1]);
		mLimitId = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- UAttack::Parser, params num < 2"));
	}
}

void UAttack::RunBeforePk(UPkMsg* msg)
{

}
