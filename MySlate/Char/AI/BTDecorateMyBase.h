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