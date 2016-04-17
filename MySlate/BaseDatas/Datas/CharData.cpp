// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CharData.h"
#include "Char/Skill/Pk/FightData.h"

UCharData::UCharData() : Super()
{
	mId = 0;
	mName = "";;
	mDescr = "";
	mHeath = 100.f;
	mFightData = NewObject<UFightData>(UFightData::StaticClass());
	mFightData->AddToRoot();
}

UCharData::~UCharData()
{
	if (mFightData != nullptr)
	{
		mFightData->RemoveFromRoot();
		mFightData = nullptr;
	}
}
