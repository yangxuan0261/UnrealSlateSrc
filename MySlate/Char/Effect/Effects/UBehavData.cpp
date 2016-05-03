
#include "MySlate.h"
#include "UBehavData.h"

#include "../../Skill/Utils/CommonDef.h"
#include "../EffectMgr.h"

UEffDataElem::UEffDataElem()
{
	mResId = 0;
	mEffectType = ESkillEffectType::SelfFollow;
	mBindPoint = "";
	mDelayTime = 0.f;
	mLoc = FVector::ZeroVector;
	mScale = FVector(1.f, 1.f, 1.f);
	mRotate = FRotator::ZeroRotator;
}

UEffDataElem::~UEffDataElem()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UEffDataElem::~UEffDataElem"));
}

void UEffDataElem::BeginDestroy()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UEffDataElem::BeginDestroy, id:%d"), mResId);
	Super::BeginDestroy();
}

UBehavData::UBehavData() : Super()
{
	mId = 0;
}

UBehavData::~UBehavData()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UBehaviorData::~UBehaviorData"));
}

void UBehavData::BeginDestroy()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UBehaviorData::BeginDestroy, id:%d"), mId);
	Super::BeginDestroy();
}

void UBehavData::Tick(float DeltaTime)
{

}

TArray<UEffDataElem*>& UBehavData::GetEffElems()
{
	return mEffElemVec;
}

