#pragma once

#include "BTNodeExt.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

UCLASS()
class UBTNodeExt : public UObject
{
	GENERATED_BODY()
public:
	UBTNodeExt();
	virtual ~UBTNodeExt();

	UFUNCTION(BlueprintCallable, Category = "UBTDecorateMyBase")
		void		InitData(UBehaviorTreeComponent* _BTComp);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTDecorateMyBase")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTDecorateMyBase")
		AMyAIController*	mOwnerAI;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBTDecorateMyBase")
		UBehaviorTreeComponent*	mBTComp;

};