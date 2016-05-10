// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsPkEvent.h"

UAbsPkEvent::UAbsPkEvent() : Super()
{
	
}

UAbsPkEvent::~UAbsPkEvent()
{

}

void UAbsPkEvent::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsPkEvent::Reset()
{
	Super::Reset();
	mKey = "";
	mIsPercent = false;
}

bool UAbsPkEvent::CheckPercent(const FString& _value)
{
	mIsPercent = _value.Contains(TEXT("%"));
	return mIsPercent;
}
