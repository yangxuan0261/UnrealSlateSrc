// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GolbalFunc.generated.h"

class USkillDataMgr;
class USkillMgr;
class UCoolDownMgr;

UCLASS()
class UGolbalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UGolbalFunc();
	virtual ~UGolbalFunc();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillDataMgr*		GetSkillDataMgr() { return gSkillDataMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillMgr*			GetSkillMgr() { return gSkillMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UCoolDownMgr*		GetCoolDownMgr() { return gCoolDownMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static int32				TestSingleton();

private:
	static USkillDataMgr*			gSkillDataMgr;
	static USkillMgr*				gSkillMgr;
	static UCoolDownMgr*			gCoolDownMgr;
};
