// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FightData.h"

UFightData::UFightData() : Super()
{
	mAttackPhy = 0.f;
	mLv = 1;
}

UFightData::~UFightData()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::~UFightData"));
}

void UFightData::Clone(UFightData& _fightData)
{
	_fightData.mAttackPhy = this->mAttackPhy;
	_fightData.mLv = this->mLv;
}
