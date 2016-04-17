// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsPkEvent.h"

UAbsPkEvent::UAbsPkEvent() : Super()
{
	mKey = "";
	mIsPercent = false;
}

UAbsPkEvent::~UAbsPkEvent()
{

}

bool UAbsPkEvent::CheckPercent(const FString& _value)
{
	mIsPercent = _value.Contains(TEXT("%"));
	return mIsPercent;
}
