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

void UCharMgr::GetIgnoreCharsByTeam(ETeam _type, UPARAM(ref) TArray<AMyChar*> _chars) const
{
	AMyChar* target = nullptr;
	for (TMap<int32, AMyChar*>::TConstIterator Iter = mAllCharMap.CreateConstIterator(); Iter; ++Iter)
	{
		target = Iter->Value;
		if (target->GetDataComp()->GetTeamType() == _type)
		{
			_chars.Add(target);
		}
	}
}

