
#pragma once

#include "MyGameMode.generated.h"

UCLASS()
class AMyGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	AMyGameMode();
	virtual ~AMyGameMode();

	/** Transitions to WaitingToStart and calls BeginPlay on actors. */
	virtual void StartPlay() override;

	virtual void InitGameState() override;
	/**
	* Handle new player, skips pawn spawning.
	* @param NewPlayer
	*/
	virtual void RestartPlayer(AController* NewPlayer) override;

	/** Restart the game, by default travel to the current map */
	virtual void RestartGame() override;

	virtual void BeginDestroy() override;

public:
	UFUNCTION(Exec)
		virtual void solspeed();

	UFUNCTION(Exec)
		virtual void solname(FString _str, int32 _num);
};
