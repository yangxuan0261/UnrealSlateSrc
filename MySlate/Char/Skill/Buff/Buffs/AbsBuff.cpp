// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsBuff.h"

#include "../../Function/Funcs/AbsPkEvent.h"
#include "../../Pk/PkMsg.h"
#include "Char/CharMgr.h"
#include "Char/MyChar.h"

UAbsBuff::UAbsBuff() : Super()
{
	mBuffId = 0;
	mOwnerId = 0;
	mAttackerId = 0;
	mBuffTemp = nullptr;
	mTimer = 0.f;
	mTotalTime = 0.f;
	mLessTimes = 0;
	mIsRemove = false;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
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
	//持续加血


	mTimer += DeltaSeconds;
	if (mTimer > mTotalTime)
	{
		Remove();
	}
}

void UAbsBuff::BuffStart()
{

}

void UAbsBuff::BuffOver()
{

}

void UAbsBuff::RunBeforePk(UPkMsg* msg)
{

}

void UAbsBuff::RunEndPk(UPkMsg* msg)
{

}

const TArray<UAbsPkEvent*>& UAbsBuff::GetBuffAttrs()
{
	TArray<UAbsPkEvent*> sdf;
	return sdf;
}

AMyChar* UAbsBuff::GetOwnerChar()
{
	//return UCharMgr::GetInstance()->GetChar(mOwnerId);
	return mOwnerChar;
}

void UAbsBuff::SetAttacker(AMyChar* _char)
{
	mAttacker = _char;

	//死亡回调
	auto charDeathCallback = [&](AMyChar* _deathChar)->void {
		mAttacker = nullptr;
		UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::SetAttacker, charDeathCallback, id:%d"), _deathChar->GetUuid());
	};

	_char->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
}
