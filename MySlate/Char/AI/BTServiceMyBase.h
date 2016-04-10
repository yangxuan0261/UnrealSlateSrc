#pragma once

#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTServiceMyBase.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

// Bot AI task that tries to find a location near the current enemy
UCLASS(Blueprintable)
class UBTServiceMyBase : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTServiceMyBase();
	virtual ~UBTServiceMyBase();

	//UBTAuxiliaryNode Interface Begin 
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//UBTAuxiliaryNode Interface End 

	//UBTAuxiliaryNode Interface Begin 
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	//UBTAuxiliaryNode Interface End 

public:
	UFUNCTION(BlueprintCallable, Category = "UBTServiceMyBase")
		AMyChar*	GetCloestEnemy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTServiceMyBase")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTServiceMyBase")
		AMyAIController*	mOwnerAI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTServiceMyBase")
		UBehaviorTreeComponent*	mBTComp;
};