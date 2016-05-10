
/********************************************************************
*¼Óbuff*		addbuff_1234 - addbuff_buffid
*********************************************************************
*/
#pragma once

#include "./AbsPkEvent.h"
#include "AddBuff.generated.h"

UCLASS()
class UAddBuff : public UAbsPkEvent
{
	GENERATED_BODY()

public:
	UAddBuff();
	virtual ~UAddBuff();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	static UAddBuff* CreateFunction(const FString& _key);
	virtual UAbsPkEvent* Clone() override;
	virtual void Parser(const TArray<FString>& _params) override;

	virtual void RunEndEvns(UPkMsg* msg) override;

public:
	int32		mBuffId;
};
