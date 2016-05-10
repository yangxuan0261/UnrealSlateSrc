
#pragma once

#include "./AbsBuff.h"
#include "AppendBuff.generated.h"

UCLASS()
class UAppendBuff : public UAbsBuff
{
	GENERATED_BODY()
public:
	UAppendBuff();
	virtual ~UAppendBuff();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	void AppendBuff(UAbsBuff* _beAdd);
};
