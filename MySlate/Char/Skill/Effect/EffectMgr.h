
#pragma once

#include "../../../Common/ISingleton.h"

#include "EffectMgr.generated.h"

UCLASS()
class UEffectMgr : public UObject, public USingleton<UEffectMgr>
{
	GENERATED_BODY()

public:
	UEffectMgr();
	virtual ~UEffectMgr();
	virtual void BeginDestroy() override;

public:

};
