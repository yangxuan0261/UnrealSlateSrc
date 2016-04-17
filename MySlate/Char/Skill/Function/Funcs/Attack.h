/*********************************************************************/
/*攻击力增加(百分比)*/
/*********************************************************************/
#pragma once
#include "AbsPkEvent.h"
#include "Attack.generated.h"

UCLASS()
class UAttack : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UAttack();
	virtual ~UAttack();

	static UAttack* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;
	virtual void Parser(const TArray<FString>& _params) override;
	virtual void RunBeforePk(UPkMsg* msg) override;

public:
	float		mValue;
	int32		mOwner;
	int32		mLimitId;
};
