
#pragma once

#include "Tickable.h"
#include "./GameState/GSInter.h"
#include "MyGameState.generated.h"

UENUM()
enum class EGameplayState : uint8 //游戏状态
{
	None = 0,
	Start,
	Waiting,
	Playing,
	Finished,
	Count,
};

/*
等价于GameStateManager
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
	void		SetGameplayState(EGameplayState _state);
	void		StartGame();
	IGameStateInterface*	GetGameState(EGameState _state);
	void		ChangeGameState(EGameState _nextState);

public:
	//UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyGameState")
	//TArray<TScriptInterface<IGameStateInterface>>	mGameStateVec;
	TArray<IGameStateInterface*>	mGameStateVec;

private:
	IGameStateInterface*	mCurrState;

	EGameplayState	mState;
	float			mWarmupTime;
	FTimerHandle	mWarmTimeHandler;

};


