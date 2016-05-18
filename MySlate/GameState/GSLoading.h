
#pragma once

#include "./GSBase.h"
#include "GSLoading.generated.h"

UCLASS()
class UGameStateLoading : public UGameStateBase
{
	GENERATED_BODY()
public:
	UGameStateLoading();
	virtual ~UGameStateLoading() {}
	virtual void BeginDestroy() override;

	virtual void OnEnterState() override;
	virtual void OnExitState() override;
	virtual void OnTick(float DeltaSeconds) override;

public:

};