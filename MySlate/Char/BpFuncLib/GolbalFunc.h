// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GolbalFunc.generated.h"

class USkillDataMgr;
class USkillMgr;
class UCharMgr;
class UFunctionFactory;

UCLASS()
class UGolbalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UGolbalFunc();
	virtual ~UGolbalFunc();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					InitMgrs();
	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					DestroyMgrs();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillDataMgr*		GetSkillDataMgr() { return gSkillDataMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillMgr*			GetSkillMgr() { return gSkillMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UCharMgr*			GetCharMgr() { return gCharMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TurnForward(AActor* _actor, const FVector& _targetLoc);

	//--------------- test function
	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestStrSplit();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestForceGC();
		
private:
	static USkillDataMgr*			gSkillDataMgr;
	static USkillMgr*				gSkillMgr;
	static UCharMgr*				gCharMgr;
	static UFunctionFactory*		gFunctionMgr;
};
