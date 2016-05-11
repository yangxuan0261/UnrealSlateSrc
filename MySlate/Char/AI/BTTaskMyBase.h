#pragma once

#include "./BTNodeInter.h"
#include "BTTaskMyBase.generated.h"

class AMyChar;
class UBehaviorTreeComponent;

UCLASS(Blueprintable)
class UBTTaskMyBase : public UBTTask_BlueprintBase, public IBTNodeInterface
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

	UFUNCTION(BlueprintCallable, Category = "UBTTaskMyBase")
		AMyChar*	GetChar() const { return mOwnerChar; }
public:

};