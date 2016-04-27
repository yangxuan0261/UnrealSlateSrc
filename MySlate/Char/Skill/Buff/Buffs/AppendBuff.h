
#pragma once

#include "AppendBuff.generated.h"

class UAbsBuff;

UCLASS()
class UAppendBuff : public UAbsBuff
{
	GENERATED_BODY()

public:
	UAppendBuff();
	virtual ~UAppendBuff();
	virtual void BeginDestroy() override;
	
	void AppendBuff(UAbsBuff* _beAdd);
};
