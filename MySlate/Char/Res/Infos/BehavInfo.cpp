
#include "MySlate.h"
#include "BehavInfo.h"

FEffElemInfo::FEffElemInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FEffElemInfo::FEffElemInfo construct"));
	mResId = 0;
	mOwnType = EOwnType::Self;
	mFollowType = EFollowType::Follow;
	mBindPoint = "";
	mDelayTime = -1.f;
	mLoc = FVector::ZeroVector;
	mScale = FVector::ZeroVector;
	mRotate = FRotator::ZeroRotator;
}

FEffElemInfo::~FEffElemInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FEffElemInfo::~FEffElemInfo"));
}

FShakeInfo::FShakeInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FShakeInfo::FShakeInfo construct"));
	mA = 0;
	mW = 0.f;
	mTime = -1.f;
	mIsX = true;
	mOwnType = EOwnType::Self;
	mDelayTime = -1.f;
}

FShakeInfo::~FShakeInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FShakeInfo::~FShakeInfo"));
}

FBehavInfo::FBehavInfo() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::FBehavInfo construct"));
}

FBehavInfo::~FBehavInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::~FBehavInfo"));
}


