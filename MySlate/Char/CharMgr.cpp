// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CharMgr.h"

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
		//if (_char->)
		{
		}
	}
}
