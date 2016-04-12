// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircleFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class UCircleFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCircleFilter();
	virtual ~UCircleFilter();

	virtual void filter(UPkMsg* msg);
	virtual UAbsFilter* clone();
	virtual void paser(TArray<FString> _params);

public:
	int32		mType;
	int32		mCount;
	int32		mRadius;
};
