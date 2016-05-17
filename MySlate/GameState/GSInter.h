
#pragma once

#include "GSInter.generated.h"

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

UINTERFACE()
class UGameStateInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IGameStateInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IGameStateInterface();

public:
	virtual	void	OnEnterState() {}
	virtual	void	OnExitState() {}
	virtual void	OnTick(float DeltaSeconds) = 0;

	void		SetObj(UObject* _obj) { mOwner = _obj; }
	EGameState	GetGameState() const { return mGameState; }
	AMyGameState*	GetMyGameState();
protected:
	UObject*		mOwner;
	EGameState		mGameState;
	AMyGameState*	mGameStateMgr;
};