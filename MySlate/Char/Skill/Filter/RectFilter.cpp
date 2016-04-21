// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "RectFilter.h"

#include "../Pk/PkMsg.h"
#include "Char/MyChar.h"

URectFilter::URectFilter() : Super()
{
	mBoxSize = FVector(0.f, 0.f, 0.f);
}

URectFilter::~URectFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- URectFilter::~URectFilter"));
}
 
void URectFilter::BeginDestroy()
{

	UE_LOG(FilterLogger, Warning, TEXT("--- URectFilter::BeginDestroy"));
	Super::BeginDestroy();
}

void URectFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector(0.f, 0.f, 0.f) */)
{
	Super::Filter(_msg, EFilterType::Circle, 0.f, mBoxSize);

}

UAbsFilter* URectFilter::Clone()
{
	return CreateFilter(mKey);
}

void URectFilter::Parser(const TArray<FString>& _params)
{

	if (_params.Num() == 5)
	{
		mSelectType = FCString::Atoi(*_params[0]);
		mCount = FCString::Atoi(*_params[1]);
		mBoxSize.X = FCString::Atof(*_params[2]);
		mBoxSize.Y = FCString::Atof(*_params[2]);
		mBoxSize.Z = FCString::Atof(*_params[2]);
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- URectFilter::Parser, _params.Num() = %d"), _params.Num());
	}
}

URectFilter* URectFilter::CreateFilter(const FString& _key)
{
	URectFilter* circleFilter = NewObject<URectFilter>(URectFilter::StaticClass());
	circleFilter->SetKey(_key);
	return circleFilter;
}
