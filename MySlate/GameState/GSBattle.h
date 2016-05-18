
#pragma once

#include "./GSBase.h"
#include "GSBattle.generated.h"

UCLASS()
class UGameStateBattle : public UGameStateBase
{
	GENERATED_BODY()
public:
	UGameStateBattle();
	virtual ~UGameStateBattle() {}
	virtual void BeginDestroy() override;

	virtual void OnEnterState() override;
	virtual void OnExitState() override;

	virtual void	OnTick(float DeltaSeconds) override;

public:

private:
	bool	mFlag;
};