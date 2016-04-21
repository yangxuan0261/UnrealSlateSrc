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
	ULockFilter();
	virtual ~ULockFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* msg) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static ULockFilter* CreateFilter(const FString& _key);

public:
	int32		mType; //1¼º·½£¬-1µÐ·½
};
