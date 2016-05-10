
#include "MySlate.h"
#include "CharData.h"

#include "./Skill/Pk/FightData.h"
#include "./Object/ObjMgr.h"

UCharData::UCharData() : Super()
{
	mId = 0;
	mName = "";;
	mDescr = "";
	mHeath = 100.f;
	mHeathMax = 150.f;
}

UCharData::~UCharData()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UCharData::~UCharData"));
}

void UCharData::BeginDestroy()
{
	if (mFightData != nullptr)
	{
		mFightData->RemoveFromRoot();
		mFightData->ConditionalBeginDestroy();
		mFightData = nullptr;
	}

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UCharData::BeginDestroy, id:%d"), mId);
	Super::BeginDestroy();
}

void UCharData::Init()
{
	mFightData = GetObjMgr()->GetObj<UFightData>(GetObjMgr()->mFightDataCls);
}
