// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BuffMgr.h"

#include "Char/MyChar.h"

UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	
}

void UBuffMgr::Tick(float DeltaTime)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::Tick"));

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
