#pragma once

#include "BTNodeInter.generated.h"

class AMyChar;
class AMyAIController;
class UBehaviorTreeComponent;

UINTERFACE()
class UBTNodeInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IBTNodeInterface 
{
	GENERATED_IINTERFACE_BODY()
public:
	IBTNodeInterface();

	void		InitData(UBehaviorTreeComponent* _BTComp);

protected:
	AMyChar*			mOwnerChar;
	AMyAIController*	mAICtrl;
	UBehaviorTreeComponent*	mBTComp;
};