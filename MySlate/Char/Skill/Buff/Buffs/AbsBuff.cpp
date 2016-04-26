// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsBuff.h"

#include "../../Function/Funcs/AbsPkEvent.h"
#include "../../Pk/PkMsg.h"
#include "Char/CharMgr.h"

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
}

UAbsBuff::~UAbsBuff()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::~UAbsBuff"));
}

void UAbsBuff::BeginDestroy()
{


	UE_LOG(BuffLogger, Warning, TEXT("--- UAbsBuff::BeginDestroy"));
	Super::BeginDestroy();
}

void UAbsBuff::Tick(float DeltaSeconds)
{
	//³ÖÐø¼ÓÑª


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

TArray<UAbsPkEvent*> UAbsBuff::GetBuffAttrs()
{
	TArray<UAbsPkEvent*> sdf;
	return sdf;
}

AMyChar* UAbsBuff::GetOwnerChar()
{
	return UCharMgr::GetInstance()->GetChar(mOwnerId);
}
