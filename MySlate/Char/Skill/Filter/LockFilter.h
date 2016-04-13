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

	virtual void Filter(UPkMsg* msg) override;
	virtual UAbsFilter* Clone() override;
	virtual void Paser(const TArray<FString>& _params);

	static ULockFilter* CreateFilter(const FString& _key);

public:
	int32		mType; //1¼º·½£¬-1µÐ·½
};
