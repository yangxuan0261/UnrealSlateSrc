// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsAttrFunc.h"

#include "Char/MyChar.h"

UAbsAttrFunc::UAbsAttrFunc() : Super()
{
	mBuff = nullptr;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
}

UAbsAttrFunc::~UAbsAttrFunc()
{

}

void UAbsAttrFunc::BeginDestroy()
{
	Super::BeginDestroy();
}

void UAbsAttrFunc::SetData(UAbsBuff* _buff, AMyChar* _attacker, AMyChar* _owner)
{
	mBuff = _buff;
	
	if (_attacker != nullptr)
	{
		mAttacker = _attacker;

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mAttacker = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- UAbsAttrFunc::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};

		_attacker->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}

	if (_owner != nullptr)
	{
		mOwnerChar = _owner;

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mOwnerChar = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- UAbsAttrFunc::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};

		_owner->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
}
