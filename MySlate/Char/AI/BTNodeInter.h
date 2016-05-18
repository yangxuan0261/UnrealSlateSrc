#pragma once

#include "BTNodeInter.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

UINTERFACE(meta = (CannotImplementInterfaceInBlueprint))
class UBTNodeInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IBTNodeInterface 
{
	GENERATED_IINTERFACE_BODY()
public:
	IBTNodeInterface();

	UFUNCTION(BlueprintCallable, Category = "IBTNodeInterface")
		virtual AMyChar*	GetChar() const { return mOwnerChar; }

	UFUNCTION(BlueprintCallable, Category = "IBTNodeInterface")
		virtual AMyAIController*	GetController() const { return mAICtrl; }

	UFUNCTION(BlueprintCallable, Category = "IBTNodeInterface")
		virtual UBehaviorTreeComponent*	GetBTComp() const { return mBTComp; }

protected:
	void		InitData(UBehaviorTreeComponent* _BTComp);

protected:
	AMyChar*			mOwnerChar;
	AMyAIController*	mAICtrl;
	UBehaviorTreeComponent*	mBTComp;
};