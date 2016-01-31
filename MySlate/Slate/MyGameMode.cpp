// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyGameMode.h"

#include "StandardHUD.h"
#include "MySlatePlayerController.h"

AMyGameMode::AMyGameMode() : Super()
{
	//Set the hud class to use our custom HUD by default.
	HUDClass = AStandardHUD::StaticClass();

	// use our custom PlayerController class
	PlayerControllerClass = AMySlatePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}