// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyChar.h"

#include "MyGameInstance.h"
#include "Engine.h"
#include "Level/MyLevelScriptActor.h"

// Sets default values
AMyChar::AMyChar()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


}

// Called when the game starts or when spawned
void AMyChar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyChar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UMyGameInstance* mgi = Cast<UMyGameInstance>(GetGameInstance());
	if (mgi)
	{
		mgi->InterLevelPersistentValue++;
		//FString str = FString::Printf(TEXT("--- Cast myGameInstance Success - %d"), mgi->InterLevelPersistentValue);
		/*GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);*/
	}

	AMyLevelScriptActor* msa = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (msa)
	{
		FString str = FString::Printf(TEXT("--- Cast AMyLevelScriptActor Success - %d"), msa->Counter);
		//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	}

}

// Called to bind functionality to input
void AMyChar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

