#pragma once

#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "BTTaskMyBase.generated.h"

class AMyChar;
class UBehaviorTreeComponent;

// Bot AI task that tries to find a location near the current enemy
UCLASS(Blueprintable)
class UBTTaskMyBase : public UBTTask_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTTaskMyBase();
	virtual ~UBTTaskMyBase();

	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	//UBTAuxiliaryNode Interface Begin 
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	//UBTAuxiliaryNode Interface End 

	UFUNCTION(BlueprintCallable, Category = "UBTTaskMyBase")
		bool		MoveToTarget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTTaskMyBase")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTTaskMyBase")
		AMyAIController*	mOwnerAI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTTaskMyBase")
		UBehaviorTreeComponent*	mBTComp;

};