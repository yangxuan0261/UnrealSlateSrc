
#include "MySlate.h"
#include "GSBattle.h"

#include "./MyGameState.h"

UGameStateBattle::UGameStateBattle() : Super(), IGameStateInterface()
{
	IGameStateInterface::SetObj(this);
	mGameState = EGameState::Battle;
	mFlag = false;
}

void UGameStateBattle::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGameStateBattle::OnEnterState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateBattle::OnEnterState 11"));
}

void UGameStateBattle::OnExitState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateBattle::OnExitState 22"));
}

void UGameStateBattle::OnTick(float DeltaSeconds)
{
	if (!mFlag)
	{
		UE_LOG(GameLogger, Warning, TEXT("--- UGameStateBattle::OnTick, dt:%f"), DeltaSeconds);
		mFlag = !mFlag;
	}
}
