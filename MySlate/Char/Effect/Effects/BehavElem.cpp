
#include "MySlate.h"
#include "BehavElem.h"

#include "../../../GameUtils.h"
#include "../EffectMgr.h"
#include "../../MyChar.h"
#include "../../BehavInter.h"
#include "../../Object/ObjMgr.h"

UBehavElem::UBehavElem() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UBehavElem::~UBehavElem()
{

}

void UBehavElem::BeginDestroy()
{
	Super::BeginDestroy();
}

void UBehavElem::Reset()
{
	mGroupId = 0;
	mTarget = nullptr;
	mDelayer = 0.f;
	mDelayTime = 0.f;
	mState = EElemState::Idle;
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

	IObjInterface::Recycle();
}

void UBehavElem::Start()
{
	mState = EElemState::Start;
}

//匹配到宿主actor
void UBehavElem::SetActor(IBehavInterface* _actor)
{
	mTarget = _actor;
	mOverDlg.BindRaw(_actor, &AMyChar::RemoveBehavElem);

	AActor* dstTar = nullptr;
	AMyBullet* bullet = Cast<AMyBullet>(_actor);
	dstTar = bullet != nullptr ? bullet : nullptr;
	if (dstTar == nullptr)
	{
		AMyChar* mychar = Cast<AMyChar>(_actor);
		dstTar = mychar != nullptr ? mychar : nullptr;
	}

	_actor->SetActor(dstTar);
}
