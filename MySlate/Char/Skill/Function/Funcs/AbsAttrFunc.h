// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsAttrFunc.generated.h"

UCLASS()
class UAbsAttrFunc : public UObject
{
	GENERATED_BODY()

public:
	

public:
	UAbsAttrFunc();
	virtual ~UAbsAttrFunc();
	virtual void BeginDestroy() override;

	virtual void RunFunc() {}
};
