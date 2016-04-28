// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "Suckup.h"

#include "../../Buff/Buffs/AbsBuff.h"
#include "Char/Comp/MyCharDataComp.h"
#include "Char/MyChar.h"

USuckup::USuckup() : Super()
{
	//buff
	mDtVal = 0.f;
	mDurable = true;

	//skill
	mValue = 0.f;
}

USuckup::~USuckup()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- USuckup::~USuckup"));
}

void USuckup::BeginDestroy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- USuckup::BeginDestroy"));
	Super::BeginDestroy();
}

USuckup* USuckup::CreateFunction(const FString& _key)
{
	USuckup* func = NewObject<USuckup>(USuckup::StaticClass());
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* USuckup::Clone()
{
	return CreateFunction(mKey);
}

void USuckup::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 1)
	{
		CheckPercent(_params[0]);
		mValue = (float)FCString::Atoi(*_params[0]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- USuckup::Parser, params num < 1"));
	}
}

void USuckup::RunTick(float DeltaSeconds)
{
	if (mDurable)
	{
		if (mOwnerChar != nullptr) //buffÊ¹ÓÃmOwnerChar
		{
			mOwnerChar->GetDataComp()->Hurt(mDtVal);
		}
		if (mAttacker != nullptr)
		{
			mAttacker->GetDataComp()->Hurt(-mDtVal);
		}
	}
}

void USuckup::RunStart()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- USuckup::RunStart"));
	if (mBuff == nullptr)
	{
		UE_LOG(FuncLogger, Warning, TEXT("--- USuckup::RunStart, mBuff == nullptr"));
	}

	mDurable = mBuff->IsDurable();
	if (mDurable)
	{
		mDtVal = mBuff->GetDtVal(mValue);
	}
}

void USuckup::RunOver()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- USuckup::RunOver"));
}
