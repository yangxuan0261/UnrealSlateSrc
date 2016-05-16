// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class MYSLATE_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMyGameMode();
	virtual ~AMyGameMode();
	/**
	* Handle new player, skips pawn spawning.
	* @param NewPlayer
	*/
	virtual void RestartPlayer(AController* NewPlayer) override;

public:
	UFUNCTION(Exec)
		virtual void solspeed();

	UFUNCTION(Exec)
		virtual void solname(FString _str, int32 _num);
};
