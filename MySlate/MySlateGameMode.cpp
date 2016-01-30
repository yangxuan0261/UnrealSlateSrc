// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MySlate.h"
#include "MySlateGameMode.h"
#include "MySlatePlayerController.h"
#include "MySlateCharacter.h"

AMySlateGameMode::AMySlateGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AMySlatePlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}