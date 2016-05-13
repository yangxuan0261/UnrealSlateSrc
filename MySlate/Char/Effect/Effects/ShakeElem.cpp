
#include "MySlate.h"
#include "ShakeElem.h"

#include "../../Object/ObjMgr.h"

UShakeElem::UShakeElem() : Super()
{
	mTarget = nullptr;
	mLoc = FVector::ZeroVector;
	mDtLoc = FVector::ZeroVector;
	mRunTimer = 0.f;
}

UShakeElem::~UShakeElem()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UShakeElem::~UShakeElem"));
}

void UShakeElem::BeginDestroy()
{
	UE_LOG(EffectLogger, Warning, TEXT("--- UShakeElem::BeginDestroy"));
	Super::BeginDestroy();
}

UShakeElem* UShakeElem::Clone()
{
	UShakeElem* shakeElem = gGetObj()->GetObj<UShakeElem>(gGetObj()->mShkElemCls);
	shakeElem->mA = this->mA;
	shakeElem->mW = this->mW;
	shakeElem->mTime = this->mTime;
	shakeElem->mIsX = this->mIsX;
	shakeElem->mOwnType = this->mOwnType;
	shakeElem->mDelayTime = this->mDelayTime;
	return shakeElem;
}

void UShakeElem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mState == EElemState::Ticking)
	{
		if (mRunTimer < mTime)
		{
			mRunTimer += DeltaTime;
			float dtVal = mA * (1 - mRunTimer / mTime) * FMath::Cos(mW * mRunTimer) - mA * 0.5f;
			if (mIsX)
			{
				mDtLoc.X = dtVal;
			}
			else
			{
				mDtLoc.Y = dtVal;
			}
			mTarget->GetActor()->SetActorLocation(mLoc + mDtLoc);
		}
		else
		{
			mState = EElemState::Over;
			UE_LOG(EffectLogger, Warning, TEXT("--- End pos y=%f"), mTarget->GetActor()->GetActorLocation().Y);
		}
	}
}

void UShakeElem::Start()
{
	if (mTarget != nullptr)
	{
		Super::Start();
		mLoc = mTarget->GetActor()->GetActorLocation();
		mDtLoc = FVector::ZeroVector;
		mRunTimer = 0.f;
		mDelayer = 0.f;
		UE_LOG(EffectLogger, Warning, TEXT("--- Start pos y=%f"), mTarget->GetActor()->GetActorLocation().Y);
	}
	else
	{
		mState = EElemState::Over;
		UE_LOG(EffectLogger, Error, TEXT("--- UShakeElem::Start, char == nullptr"));
	}
}
