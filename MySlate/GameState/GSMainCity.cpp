
#include "MySlate.h"
#include "GSMainCity.h"

#include "./MyGameState.h"

UGameStateMainCity::UGameStateMainCity() : Super(), IGameStateInterface()
{
	IGameStateInterface::SetObj(this);
	mGameState = EGameState::MainCity;
}

void UGameStateMainCity::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGameStateMainCity::OnEnterState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateMainCity::OnEnterState 11"));
}

void UGameStateMainCity::OnExitState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateMainCity::OnExitState 22"));
}

void UGameStateMainCity::OnTick(float DeltaSeconds)
{
	GetMyGameState()->ChangeGameState(EGameState::Battle);
}
