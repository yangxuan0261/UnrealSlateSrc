// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"

#include "SkillTemplate.generated.h"

UCLASS()
class USkillTemplate : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillTemplate();
	virtual ~USkillTemplate();

public:
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	int32			GetId() { return mId; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetName() { return mName; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetDescr() { return mDescr; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	float			GetCoolDown() { return mCoolDown; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mCoolDown;

	//GetSetProperty(mDescr, Descr, USkillTemplate);
	//GetSetProperty(mCoolDown, CoolDown, USkillTemplate);
};
