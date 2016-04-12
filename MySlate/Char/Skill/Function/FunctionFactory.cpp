// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FunctionFactory.h"
#include "../Utils/CommonDef.h"
#include "Base/AbsPkEvent.h"
#include "../Filter/AbsFilter.h"

DECLARE_LOG_CATEGORY_EXTERN(UFunctionFactoryLogger, Log, All);
DEFINE_LOG_CATEGORY(UFunctionFactoryLogger)

// Sets default values
UFunctionFactory::UFunctionFactory() : Super()
{

}

UFunctionFactory::~UFunctionFactory()
{
	for (auto iter = mFunctionMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
	}
	mFunctionMap.Empty();
	
	for (auto iter = mFilterMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
	}
	mFilterMap.Empty();
}

void UFunctionFactory::registerFunction(UAbsPkEvent* _object)
{
	FString key = _object->GetKey();
	UAbsPkEvent** func = mFunctionMap.Find(key);
	if (func != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFunctionMap.Add(key, _object);
}

void UFunctionFactory::registerFilter(UAbsFilter* _object)
{
	FString key = _object->GetKey();
	UAbsFilter** filter = mFilterMap.Find(key);
	if (filter != nullptr)
	{
		return;
	}
	_object->AddToRoot();
	mFilterMap.Add(key, _object);
}

UAbsFilter* UFunctionFactory::createFilter(const FString& _str)
{
	FString paramStr = _str.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, *Split_Line, true);


	return nullptr;
}
