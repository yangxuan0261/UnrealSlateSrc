// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BufflTemplate.h"

UBufflTemplate::UBufflTemplate() : Super()
{
 
}

UBufflTemplate::~UBufflTemplate()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::~UBufflTemplate"));
}

void UBufflTemplate::BeginDestroy()
{


	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::BeginDestroy"));
	Super::BeginDestroy();
}

