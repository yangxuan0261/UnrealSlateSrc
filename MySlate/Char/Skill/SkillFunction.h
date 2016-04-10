// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillFunction.generated.h"

UCLASS()
class USkillFunction : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillFunction();
	virtual ~USkillFunction();

public:
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual void Tick(float DeltaSeconds);
};
