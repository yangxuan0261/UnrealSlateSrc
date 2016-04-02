#include "MySlate.h"
#include "BTServiceMyBase.h"

#include "Char/AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/CharMgr.h"
#include "Char/MyCharDataComp.h"

UBTServiceMyBase::UBTServiceMyBase() : Super()
{
	mOwnerChar = nullptr;
}

UBTServiceMyBase::~UBTServiceMyBase()
{

}

void UBTServiceMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!mOwnerChar)
	{
		mOwnerChar = GetMyChar();
	}

}

AMyChar* UBTServiceMyBase::GetMyChar()
{
	AMyChar* myChar = Cast<AMyChar>(AIOwner->GetPawn());
	return myChar != nullptr ? myChar : nullptr;
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

