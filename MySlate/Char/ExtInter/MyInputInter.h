#pragma once

/*******************************************
***** ÊäÈë¿ØÖÆÆ÷À©Õ¹
*******************************************/

#include "MyInputInter.generated.h"

UINTERFACE()
class UMyInputInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IMyInputInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IMyInputInterface();

	UFUNCTION(BlueprintNativeEvent, Category = "UMyInputInterface")
		void		SetParticleVisible(bool _b);

	UFUNCTION(BlueprintNativeEvent, Category = "UMyInputInterface")
		void		MoveToDst(const FVector& _loc);

	UFUNCTION(BlueprintNativeEvent, Category = "UMyInputInterface")
		void		AttackTarget(AMyChar* _target, int32 _skillId = 0);
};