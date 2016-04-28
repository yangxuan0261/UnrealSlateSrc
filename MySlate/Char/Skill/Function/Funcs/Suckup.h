/*
吸血
*/
#pragma once
#include "AbsPkEvent.h"
#include "Suckup.generated.h"

UCLASS()
class USuckup : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	USuckup();
	virtual ~USuckup();
	virtual void BeginDestroy() override;

	static USuckup* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;
	virtual void Parser(const TArray<FString>& _params) override;

public://buff
	virtual void RunTick(float DeltaSeconds) override;
	virtual void RunStart() override;
	virtual void RunOver() override;

private://buff
	float		mDtVal; //每帧伤害值
	bool		mDurable; //是否持续

public:
	float		mValue;
};
