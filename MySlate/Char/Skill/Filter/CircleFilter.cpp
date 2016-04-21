// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CircleFilter.h"

#include "../Pk/PkMsg.h"
#include "Char/MyChar.h"

UCircleFilter::UCircleFilter() : Super()
{
	mRadius = 100;
}

UCircleFilter::~UCircleFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- UCircleFilter::~UCircleFilter"));
}
 
void UCircleFilter::BeginDestroy()
{

	UE_LOG(FilterLogger, Warning, TEXT("--- UCircleFilter::BeginDestroy"));
	Super::BeginDestroy();
}

void UCircleFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector(0.f, 0.f, 0.f) */)
{
	Super::Filter(_msg, EFilterType::Circle, mRadius);

}

UAbsFilter* UCircleFilter::Clone()
{
	return CreateFilter(mKey);
}

void UCircleFilter::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 3)
	{
		mSelectType = FCString::Atoi(*_params[0]);
		mCount = FCString::Atoi(*_params[1]);
		mRadius = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- UCircleFilter::Parser, _params.Num() = %d"), _params.Num());
	}
}

UCircleFilter* UCircleFilter::CreateFilter(const FString& _key)
{
	UCircleFilter* circleFilter = NewObject<UCircleFilter>(UCircleFilter::StaticClass());
	circleFilter->SetKey(_key);
	return circleFilter;
}
