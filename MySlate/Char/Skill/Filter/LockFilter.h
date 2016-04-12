// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "LockFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class ULockFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ULockFilter();
	virtual ~ULockFilter();

	virtual void filter(UPkMsg* msg);
	virtual UAbsFilter* clone();
	virtual void paser(TArray<FString> _params);

public:
	int32		mType; //1¼º·½£¬-1µÐ·½
};
