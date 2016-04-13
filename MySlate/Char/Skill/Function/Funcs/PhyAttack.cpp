// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PhyAttack.h"

UPhyAttack::UPhyAttack() : Super()
{
}

UPhyAttack::~UPhyAttack()
{

}

UPhyAttack* UPhyAttack::CreateFunction(const FString& _key)
{
	UPhyAttack* func = NewObject<UPhyAttack>(UPhyAttack::StaticClass());
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UPhyAttack::Clone()
{
	return CreateFunction(mKey);
}
