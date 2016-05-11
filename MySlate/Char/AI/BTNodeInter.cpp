#include "MySlate.h"
#include "BTNodeInter.h"

#include "../MyChar.h"
#include "./MyAIController.h"

UBTNodeInterface::UBTNodeInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

IBTNodeInterface::IBTNodeInterface()
{
	mOwnerChar = nullptr;
	mAICtrl = nullptr;
	mBTComp = nullptr;
}

void IBTNodeInterface::InitData(UBehaviorTreeComponent* _BTComp)
{
	mBTComp = _BTComp;
	mAICtrl = mBTComp != nullptr ? Cast<AMyAIController>(_BTComp->GetOwner()) : nullptr;
	mOwnerChar = mAICtrl != nullptr ? Cast<AMyChar>(mAICtrl->GetPawn()) : nullptr;
}