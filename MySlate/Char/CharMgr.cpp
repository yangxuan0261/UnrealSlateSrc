// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CharMgr.h"

#include "MyChar.h"
#include "Comp/MyCharDataComp.h"

static int32 uuid = 1;
static int32 IdGenerator()
{
	return uuid++;
}

UCharMgr::UCharMgr() : Super()
{

}

UCharMgr::~UCharMgr()
{
	mSelfCharArr.Empty();
	mTeamCharArr.Empty();
	mEnemyCharArr.Empty();
}



void UCharMgr::AddChar(AMyChar* _char)
{
	if (_char != nullptr)
	{
		if (_char->mDataComp->mTeam == ETeam::Teammate)
		{
			mTeamCharArr.AddUnique(_char);
		}
		else if (_char->mDataComp->mTeam == ETeam::Enemy)
		{
			mEnemyCharArr.AddUnique(_char);
		}
		_char->SetUuid(::IdGenerator());
		mAllCharMap.Add(_char->mUuid, _char);
	}
}

AMyChar* UCharMgr::GetChar(int32 _id)
{
	AMyChar** mychar = mAllCharMap.Find(_id);
	return mychar != nullptr ? *mychar : nullptr;
}

void UCharMgr::RemoveChar(int32 _id)
{
	mAllCharMap.Remove(_id);
}

ETeam UCharMgr::GetDestTeam(const ETeam& _atkTeam, int32 _flag)
{
	//_flag: 1:攻击方，2:受击方
	if (_flag == 1)
	{
		return _atkTeam;
	}
	else
	{
		if (_atkTeam == ETeam::Teammate)
		{
			return ETeam::Enemy;
		}
		else
		{
			return ETeam::Teammate;
		}
	}
}

ETeam UCharMgr::GetIgnoreTeam(const ETeam& _atkTeam, int32 _flag)
{
	//_flag: 1:攻击方，2:受击方
	if (_flag == -1)
	{
		return _atkTeam;
	}
	else
	{
		if (_atkTeam == ETeam::Teammate)
		{
			return ETeam::Enemy;
		}
		else
		{
			return ETeam::Teammate;
		}
	}
}

void UCharMgr::GetIgnoreCharsByTeam(ETeam _type, UPARAM(ref) TArray<AMyChar*>& _outChars) const
{
	AMyChar* target = nullptr;
	for (TMap<int32, AMyChar*>::TConstIterator Iter = mAllCharMap.CreateConstIterator(); Iter; ++Iter)
	{
		target = Iter->Value;
		if (target->GetDataComp()->GetTeamType() == _type)
		{
			_outChars.Add(target);
		}
	}
}

void UCharMgr::ConvertCharsToActors(UPARAM(ref) const TArray<AMyChar*>& _srcChars, TArray<AActor*>& _outActors)
{
	for (AMyChar* tmpChar : _srcChars)
	{
		_outActors.Add(tmpChar);
	}
}

void UCharMgr::ConvertActorsToChars(UPARAM(ref) const TArray<AActor*>& _srcActors, TArray<AMyChar*>& _outChars)
{
	AMyChar* target = nullptr;
	for (AActor* tmpActor : _srcActors)
	{
		target = Cast<AMyChar>(tmpActor);
		if (target != nullptr)
		{
			_outChars.Add(target);
		}
	}
}

