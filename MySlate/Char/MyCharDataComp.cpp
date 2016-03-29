// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyCharDataComp.h"


DECLARE_LOG_CATEGORY_EXTERN(UCharDataLogger, Log, All);
DEFINE_LOG_CATEGORY(UCharDataLogger)

// Sets default values
UMyCharDataComp::UMyCharDataComp(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
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

}

void UMyCharDataComp::BeginPlay()
{
	Super::BeginPlay();
	//UE_LOG(UCharDataLogger, Warning, TEXT("--- UMyCharDataComp::BeginPlay"));
}

void UMyCharDataComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(UCharDataLogger, Warning, TEXT("--- UMyCharDataComp::TickComponent"));
}

void UMyCharDataComp::BeginDestroy()
{
	//UE_LOG(UCharDataLogger, Warning, TEXT("--- UMyCharDataComp::BeginDestroy"));
	Super::BeginDestroy();
}

