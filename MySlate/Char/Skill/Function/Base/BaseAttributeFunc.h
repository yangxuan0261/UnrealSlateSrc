// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Func.h"
#include "BaseAttributeFunc.generated.h"

UCLASS()
class UBaseAttributeFunc : public UFunc
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UBaseAttributeFunc();
	virtual ~UBaseAttributeFunc();


	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;
};
