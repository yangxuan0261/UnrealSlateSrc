// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BuffMgr.h"

#include "Char/MyChar.h"
#include "Buffs/AbsBuff.h"

UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UBuffMgr::~UBuffMgr"));
}

void UBuffMgr::BeginDestroy()
{
	for (auto iter = mBuffs.CreateIterator(); iter; ++iter)
	{
		for (auto tempBuff : iter->Value)
		{
			tempBuff->RemoveFromRoot();
			tempBuff->ConditionalBeginDestroy();
		}
		iter->Value.Empty();
	}

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UBuffMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UBuffMgr::Tick(float DeltaTime)
{
	//UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::Tick"));

}

bool UBuffMgr::IsTickable() const
{
	return true;
}

TStatId UBuffMgr::GetStatId() const
{
	return TStatId();
}

void UBuffMgr::RunBeforePkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::RunEndPkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::RemoveBuff(int32 _charId)
{

}

void UBuffMgr::CharDeathNotify(AMyChar* _char)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::CharDeathNotify, char death, uuid:%d"), _char->GetUuid());

	RemoveBuff(_char->GetUuid());
}
