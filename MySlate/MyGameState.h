
#pragma once

#include "Tickable.h"
#include "./GameState/GSBase.h"
#include "MyGameState.generated.h"

/*
µÈ¼ÛÓÚGameStateManager
*/

UCLASS()
class AMyGameState : public AGameState, public FTickableGameObject
{
	GENERATED_BODY()
public:
	AMyGameState();
	virtual ~AMyGameState();

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:
	void		StartGame();
	UGameStateBase*	GetGameState(EGameState _state);
	void		ChangeGameState(EGameState _nextState);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyGameState")
		TArray<UGameStateBase*>	mGameStateVec;

private:
	UGameStateBase*	mCurrState;
	float			mWarmupTime;
	FTimerHandle	mWarmTimeHandler;

};


