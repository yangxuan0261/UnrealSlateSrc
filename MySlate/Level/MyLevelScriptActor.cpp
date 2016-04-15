// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyLevelScriptActor.h"

AMyLevelScriptActor::AMyLevelScriptActor()
	: Counter(0)
	, SolusLevelName("")        
{
}

void AMyLevelScriptActor::BeginPlay()
{
	FString str = FString::Printf(TEXT("--- AMyLevelScriptActor::BeginPlay()-%d"), 1);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	Super::BeginPlay();
	FString str2 = FString::Printf(TEXT("--- AMyLevelScriptActor::BeginPlay()-%d"), 2);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str2);

}

void AMyLevelScriptActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
}

void AMyLevelScriptActor::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	Counter++;
}

void AMyLevelScriptActor::SolusLevel_UpdateLevelSaveData()
{
}
