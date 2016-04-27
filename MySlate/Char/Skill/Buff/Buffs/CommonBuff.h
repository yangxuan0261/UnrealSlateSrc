
#pragma once

#include "CommonBuff.generated.h"

UCLASS()
class UCommonBuff : public UAbsBuff
{
	GENERATED_BODY()

public:
	UCommonBuff();
	virtual ~UCommonBuff();
	virtual void BeginDestroy() override;

};
