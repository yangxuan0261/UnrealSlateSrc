
#pragma once

#include "./GSInter.h"
#include "GSMainCity.generated.h"

UCLASS()
class UGameStateMainCity : public UObject, public IGameStateInterface
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