// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsFilter.h"

UAbsFilter::UAbsFilter()
{
	mKey = "";
}

UAbsFilter::~UAbsFilter()
{

}

void UAbsFilter::filter(UPkMsg* msg)
{

}

UAbsFilter * UAbsFilter::clone()
{
	return nullptr;
}

void UAbsFilter::paser(TArray<FString> _params)
{

}
