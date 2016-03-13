#include "MySlate.h"
#include "BTTaskMoveToActor.h"

#include "MyAIController.h"

UBTTaskMoveToActor::UBTTaskMoveToActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
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
