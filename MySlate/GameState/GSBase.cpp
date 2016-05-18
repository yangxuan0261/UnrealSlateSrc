#include "MySlate.h"
#include "GSBase.h"

#include "../MyGameState.h"

UGameStateBase::UGameStateBase() : Super()
{
	mGameState = EGameState::None;
	mGameStateMgr = nullptr;
}

UGameStateBase::~UGameStateBase()
{

}

AMyGameState* UGameStateBase::GetMyGameState()
{
	if (mGameStateMgr == nullptr)
	{
		mGameStateMgr = Cast<AMyGameState>(GetOuter());
	}

	return mGameStateMgr;
}
