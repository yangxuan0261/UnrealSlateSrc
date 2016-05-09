
#include "MySlate.h"
#include "BehavElem.h"

#include "../../Skill/Utils/CommonDef.h"
#include "../EffectMgr.h"
#include "../../MyChar.h"
#include "../../BehavInter.h"

UBehavElem::UBehavElem()
{
	mGroupId = 0;
	mTarget = nullptr;
	mDelayer = 0.f;
	mDelayTime = 0.f;
	mState = EElemState::Idle;
}

UBehavElem::~UBehavElem()
{

}

void UBehavElem::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBehavElem::Tick(float DeltaTime)
{
	if (mState == EElemState::Start)
	{
		if (mDelayer < mDelayTime)
		{
			mDelayer += DeltaTime;
		}
		else
		{
			mState = EElemState::Ticking;
		}
	}

	if (mState == EElemState::Over)
	{
		mState = EElemState::Idle;
		MyDestroy(true);
	}
}

void UBehavElem::AddOverDlg(FBehavElemDlg _dlg)
{
	mOverDlg = _dlg;
}

void UBehavElem::MyDestroy(bool _needNotify /*= true*/)
{
	if (_needNotify)
	{
		mOverDlg.ExecuteIfBound(this); //通知绑定者移除
	}
	RemoveFromRoot();
	ConditionalBeginDestroy();
}

void UBehavElem::Start()
{
	mState = EElemState::Start;
}

void UBehavElem::SetActor(IBehavInterface* _actor)
{
	mTarget = _actor;
	mOverDlg.BindRaw(_actor, &AMyChar::RemoveBehavElem);
}

//--------------- UShakeElem Begin ------------
UShakeElem::UShakeElem()
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
	UShakeElem* shakeElem = NewObject<UShakeElem>(UShakeElem::StaticClass());
	shakeElem->mA = this->mA;
	shakeElem->mW = this->mW;
	shakeElem->mTime = this->mTime;
	shakeElem->mIsX = this->mIsX;
	shakeElem->mOwnType = this->mOwnType;
	shakeElem->mDelayTime = this->mDelayTime;
	shakeElem->AddToRoot();
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

//--------------- UEffDataElem Begin ------------
UEffDataElem::UEffDataElem()
{
	mPsComp = nullptr;
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

void UEffDataElem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (mState == EElemState::Ticking)
	{
		mState = EElemState::Idle; //等粒子播完的回调设置mState = EElemState::Over
		mPsComp->SetVisibility(true);
		mPsComp->CustomTimeDilation = 1.f;
	}
}

void UEffDataElem::Start()
{
	if (mPsComp != nullptr)
	{
		Super::Start();
		//mPsComp 
		mPsComp->SetVisibility(false);
		mPsComp->CustomTimeDilation = 0.f;
	}
	else
	{
		mState = EElemState::Over;
		UE_LOG(EffectLogger, Error, TEXT("--- UEffDataElem::Start, mPsComp == nullptr"));
	}
}

void UEffDataElem::MyDestroy(bool _needNotify /*= true*/)
{
	if (mPsComp != nullptr)
	{
		mPsComp->DetachFromParent();
		mPsComp->DestroyComponent();
	}
	Super::MyDestroy(_needNotify);
}

void UEffDataElem::SetActor(IBehavInterface* _actor)
{
	Super::SetActor(_actor);
}

void UEffDataElem::SetData(UParticleSystemComponent* _psComp)
{
	mPsComp = _psComp;
	if (mPsComp != nullptr)
	{
		mPsComp->OnSystemFinished.AddDynamic(this, &UEffDataElem::OnCompleted); //特效播完的回调
	}
}

void UEffDataElem::OnCompleted(UParticleSystemComponent* _psComp)
{
	mState = EElemState::Over;
}

UEffDataElem* UEffDataElem::Clone()
{
	UEffDataElem* effectElem = NewObject<UEffDataElem>(UEffDataElem::StaticClass());
	effectElem->mResId = this->mResId;
	effectElem->mOwnType = this->mOwnType;
	effectElem->mFollowType = this->mFollowType;
	effectElem->mBindPoint = this->mBindPoint;
	effectElem->mDelayTime = this->mDelayTime;
	effectElem->mLoc = this->mLoc;
	effectElem->mRotate = this->mRotate;
	effectElem->AddToRoot();
	return effectElem;
}

