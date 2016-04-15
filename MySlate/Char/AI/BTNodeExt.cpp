#include "MySlate.h"
#include "BTNodeExt.h"

#include "Char/MyChar.h"
#include "Char/AI/MyAIController.h"

UBTNodeExt::UBTNodeExt() : Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;
}

UBTNodeExt::~UBTNodeExt()
{

}

void UBTNodeExt::InitData(UBehaviorTreeComponent* _BTComp)
{
	mBTComp = _BTComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

