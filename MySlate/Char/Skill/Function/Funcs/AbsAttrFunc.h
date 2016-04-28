
#pragma once

#include "AbsAttrFunc.generated.h"

class UAbsBuff;
class AMyChar;

UCLASS()
class UAbsAttrFunc : public UObject
{
	GENERATED_BODY()

public:
	

public:
	UAbsAttrFunc();
	virtual ~UAbsAttrFunc();
	virtual void BeginDestroy() override;

	virtual void RunTick(float DeltaSeconds) {}
	virtual void RunStart() {}
	virtual void RunOver() {}

	void	SetData(UAbsBuff* _buff, AMyChar* _attacker, AMyChar* _owner);

protected:
	UAbsBuff*		mBuff;
	AMyChar*		mAttacker;
	AMyChar*		mOwnerChar;
};
