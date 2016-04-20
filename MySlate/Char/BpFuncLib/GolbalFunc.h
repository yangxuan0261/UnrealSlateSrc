// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GolbalFunc.generated.h"

class USkillDataMgr;
class USkillMgr;
class UCharMgr;
class UFuncFactory;
class UBaseDataMgr;
class UBuffMgr;
class AMyChar;

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

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestStrContains(FString _str);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestFilter(AMyChar* _actor, float _radius);

private:
	static USkillDataMgr*			gSkillDataMgr;
	static USkillMgr*				gSkillMgr;
	static UCharMgr*				gCharMgr;
	static UFuncFactory*			gFunctionMgr;
	static UBaseDataMgr*			gBaseDataMgr;
	static UBuffMgr*				gBuffMgr;

};
