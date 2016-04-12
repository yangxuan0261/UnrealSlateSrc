// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FunctionFactory.h"
#include "../Utils/CommonDef.h"

DECLARE_LOG_CATEGORY_EXTERN(UFunctionFactoryLogger, Log, All);
DEFINE_LOG_CATEGORY(UFunctionFactoryLogger)

// Sets default values
UFunctionFactory::UFunctionFactory() : Super()
{

}

UFunctionFactory::~UFunctionFactory()
{

}

UAbsFilter* UFunctionFactory::createFilter(const FString& _str)
{
	FString paramStr = _str.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, *Split_Line, true);
	return nullptr;
}
