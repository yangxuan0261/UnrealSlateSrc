// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FightData.h"

UFightData::UFightData() : Super()
{
	Reset();
}

UFightData::~UFightData()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::~UFightData"));
}

void UFightData::BeginDestroy()
{

	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::BeginDestroy"));
	Super::BeginDestroy();
}

UFightData* UFightData::Clone()
{
	UFightData* data = NewObject<UFightData>(UFightData::StaticClass());
	data->Copy(this);
	return data;
}

void UFightData::Copy(UFightData* _fightData)
{
	this->mAttackPhy = _fightData->mAttackPhy;
	this->mLv = _fightData->mLv;
}

void UFightData::Reset()
{
	mAttackPhy = 0.f;
	mLv = 1;
}
