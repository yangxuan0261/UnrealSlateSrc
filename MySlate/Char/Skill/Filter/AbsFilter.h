// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS(Abstract)
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();

	virtual void filter(UPkMsg* msg);//过虑可选actor
	virtual UAbsFilter* clone();
	virtual void paser(TArray<FString> _params);//解释数据

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mFilterKey;

};
