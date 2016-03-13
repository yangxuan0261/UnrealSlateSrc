#pragma once
#include "AIController.h"
#include "MyAIController.generated.h"

class UBehaviorTreeComponent;
class UBlackboardComponent;

UCLASS()
class AMyAIController : public AAIController
{
	GENERATED_UCLASS_BODY()
private:
	UPROPERTY(transient)
		UBlackboardComponent* BlackboardComp;

	/* Cached BT component */
	UPROPERTY(transient)
		UBehaviorTreeComponent* BehaviorComp;

protected:
	int32 EnemyKeyID;
	int32 NeedAmmoKeyID;

public:
	// Begin AController interface
	virtual void GameHasEnded(class AActor* EndGameFocus = NULL, bool bIsWinner = false) override;
	virtual void Possess(class APawn* InPawn) override;
	virtual void BeginInactiveState() override;
	// End APlayerController interface

	/* Finds the closest enemy and sets them as current target */
	UFUNCTION(BlueprintCallable, Category = "Behavior")
		bool FindClosestEnemy();

	bool SetEnemy(class APawn* InPawn);
	class APawn* GetEnemy() const;

	UFUNCTION(BlueprintCallable, Category = "Behavior")
		void PlayAnim();

};