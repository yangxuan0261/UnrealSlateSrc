#pragma once

#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BTServiceMyBase.generated.h"

class AMyChar;

// Bot AI task that tries to find a location near the current enemy
UCLASS(Blueprintable)
class UBTServiceMyBase : public UBTService_BlueprintBase
{
	GENERATED_BODY()
public:
	UBTServiceMyBase();
	virtual ~UBTServiceMyBase();

public:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UBTServiceMyBase")
		AMyChar*	GetMyChar();
	UFUNCTION(BlueprintCallable, Category = "UBTServiceMyBase")
		AMyChar*	GetCloestEnemy();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTServiceMyBase")
		AMyChar*	mOwnerChar;
};