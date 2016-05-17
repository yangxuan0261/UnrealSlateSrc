#include "MySlate.h"
#include "GSInter.h"

#include "../MyGameState.h"

UGameStateInterface::UGameStateInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

IGameStateInterface::IGameStateInterface()
{
	mGameState = EGameState::None;
	mOwner = nullptr;
	mGameStateMgr = nullptr;
}

AMyGameState* IGameStateInterface::GetMyGameState()
{
	if (mGameStateMgr == nullptr)
	{
		if (mOwner != nullptr)
		{
			return Cast<AMyGameState>(mOwner->GetOuter());
		}
	}

	return nullptr;
}
