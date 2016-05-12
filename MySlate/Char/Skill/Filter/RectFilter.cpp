
#include "MySlate.h"
#include "RectFilter.h"

#include "../Pk/PkMsg.h"
#include "../../MyChar.h"
#include "../../Object/ObjMgr.h"

URectFilter::URectFilter() : Super()
{
}

URectFilter::~URectFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- URectFilter::~URectFilter"));
}
 
void URectFilter::BeginDestroy()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- URectFilter::BeginDestroy"));
	Super::BeginDestroy();
}

void URectFilter::Reset()
{
	Super::Reset();
	mBoxSize = FVector::ZeroVector;
}

void URectFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector::ZeroVector */)
{
	Super::Filter(_msg, EFilterType::Circle, 0.f, mBoxSize);

}

UAbsFilter* URectFilter::Clone()
{
	return CreateFilter(mKey);
}

void URectFilter::Parser(const TArray<FString>& _params)
{

	if (_params.Num() == 5)
	{
		mSelectType = (ESelectType)FCString::Atoi(*_params[0]);
		mCount = FCString::Atoi(*_params[1]);
		mBoxSize.X = FCString::Atof(*_params[2]);
		mBoxSize.Y = FCString::Atof(*_params[2]);
		mBoxSize.Z = FCString::Atof(*_params[2]);
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- URectFilter::Parser, _params.Num() = %d"), _params.Num());
	}
}

URectFilter* URectFilter::CreateFilter(const FString& _key)
{
	URectFilter* circleFilter = GetObjMgr()->GetObj<URectFilter>(GetObjMgr()->mRectFltCls);
	circleFilter->SetKey(_key);
	return circleFilter;
}
