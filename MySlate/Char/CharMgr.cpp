// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CharMgr.h"

#include "MyChar.h"
#include "MyCharDataComp.h"

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
