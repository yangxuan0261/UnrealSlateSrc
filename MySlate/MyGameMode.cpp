#include "MySlate.h"
#include "MyGameMode.h"

#include "./Slate/StandardHUD.h"
#include "./Player/MyPlayerCtrler.h"
#include "./MyGameState.h"

AMyGameMode::AMyGameMode() : Super()
{
	////Set the hud class to use our custom HUD by default.
	//HUDClass = AStandardHUD::StaticClass();

	// use our custom PlayerController class
	//PlayerControllerClass = AMyPlayerCtrler::StaticClass();

	//// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	//if (PlayerPawnBPClass.Class != NULL)
	//{
	//	DefaultPawnClass = PlayerPawnBPClass.Class;
	//}
}

AMyGameMode::~AMyGameMode()
{
	UE_LOG(GameLogger, Warning, TEXT("AMyGameMode::~AMyGameMode"));
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
}

void AMyGameMode::InitGameState()
{
	Super::InitGameState();

	AMyGameState* gameState = GetGameState<AMyGameState>();
	if (gameState != nullptr)
	{
		gameState->StartGame();
	}
}

//void AMyGameMode::RestartPlayer(AController* NewPlayer)
//{
//	AActor* const StartSpot = FindPlayerStart(NewPlayer);
//	if (StartSpot != nullptr)
//	{
//		// initialize and start it up
//		InitStartSpot(StartSpot, NewPlayer);
//
//		AMyPlayerCtrler* const NewPC = Cast<AMyPlayerCtrler>(NewPlayer);
//		if (NewPC != nullptr)
//		{
//			NewPC->SetInitialLocationAndRotation(StartSpot->GetActorLocation(), StartSpot->GetActorRotation());
//		}
//	}
//	else
//	{
//		UE_LOG(GameLogger, Warning, TEXT("Player start not found, failed to restart player"));
//	}
//}

void AMyGameMode::RestartGame()
{
	Super::RestartGame();
}

void AMyGameMode::BeginDestroy()
{
	UE_LOG(GameLogger, Warning, TEXT("Player start not found, failed to restart player"));
	Super::BeginDestroy();
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
