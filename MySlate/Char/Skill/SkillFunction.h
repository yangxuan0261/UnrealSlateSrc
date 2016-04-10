// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.h"
#include "SkillFunction.generated.h"

class USkillTemplate;

UCLASS()
class USkillFunction : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillFunction();
	virtual ~USkillFunction();


public:
	UFUNCTION(BlueprintCallable, Category = "USkillFunction")
		virtual void Tick(float DeltaSeconds);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		USkillTemplate*		mSkillTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillFunction")
		ESkillType	mType;
};
