// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"

#include "SkillDataMgr.generated.h"

class USkillTemplate;
class UBufflTemplate;

UCLASS()
class USkillDataMgr : public UObject, public USingleton<USkillDataMgr>
{
	GENERATED_BODY()

public:
	USkillDataMgr();
	virtual ~USkillDataMgr();

public:
	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void				InitFakeDate();

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		USkillTemplate*		GetSkillTemplate(int32 _skillId);
	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		UBufflTemplate*		GetBuffTemplate(int32 _buffId);

private:
	TMap<int32, USkillTemplate*>	mSkillTempMap;
	TMap<int32, UBufflTemplate*>	mBuffTempMap;
};
