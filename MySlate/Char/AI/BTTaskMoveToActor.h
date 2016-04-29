#pragma once

#include "BTTaskMoveToActor.generated.h"

UCLASS()
class UBTTaskMoveToActor : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBTTaskMoveToActor();
	virtual ~UBTTaskMoveToActor();

public:
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};