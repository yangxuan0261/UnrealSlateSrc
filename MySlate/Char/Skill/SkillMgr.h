// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"
#include "Tickable.h"

#include "SkillMgr.generated.h"

class UBehaviorData;

UCLASS()
class USkillMgr : public UObject, public FTickableGameObject, public USingleton<USkillMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillMgr();
	virtual ~USkillMgr();

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:
	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		UBehaviorData* GetBehaviorData(int32 _id);

private:
	UBehaviorData* LoadBehaviorData(int32 _id);

private:
	float		mCounter;

	TMap<int32, UBehaviorData*>		mBehaviorDataMap;//存放技能数据
};
