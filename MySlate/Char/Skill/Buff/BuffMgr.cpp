// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BuffMgr.h"

#include "Char/MyChar.h"
#include "Buffs/AbsBuff.h"
#include "Buffs/AppendBuff.h"
#include "Buffs/CommonBuff.h"
#include "../Utils/SkillDataMgr.h"
#include "../Template/BufflTemplate.h"


UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::~UBuffMgr"));
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
	mBuffs.Empty();

	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UBuffMgr::Tick(float DeltaTime)
{
	UAbsBuff* buff = nullptr;
	for (auto Iter = mBuffs.CreateIterator(); Iter; ++Iter)
	{
		TArray<UAbsBuff*>&	buffs = Iter->Value;
		for (int32 i = 0;i < buffs.Num(); i++)
		{
			buff = buffs[i];
			if (buff->IsRemoeve())
			{
				buff->BuffOver();
				buffs.RemoveAt(i);
			}
			else
			{
				buff->Tick(DeltaTime);//¸üÐÂbuffer
			}
		}

		if (buffs.Num() == 0)
		{
			Iter.RemoveCurrent();
		}
	}
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

void UBuffMgr::AddBuff(int32 _attackId,int32 _targetId, int32 _skillId, int32 _buffId)
{
	UBufflTemplate* buffTemp = USkillDataMgr::GetInstance()->GetBuffTemplate(_buffId);
	if (buffTemp != nullptr)
	{
		if (buffTemp->mCanAdd) //µþ¼Óbuff
		{
			UAppendBuff* appendBuff = NewObject<UAppendBuff>(UAppendBuff::StaticClass());

			UAbsBuff* findBuff = FindBuff(_targetId, _buffId);
			UAppendBuff* buff = findBuff != nullptr ? Cast<UAppendBuff>(UAppendBuff::StaticClass()) : nullptr;
			if (buff != nullptr)
			{
				buff->AppendBuff(buff);
				appendBuff->ConditionalBeginDestroy();
			}
			else
			{

			}

		}
		else
		{
			UCommonBuff* commBuff = NewObject<UCommonBuff>(UCommonBuff::StaticClass());

		}
	}
	else
	{
		UE_LOG(BuffLogger, Error, TEXT("--- UBuffMgr::AddBuff, buff template == nullptr, id:%d"), _buffId);
	}
}

UAbsBuff* UBuffMgr::FindBuff(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			if (buff->GetBuffId() == _buffId)
				return buff;

		}
	}
	return nullptr;
}

void UBuffMgr::RemoveBuff(int32 _charId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			buff->Remove();
		}
	}
}

void UBuffMgr::RemoveBuffSpec(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			if (buff->GetBuffId() == _buffId)
			{
				buff->Remove();
				break;
			}
		}
	}
}

void UBuffMgr::CharDeathNotify(AMyChar* _char)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::CharDeathNotify, char death, uuid:%d"), _char->GetUuid());

	RemoveBuff(_char->GetUuid());
}
