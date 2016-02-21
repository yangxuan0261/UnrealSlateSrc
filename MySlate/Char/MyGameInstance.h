// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYSLATE_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	/** Increment this value in any map, change map, and notice it persists! */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = UMyGameInstance)
		int32 InterLevelPersistentValue;

	//loading test
	//virtual void Init() override;

	//UFUNCTION()W
	//	virtual void MyBeginLoadingScreen();
	//UFUNCTION()
	//	virtual void MyEndLoadingScreen();
};
