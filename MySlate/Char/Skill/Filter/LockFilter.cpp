// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "LockFilter.h"

ULockFilter::ULockFilter() : Super()
{
}

ULockFilter::~ULockFilter()
{

}

void ULockFilter::Filter(UPkMsg* msg)
{

}

UAbsFilter* ULockFilter::Clone()
{
	return CreateFilter(mKey);
}

void ULockFilter::Paser(const TArray<FString>& _params)
{
	mType = -1; //Ä¬ÈÏµÐ·½
	if (_params.Num() > 0)
	{
		mType = FCString::Atoi(*_params[0]);
	}
}

ULockFilter* ULockFilter::CreateFilter(const FString& _key)
{
	ULockFilter* lockFilter = NewObject<ULockFilter>(ULockFilter::StaticClass());
	lockFilter->SetKey(_key);
	return lockFilter;
}
