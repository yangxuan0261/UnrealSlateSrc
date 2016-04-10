#pragma once

#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BTDecorateMyBase.generated.h"

class AMyChar;
class UBehaviorTreeComponent;

// Bot AI task that tries to find a location near the current enemy
UCLASS(Blueprintable)
class UBTDecorateMyBase : public UBTDecorator_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTDecorateMyBase();
	virtual ~UBTDecorateMyBase();

	//virtual void OnNodeActivation(FBehaviorTreeSearchData& SearchData);

	///** called when underlying node has finished
	//* this function should be considered as const (don't modify state of object) if node is not instanced! */
	//virtual void OnNodeDeactivation(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type NodeResult);

	///** called when underlying node was processed (deactivated or failed to activate)
	//* this function should be considered as const (don't modify state of object) if node is not instanced! */
	//virtual void OnNodeProcessed(FBehaviorTreeSearchData& SearchData, EBTNodeResult::Type& NodeResult);

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		AMyChar*	GetMyChar();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		UBehaviorTreeComponent*	GetBTComp();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		bool		CanUseSkill();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		void		UseSkill();
	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		bool		IsAttackRange();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTDecorateMyBase")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTDecorateMyBase")
		UBehaviorTreeComponent*	mBTComp;
};