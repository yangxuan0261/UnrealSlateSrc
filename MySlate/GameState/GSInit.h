
#pragma once

#include "./GSBase.h"
#include "GSInit.generated.h"

UCLASS()
class UGameStateInit : public UGameStateBase
{
	GENERATED_BODY()
public:
	UGameStateInit();
	virtual ~UGameStateInit() {}
	virtual void BeginDestroy() override;

	virtual void OnEnterState() override;
	virtual void OnExitState() override;
	virtual void OnTick(float DeltaSeconds) override;

protected:

};