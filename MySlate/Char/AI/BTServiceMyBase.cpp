#include "MySlate.h"
#include "BTServiceMyBase.h"

#include "Char/MyChar.h"
#include "Char/CharMgr.h"
#include "Char/MyCharDataComp.h"
#include "Char/AI/MyAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

UBTServiceMyBase::UBTServiceMyBase() : Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;

	//设置每帧tick
	bNotifyTick = 1;
}

UBTServiceMyBase::~UBTServiceMyBase()
{

}

void UBTServiceMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

void UBTServiceMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	mBTComp = &OwnerComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

void UBTServiceMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

AMyChar * UBTServiceMyBase::GetCloestEnemy()
{
	TArray<AMyChar*> searchArr;
	if (mOwnerChar)
	{
		if (mOwnerChar->mDataComp->mTeam == ETeam::Enemy)
		{
			searchArr = UCharMgr::GetInstance()->mTeamCharArr;
		}
		else if (mOwnerChar->mDataComp->mTeam == ETeam::Teammate)
		{
			searchArr = UCharMgr::GetInstance()->mEnemyCharArr;
		}

		AMyChar* closetOne = nullptr; //找出最近的敌人
		float BestDistSq = MAX_FLT;
		for (int32 i = 0; i < searchArr.Num(); ++i)
		{
			AMyChar* enemy = searchArr[i];
			if (enemy->IsAlive())
			{
				const float DistSq = (enemy->GetActorLocation() - mOwnerChar->GetActorLocation()).Size();
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					closetOne = enemy;
				}
			}
		}

		return closetOne;
	}
	return nullptr;
}

