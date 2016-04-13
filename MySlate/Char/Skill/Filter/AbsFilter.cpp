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

void UAbsFilter::Filter(UPkMsg* msg)
{

}

UAbsFilter * UAbsFilter::Clone()
{
	return nullptr;
}

void UAbsFilter::Paser(const TArray<FString>& _params)
{

}
