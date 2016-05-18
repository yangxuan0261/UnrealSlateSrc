
#pragma once

#include "./GSBase.h"
#include "GSMainCity.generated.h"

UCLASS()
class UGameStateMainCity : public UGameStateBase
{
	GENERATED_BODY()
public:
	UGameStateMainCity();
	virtual ~UGameStateMainCity() {}
	virtual void BeginDestroy() override;

	virtual void OnEnterState() override;
	virtual void OnExitState() override;
	virtual void OnTick(float DeltaSeconds) override;

public:

};