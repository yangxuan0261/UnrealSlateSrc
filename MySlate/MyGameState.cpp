#include "MySlate.h"
#include "MyGameState.h"

#include "./GameState/GSInit.h"
#include "./GameState/GSLoading.h"
#include "./GameState/GSMainCity.h"
#include "./GameState/GSBattle.h"

AMyGameState::AMyGameState()
{
	mWarmupTime = 3.f;
	mCurrState = nullptr;
}

AMyGameState::~AMyGameState()
{

}

void AMyGameState::Tick(float DeltaTime)
{
	if (mCurrState != nullptr)
	{
		mCurrState->OnTick(DeltaTime);
	}
}

bool AMyGameState::IsTickable() const
{
	return true;
}

TStatId AMyGameState::GetStatId() const
{
	return TStatId();
}

void AMyGameState::StartGame()
{
	mGameStateVec.Add(NewObject<UGameStateInit>(this, UGameStateInit::StaticClass()));
	mGameStateVec.Add(NewObject<UGameStateLoading>(this, UGameStateLoading::StaticClass()));
	mGameStateVec.Add(NewObject<UGameStateMainCity>(this, UGameStateMainCity::StaticClass()));
	mGameStateVec.Add(NewObject<UGameStateBattle>(this, UGameStateBattle::StaticClass()));

	ChangeGameState(EGameState::Init);
}

UGameStateBase* AMyGameState::GetGameState(EGameState _state)
{
	UGameStateBase** gameState = mGameStateVec.FindByPredicate([&](const UGameStateBase* _gameState)->bool {
		return _state == _gameState->GetGameState();
	});
	return gameState != nullptr ? *gameState : nullptr;
}

void AMyGameState::ChangeGameState(EGameState _nextState)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyGameState::ChangeGameState, state = %s"), *GetEnumAsString("EGameState", _nextState));

	UGameStateBase* nextState = GetGameState(_nextState);
	if (nextState != nullptr)
	{
		if (nextState != mCurrState)
		{
			if (mCurrState != nullptr)
			{
				mCurrState->OnExitState();
			}

			nextState->OnEnterState();
			mCurrState = nextState;
		}
	}
}
