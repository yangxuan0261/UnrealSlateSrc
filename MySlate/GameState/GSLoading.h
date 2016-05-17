
#pragma once

#include "./GSInter.h"
#include "GSLoading.generated.h"

UCLASS()
class UGameStateLoading : public UObject, public IGameStateInterface
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