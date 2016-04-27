// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CommonBuff.h"

UCommonBuff::UCommonBuff() : Super()
{

}

UCommonBuff::~UCommonBuff()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UCommonBuff::~UCommonBuff"));
}

void UCommonBuff::BeginDestroy()
{


	UE_LOG(BuffLogger, Warning, TEXT("--- UCommonBuff::BeginDestroy"));
	Super::BeginDestroy();
}