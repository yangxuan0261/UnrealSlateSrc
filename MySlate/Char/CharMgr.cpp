// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CharMgr.h"

#include "MyChar.h"
#include "MyCharDataComp.h"

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
	}
}
