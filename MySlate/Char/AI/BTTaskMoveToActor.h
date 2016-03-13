#pragma once
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BTTaskMoveToActor.generated.h"

// Bot AI task that tries to find a location near the current enemy
UCLASS()
class UBTTaskMoveToActor : public UBTTask_BlackboardBase
{
	GENERATED_UCLASS_BODY()
public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};