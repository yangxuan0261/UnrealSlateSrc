#include "MySlate.h"
#include "BTServiceMyBase.h"

#include "../MyChar.h"
#include "../CharMgr.h"
#include "../Comp/MyCharDataComp.h"
#include "./MyAIController.h"

UBTServiceMyBase::UBTServiceMyBase() : Super(), IBTNodeInterface()
{
	//设置每帧tick
	bNotifyTick = 1;
}

UBTServiceMyBase::~UBTServiceMyBase()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTServiceMyBase::~UBTServiceMyBase"));
}

void UBTServiceMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

void UBTServiceMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	IBTNodeInterface::InitData(&OwnerComp);
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
			searchArr = gGetCharMgr()->mTeamCharArr;
		}
		else if (mOwnerChar->mDataComp->mTeam == ETeam::Teammate)
		{
			searchArr = gGetCharMgr()->mEnemyCharArr;
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

