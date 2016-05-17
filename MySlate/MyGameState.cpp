#include "MySlate.h"
#include "MyGameState.h"

#include "./GameUtils.h"
#include "./GameState/GSInit.h"
#include "./GameState/GSLoading.h"
#include "./GameState/GSMainCity.h"
#include "./GameState/GSBattle.h"

AMyGameState::AMyGameState()
{
	mWarmupTime = 3.f;
	mState = EGameplayState::None;
	mCurrState = nullptr;
}

AMyGameState::~AMyGameState()
{
	for (IGameStateInterface* gameState : mGameStateVec)
	{
		UObject* obj = Cast<UObject>(gameState);
		if (obj)
		{
			obj->RemoveFromRoot();
			obj->ConditionalBeginDestroy();
		}
	}
	mGameStateVec.Empty();
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

void AMyGameState::SetGameplayState(EGameplayState _state)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyGameState::Tick, state = %s"), *GetEnumAsString("EGameplayState", _state));
	mState = _state;
}

void AMyGameState::StartGame()
{
	UObject* gs = nullptr;
	gs = NewObject<UGameStateInit>(this, UGameStateInit::StaticClass());
	gs->AddToRoot();
	mGameStateVec.Add(Cast<IGameStateInterface>(gs));

	gs = NewObject<UGameStateLoading>(this, UGameStateLoading::StaticClass());
	gs->AddToRoot();
	mGameStateVec.Add(Cast<IGameStateInterface>(gs));

	gs = NewObject<UGameStateMainCity>(this, UGameStateMainCity::StaticClass());
	gs->AddToRoot();
	mGameStateVec.Add(Cast<IGameStateInterface>(gs));

	gs = NewObject<UGameStateBattle>(this, UGameStateBattle::StaticClass());
	gs->AddToRoot();
	mGameStateVec.Add(Cast<IGameStateInterface>(gs));

	ChangeGameState(EGameState::Init);
}

IGameStateInterface* AMyGameState::GetGameState(EGameState _state)
{
	IGameStateInterface** gameState = mGameStateVec.FindByPredicate([&](const IGameStateInterface* _gameState)->bool {
		return _state == _gameState->GetGameState();
	});
	return gameState != nullptr ? *gameState : nullptr;
}

void AMyGameState::ChangeGameState(EGameState _nextState)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyGameState::ChangeGameState, state = %s"), *GetEnumAsString("EGameState", _nextState));

	IGameStateInterface* nextState = GetGameState(_nextState);
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
