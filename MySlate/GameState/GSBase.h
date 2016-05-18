
#pragma once

#include "GSBase.generated.h"

class AMyGameState;

UENUM()
enum class EGameState : uint8 //游戏的各种状态
{
	None = 0,
	Init,
	Connect,
	Loading,
	MainCity,
	Battle,
	Count,
};

UCLASS()
class UGameStateBase : public UObject
{
	GENERATED_BODY()
public:
	UGameStateBase();
	virtual ~UGameStateBase();

public:
	virtual	void	OnEnterState() {}
	virtual	void	OnExitState() {}
	virtual void	OnTick(float DeltaSeconds) {}

	EGameState	GetGameState() const { return mGameState; }
	AMyGameState*	GetMyGameState();
protected:
	EGameState		mGameState;
	AMyGameState*	mGameStateMgr;
};