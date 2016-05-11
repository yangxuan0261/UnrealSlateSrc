#pragma once

#include "./BTNodeInter.h"
#include "BTServiceMyBase.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

UCLASS(Blueprintable)
class UBTServiceMyBase : public UBTService_BlueprintBase, public IBTNodeInterface
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

	UFUNCTION(BlueprintCallable, Category = "UBTServiceMyBase")
		AMyChar*	GetChar() const { return mOwnerChar; }
public:

};