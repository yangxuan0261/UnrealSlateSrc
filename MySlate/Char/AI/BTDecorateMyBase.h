#pragma once

#include "./BTNodeInter.h"
#include "BTDecorateMyBase.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

// Bot AI task that tries to find a location near the current enemy
UCLASS(Blueprintable)
class UBTDecorateMyBase : public UBTDecorator_BlueprintBase, public IBTNodeInterface
{
	GENERATED_BODY()
public:
	UBTDecorateMyBase();
	virtual ~UBTDecorateMyBase();

	//UBTAuxiliaryNode Interface Begin 
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	//UBTAuxiliaryNode Interface End 

	//UBTAuxiliaryNode Interface Begin 
	virtual void OnInstanceCreated(UBehaviorTreeComponent& OwnerComp) override;
	virtual void OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp) override;
	//UBTAuxiliaryNode Interface End 

public:
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		bool		CanUseSkill();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		void		UseSkill();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		bool		IsAttackRange();

	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		AMyChar*	GetChar() const { return mOwnerChar; }
public:

};