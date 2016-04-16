/*
ÎïÀí¹¥»÷
*/
#pragma once
#include "AbsPkEvent.h"
#include "PhyAttack.generated.h"

UCLASS()
class UPhyAttack : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPhyAttack();
	virtual ~UPhyAttack();

	static UPhyAttack* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;


public:
};
