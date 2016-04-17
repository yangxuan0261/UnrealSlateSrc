// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CircleFilter.h"

UCircleFilter::UCircleFilter() : Super()
{

}

UCircleFilter::~UCircleFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- UCircleFilter::~UCircleFilter"));
}
 
void UCircleFilter::Filter(UPkMsg* msg)
{

}

UAbsFilter* UCircleFilter::Clone()
{
	return CreateFilter(mKey);
}

void UCircleFilter::Parser(const TArray<FString>& _params)
{
	mType = -1;
	mCount = -1;
	mRadius = 100;
	if (_params.Num() > 0)
	{
		mType = FCString::Atoi(*_params[0]);
		mCount = FCString::Atoi(*_params[1]);
		mRadius = FCString::Atoi(*_params[2]);
	}
}

UCircleFilter* UCircleFilter::CreateFilter(const FString& _key)
{
	UCircleFilter* circleFilter = NewObject<UCircleFilter>(UCircleFilter::StaticClass());
	circleFilter->SetKey(_key);
	return circleFilter;
}
