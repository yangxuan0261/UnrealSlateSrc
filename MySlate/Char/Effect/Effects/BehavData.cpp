
#include "MySlate.h"
#include "BehavData.h"

#include "./BehavElem.h"

UBehavData::UBehavData()
{
	mId = 0;
}

UBehavData::~UBehavData()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UBehaviorData::~UBehaviorData"));
}

void UBehavData::BeginDestroy()
{
	MyDestroy(mAtkEffVec, mAtkShkVec);
	MyDestroy(mBltEffVec, mBltShkVec);
	MyDestroy(mTarEffVec, mTarShkVec);
	MyDestroy(mSceEffVec, mSceShkVec);

	UE_LOG(EffectLogger, Warning, TEXT("--- UBehaviorData::BeginDestroy, id:%d"), mId);
	Super::BeginDestroy();
}

void UBehavData::MyDestroy(TArray<UEffDataElem*>& _effectVec, TArray<UShakeElem*> _shakeVec)
{
	for (UEffDataElem* effElem : _effectVec)
	{
		effElem->RemoveFromRoot();
		effElem->ConditionalBeginDestroy();
	}
	_effectVec.Empty();

	for (UShakeElem* shakeElem : _shakeVec)
	{
		shakeElem->RemoveFromRoot();
		shakeElem->ConditionalBeginDestroy();
	}
	_shakeVec.Empty();
}

void UBehavData::Tick(float DeltaTime)
{

}

UBehavData* UBehavData::Clone()
{
	return nullptr;
}

