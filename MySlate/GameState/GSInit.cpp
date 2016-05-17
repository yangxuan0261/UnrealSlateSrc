
#include "MySlate.h"
#include "GSInit.h"

#include "./MyGameState.h"

UGameStateInit::UGameStateInit() : Super() , IGameStateInterface()
{
	IGameStateInterface::SetObj(this);
	mGameState = EGameState::Init;
}

void UGameStateInit::BeginDestroy()
{
	Super::BeginDestroy();
}

void UGameStateInit::OnEnterState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateInit::OnEnterState 11"));
}

void UGameStateInit::OnExitState()
{
	UE_LOG(GameLogger, Warning, TEXT("--- UGameStateInit::OnExitState 22"));
}

void UGameStateInit::OnTick(float DeltaSeconds)
{
	GetMyGameState()->ChangeGameState(EGameState::Loading);
}
