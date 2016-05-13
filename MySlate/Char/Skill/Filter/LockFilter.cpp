
#include "MySlate.h"
#include "LockFilter.h"

#include "../Pk/PkMsg.h"
#include "../../MyChar.h"
#include "../../Object/ObjMgr.h"

ULockFilter::ULockFilter() : Super()
{
}

ULockFilter::~ULockFilter()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- ULockFilter::~ULockFilter"));
}

void ULockFilter::BeginDestroy()
{
	UE_LOG(FilterLogger, Warning, TEXT("--- ULockFilter::BeginDestroy"));
	Super::BeginDestroy();
}

void ULockFilter::Reset()
{
	Super::Reset();
}

void ULockFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector::ZeroVector */)
{
	Super::Filter(_msg, EFilterType::Locked);

	_msg->AddTarget(_msg->GetTarget(), true);
}

UAbsFilter* ULockFilter::Clone()
{
	return CreateFilter(mKey);
}

void ULockFilter::Parser(const TArray<FString>& _params)
{
	if (_params.Num() > 0)
	{
		mSelectType = (ESelectType)FCString::Atoi(*_params[0]);
	}
}

ULockFilter* ULockFilter::CreateFilter(const FString& _key)
{
	ULockFilter* lockFilter = gGetObjMgr()->GetObj<ULockFilter>(gGetObjMgr()->mLockFltCls);
	lockFilter->SetKey(_key);
	return lockFilter;
}
