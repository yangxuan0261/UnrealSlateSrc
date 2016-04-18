// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyCharDataComp.h"

#include "../Skill/Pk/FightData.h"
#include "BaseDatas/Datas/CharData.h"

UMyCharDataComp::UMyCharDataComp()
	: Super()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	bAllowAnyoneToDestroyMe = true;

	mGroup = EGroup::None;
	mTeam = ETeam::None;
	mHealth = 100.f;
	mFightData = nullptr;
	mCharData = nullptr;
}

UMyCharDataComp::~UMyCharDataComp()
{
	UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::~UMyCharDataComp"));
	if (mFightData != nullptr)
	{
		mFightData->RemoveFromRoot();
		mFightData = nullptr;
	}
}

void UMyCharDataComp::BeginPlay()
{
	Super::BeginPlay();
	mFightData = NewObject<UFightData>(UFightData::StaticClass());//战斗时数据对象
	mFightData->AddToRoot();
}

void UMyCharDataComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::TickComponent"));
}

void UMyCharDataComp::SetCharData(UCharData* _data)
{
	mCharData = _data;
	mFightData->Copy(mCharData->GetFightData());//角色模板中的基础数据拷到 战斗数据对象中
}

void UMyCharDataComp::BeginDestroy()
{
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::BeginDestroy"));
	Super::BeginDestroy();
}

