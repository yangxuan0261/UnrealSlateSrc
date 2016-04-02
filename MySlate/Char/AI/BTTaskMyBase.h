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

public:
	UFUNCTION(BlueprintCallable, Category = "UBTTaskMyBase")
		AMyChar*	GetMyChar();
	UFUNCTION(BlueprintCallable, Category = "UBTTaskMyBase")
		UBehaviorTreeComponent*	GetBTComp();
	UFUNCTION(BlueprintCallable, Category = "UBTTaskMyBase")
		bool		MoveToTarget();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTTaskMyBase")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTTaskMyBase")
		UBehaviorTreeComponent*	mBTComp;


};