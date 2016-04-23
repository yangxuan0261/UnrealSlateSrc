// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillMgr.h"

#include "Common/CommonHeader.h"
#include "Effect/BehaviorData.h"

USkillMgr::USkillMgr() : Super()
{

}

USkillMgr::~USkillMgr()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillMgr::~USkillMgr"));
}

void USkillMgr::BeginDestroy()
{

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void USkillMgr::Tick(float DeltaTime)
{

}

bool USkillMgr::IsTickable() const
{
	return true;
}

TStatId USkillMgr::GetStatId() const
{
	return TStatId();
}

UBehaviorData* USkillMgr::GetBehaviorData(int32 _id)
{
	UBehaviorData** bPtr = mBehaviorDataMap.Find(_id);
	if (bPtr == nullptr)
	{
		*bPtr = LoadBehaviorData(_id);
		if (*bPtr != nullptr)
			mBehaviorDataMap.Add(_id, *bPtr);
	}
	return *bPtr;
}

UBehaviorData* USkillMgr::LoadBehaviorData(int32 _id)
{
	return nullptr;
}
