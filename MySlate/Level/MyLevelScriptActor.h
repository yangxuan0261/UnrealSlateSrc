// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/LevelScriptActor.h"
#include "MyLevelScriptActor.generated.h"

/**
 * 
 */
UCLASS()
class MYSLATE_API AMyLevelScriptActor : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaSeconds) override;

public:
	AMyLevelScriptActor();

	UFUNCTION(BlueprintCallable, Category = "Solus Level Save System")
		void SolusLevel_UpdateLevelSaveData();

	/** A Custom name for each Solus Level, specified in Level BP Default Properties! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = SolusLevel)
		FName SolusLevelName;

	int32 Counter;
	
};
