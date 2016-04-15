// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "FightData.h"

// Sets default values
UFightData::UFightData() : Super()
{
	//UE_LOG(SkillDataMgrLogger, Warning, TEXT("--- USkillDataMgr::Tick:%f"), 0.2f);
}

UFightData::~UFightData()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::~UFightData"));
}
