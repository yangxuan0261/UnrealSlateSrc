// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyCharDataComp.h"

UMyCharDataComp::UMyCharDataComp()
	: Super()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	bAllowAnyoneToDestroyMe = true;

	mGroup = EGroup::None;
	mTeam = ETeam::None;
	mHealth = 100.f;
}

UMyCharDataComp::~UMyCharDataComp()
{
	UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::~UMyCharDataComp"));
}

void UMyCharDataComp::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::BeginPlay"));
}

void UMyCharDataComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::TickComponent"));
}

void UMyCharDataComp::BeginDestroy()
{
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::BeginDestroy"));
	Super::BeginDestroy();
}

