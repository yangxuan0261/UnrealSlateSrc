
#include "MySlate.h"
#include "GSLoading.h"

#include "./MyGameState.h"

UGameStateLoading::UGameStateLoading() : Super(), IGameStateInterface()
{
	IGameStateInterface::SetObj(this);
	mGameState = EGameState::Loading;
}

void UGameStateLoading::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGameStateLoading::OnEnterState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateLoading::OnEnterState 11"));
}

void UGameStateLoading::OnExitState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateLoading::OnExitState 22"));
}

void UGameStateLoading::OnTick(float DeltaSeconds)
{
	GetMyGameState()->ChangeGameState(EGameState::MainCity);
}
