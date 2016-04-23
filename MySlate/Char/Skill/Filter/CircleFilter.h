#pragma once

#include "AbsFilter.h"
#include "CircleFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class UCircleFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	UCircleFilter();
	virtual ~UCircleFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* _msg, EFilterType _filterType = EFilterType::Locked, float _radius = 0.f, const FVector& _boxSize = FVector::ZeroVector) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static UCircleFilter* CreateFilter(const FString& _key);

public:
	int32		mRadius;		//ѡ�˰뾶
};
