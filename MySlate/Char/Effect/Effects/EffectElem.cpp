
#include "MySlate.h"
#include "EffectElem.h"

#include "../../Object/ObjMgr.h"

UEffDataElem::UEffDataElem() : Super()
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
	UEffDataElem* effectElem = gGetObj()->GetObj<UEffDataElem>(gGetObj()->mEffElemCls);
	effectElem->mResId = this->mResId;
	effectElem->mOwnType = this->mOwnType;
	effectElem->mFollowType = this->mFollowType;
	effectElem->mBindPoint = this->mBindPoint;
	effectElem->mDelayTime = this->mDelayTime;
	effectElem->mLoc = this->mLoc;
	effectElem->mRotate = this->mRotate;
	effectElem->mScale = this->mScale;
	return effectElem;
}

