#include "MySlate.h"
#include "BTTaskMoveToActor.h"

#include "MyAIController.h"

UBTTaskMoveToActor::UBTTaskMoveToActor()
	: Super()
{
}


UBTTaskMoveToActor::~UBTTaskMoveToActor()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTTaskMoveToActor::~UBTTaskMoveToActor"));
}

EBTNodeResult::Type UBTTaskMoveToActor::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AMyAIController* MyController = Cast<AMyAIController>(OwnerComp.GetAIOwner());
	if (MyController == nullptr)
		return EBTNodeResult::Failed;

	APawn* Enemy = MyController->GetEnemy();
	if (Enemy)
	{
		MyController->MoveToActor(Enemy);
		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
