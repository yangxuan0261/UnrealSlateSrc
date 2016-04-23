#pragma once

#include "AbsFilter.h"
#include "LockFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class ULockFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	ULockFilter();
	virtual ~ULockFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* _msg, EFilterType _filterType = EFilterType::Locked, float _radius = 0.f, const FVector& _boxSize = FVector::ZeroVector) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static ULockFilter* CreateFilter(const FString& _key);

public:
	int32		mType; //1¼º·½£¬-1µÐ·½
};
