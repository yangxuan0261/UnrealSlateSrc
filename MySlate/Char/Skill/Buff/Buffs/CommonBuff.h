
#pragma once

#include "./AbsBuff.h"
#include "CommonBuff.generated.h"

UCLASS()
class UCommonBuff : public UAbsBuff
{
	GENERATED_BODY()
public:
	UCommonBuff();
	virtual ~UCommonBuff();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
};
