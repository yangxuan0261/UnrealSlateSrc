// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"
#include "Char/Skill/SkillTypes.h"

#include "SkillTemplate.generated.h"

class UAbsPkEvent;
class UAbsFilter;


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
	const TArray<UAbsPkEvent*>& GetBeforePk();
	const TArray<UAbsPkEvent*>& GetBeforeSkill();
	const TArray<UAbsPkEvent*>& GetBeforeEvns();
	const TArray<UAbsPkEvent*>& GetEndEvns();
	const TArray<UAbsPkEvent*>& GetEndSkill();
	const TArray<UAbsPkEvent*>& GetEndPk();

public:
	TArray<UAbsPkEvent*> mBeforeSkillEvns;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mBeforeEvns;
	TArray<UAbsPkEvent*> mEndEvns;
	TArray<UAbsPkEvent*> mEndPk;
	TArray<UAbsPkEvent*> mEndSkillEvns;
	FString beforeSkillStr;
	FString beforeEvnsStr;
	FString endEvnsStr;
	FString pkBeforeStr;
	FString pkEndStr;
	FString endSkillStr;

public:
	//∂¡±Ì Ù–‘
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mAttackDist;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		ESkillType		mSkillType;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mfilter;
};
