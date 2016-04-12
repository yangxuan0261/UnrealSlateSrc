// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "LockFilter.h"

ULockFilter::ULockFilter() : Super()
{
}

ULockFilter::~ULockFilter()
{

}

void ULockFilter::filter(UPkMsg* msg)
{

}

UAbsFilter* ULockFilter::clone()
{
	return nullptr;
}

void ULockFilter::paser(TArray<FString> _params)
{
	mType = -1; //Ä¬ÈÏµÐ·½
	if (_params.Num() > 0)
	{
		mType = FCString::Atoi(*_params[0]);
	}
}
