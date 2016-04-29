#pragma once

#include "./AbsFilter.h"
#include "RectFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class URectFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	URectFilter();
	virtual ~URectFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* _msg, EFilterType _filterType = EFilterType::Locked, float _radius = 0.f, const FVector& _boxSize = FVector::ZeroVector) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static URectFilter* CreateFilter(const FString& _key);

public:
	FVector			mBoxSize;
};
