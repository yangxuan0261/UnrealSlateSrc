#include "MySlate.h"
#include "MyAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "Engine.h"
#include "../MyChar.h"

DECLARE_LOG_CATEGORY_EXTERN(AMyAILogger, Log, All);
DEFINE_LOG_CATEGORY(AMyAILogger)

AMyAIController::AMyAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

AMyAIController::~AMyAIController()
{
	UE_LOG(AMyAILogger, Warning, TEXT("--- UCoolDownComp::~AMyAIController"));
}

void AMyAIController::GameHasEnded(AActor * EndGameFocus, bool bIsWinner)
{
	// Stop the behaviour tree/logic
	//BehaviorComp->StopTree();
}

void AMyAIController::Possess(APawn * InPawn)
{
	Super::Possess(InPawn);

	AMyChar* myChar = Cast<AMyChar>(InPawn);



		
}

void AMyAIController::BeginInactiveState()
{
	Super::BeginInactiveState();
}

bool AMyAIController::FindClosestEnemy()
{
	AMyChar* mySelf = Cast<AMyChar>(GetPawn());
	if (!mySelf)
		return false;

	const FVector myLoc = mySelf->GetActorLocation();
	float BestDistSq = MAX_FLT;
	AMyChar * bestTarget = nullptr;

	for (FConstPawnIterator iter = GetWorld()->GetPawnIterator(); iter; ++iter)
	{
		AMyChar* tmpTarget = Cast<AMyChar>(*iter);
		if (tmpTarget != mySelf)
		{
			if (tmpTarget)
			{
				const float DistSq = (tmpTarget->GetActorLocation() - myLoc).SizeSquared();
				if (DistSq < BestDistSq)
				{
					BestDistSq = DistSq;
					bestTarget = tmpTarget;
					FString str = FString::Printf(TEXT("--- find enemy dist:%f"), BestDistSq);
					GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, str);
				}
			}
		}
	}

	if (bestTarget)
	{
		return SetEnemy(bestTarget);
	}
	return false;
}

bool AMyAIController::SetEnemy(APawn * InPawn)
{
	//if (BlackboardComp)
	//{
	//	return BlackboardComp->SetValue<UBlackboardKeyType_Object>(EnemyKeyID, InPawn);
	//}
	return false;
}

APawn * AMyAIController::GetEnemy() const
{
	//if (BlackboardComp)
	//{
	//	return Cast<APawn>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
	//}
	return nullptr;
}

