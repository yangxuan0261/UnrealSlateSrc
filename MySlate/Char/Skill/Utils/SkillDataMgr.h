// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"

#include "SkillDataMgr.generated.h"

UCLASS()
class USkillDataMgr : public UObject, public USingleton<USkillDataMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillDataMgr();
	virtual ~USkillDataMgr();

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void		SetTestNum(int32 _num) { mTestNum = _num; }
	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		int32		GetTestNum() { return mTestNum;}

private:
	int32		mTestNum;
};
