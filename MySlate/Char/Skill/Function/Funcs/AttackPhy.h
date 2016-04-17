/*
ÎïÀí¹¥»÷
*/
#pragma once
#include "AbsPkEvent.h"
#include "AttackPhy.generated.h"

UCLASS()
class UAttackPhy : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UAttackPhy();
	virtual ~UAttackPhy();

	static UAttackPhy* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;
	virtual void Parser(const TArray<FString>& _params) override;

public:
	float		mValue;
	int32		mOwner;
	int32		mLimitId;
};
