
#pragma once

#include "../../../Object/ObjInter.h"
#include "AbsAttrFunc.generated.h"

class UAbsBuff;
class AMyChar;

UCLASS()
class UAbsAttrFunc : public UObject, public IObjInterface
{
	GENERATED_BODY()
public:
	UAbsAttrFunc();
	virtual ~UAbsAttrFunc();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

public:
	virtual void RunTick(float DeltaSeconds) {}
	virtual void RunStart() {}
	virtual void RunOver() {}

	void	SetData(UAbsBuff* _buff, AMyChar* _attacker, AMyChar* _owner);

protected:
	UAbsBuff*		mBuff;
	AMyChar*		mAttacker;
	AMyChar*		mOwnerChar;
};
