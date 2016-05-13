// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyGameMode.h"

#include "./StandardHUD.h"
#include "./MyPlayerCtrler.h"

AMyGameMode::AMyGameMode() : Super()
{
	////Set the hud class to use our custom HUD by default.
	//HUDClass = AStandardHUD::StaticClass();

	//// use our custom PlayerController class
	//PlayerControllerClass = AMySlatePlayerController::StaticClass();

	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

void AMyGameMode::solspeed()
{
	FString str = FString::Printf(TEXT("--- AMyGameMode::solspeed - %d"), 789);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
}

void AMyGameMode::solname(FString _str, int32 _num)
{
	FString str = FString::Printf(TEXT("--- %s - %d"), *_str, _num);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
}
