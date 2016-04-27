// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AppendBuff.h"

#include "AbsBuff.h"

UAppendBuff::UAppendBuff() : Super()
{

}

UAppendBuff::~UAppendBuff()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UAppendBuff::~UAppendBuff"));
}

void UAppendBuff::BeginDestroy()
{


	UE_LOG(BuffLogger, Warning, TEXT("--- UAppendBuff::BeginDestroy"));
	Super::BeginDestroy();
}

void UAppendBuff::AppendBuff(UAbsBuff* _beAdd)
{

}
