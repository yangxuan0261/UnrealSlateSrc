// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsBuff.h"

#include "../../Function/Funcs/AbsPkEvent.h"
#include "../../Pk/PkMsg.h"
#include "Char/CharMgr.h"
#include "Char/MyChar.h"
#include "../../Template/BufflTemplate.h"

static int32 gEffectUuid = 1;
static int32 IdGeneratorEffect()
{
	return gEffectUuid++;
}

UAbsBuff::UAbsBuff() : Super()
{
	mBuffId = 0;
	mSkillId = 0;
	mOwnerId = 0;
	mAttackerId = 0;
	mBuffTemp = nullptr;
	mTimer = 0.f;
	mTotalTime = 0.f;
	mLessTimes = 0;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
	mBuffState = EBuffState::Idle;
	mEffectUUid = 0;
}

UAbsBuff::~UAbsBuff()
{

}

void UAbsBuff::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsBuff::Tick(float DeltaSeconds)
{
	//持续或间隔伤害
	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->RunTick(DeltaSeconds);
	}

	mTimer += DeltaSeconds;
	if (mTimer > mTotalTime)
	{
		ChangeState(EBuffState::Over);
	}
}

void UAbsBuff::BuffStart()
{
	ChangeState(EBuffState::Start);

	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->SetData(this, mAttacker, mOwnerChar); //让fun中可以获取到这个buff
		func->RunStart();
	}

	//TODO 特效绑定
	mEffectUUid = ::IdGeneratorEffect();
	FEffectBind eb(1, mEffectUUid, mBuffTemp->mBindPos, "", 10.f, nullptr);
	mOwnerChar->AttachEffect(eb);
}

void UAbsBuff::BuffOver()
{
	const TArray<UAbsPkEvent*>& funcs = mBuffTemp->GetAttrs();
	for (UAbsPkEvent* func : funcs)
	{
		func->RunOver();
	}

	mOwnerChar->DetachEffect(mEffectUUid);
}

void UAbsBuff::RunBeforePk(UPkMsg* msg)
{

}

void UAbsBuff::RunEndPk(UPkMsg* msg)
{

}

AMyChar* UAbsBuff::GetOwnerChar()
{
	return mOwnerChar;
}

bool UAbsBuff::IsDurable() const
{
	return mBuffTemp->mDurable;
}

float UAbsBuff::GetDtVal(float _value)
{
	float f = (float)mBuffTemp->mBuffTime / GWorld->GetDeltaSeconds();
	return _value / f;
}

void UAbsBuff::SetData(UBufflTemplate* _buffTemp, AMyChar* _attacker, AMyChar* _target, int32 _skillId)
{
	mBuffTemp = _buffTemp;
	mBuffId = _buffTemp->mId;
	mTotalTime = _buffTemp->mBuffTime;
	mSkillId = _skillId;

	if (_attacker != nullptr)
	{
		mAttacker = _attacker;

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mAttacker = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};

		_attacker->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}

	if (_target != nullptr)
	{
		mOwnerChar = _target;

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mOwnerChar = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};

		_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
}
