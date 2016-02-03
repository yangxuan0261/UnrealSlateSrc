// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBpFuncLib.h"

#include "MyChar.h"
#include "Animation/AnimBlueprint.h"
#include "Engine/StreamableManager.h"
#include "Engine.h"
#include "Engine/LevelStreamingKismet.h"

bool UMyBpFuncLib::TestChangeCharAnimInstance(AMyChar* _myChar, FString _pathMesh, FString _pathAnim)
{

	FStreamableManager* stream = new FStreamableManager();
	FStringAssetReference ref1(*_pathMesh);
	USkeletalMesh* TmpMesh = Cast<USkeletalMesh>(stream->SynchronousLoad(ref1));
	_myChar->GetMesh()->SetSkeletalMesh(TmpMesh);

	FStringAssetReference ref2(*_pathAnim);
	UAnimBlueprint* TmpMeshAnim = Cast<UAnimBlueprint>(stream->SynchronousLoad(ref2));
	_myChar->GetMesh()->SetAnimInstanceClass((UClass*)TmpMeshAnim->GetAnimBlueprintGeneratedClass());
	delete stream;
	return true;
}

bool UMyBpFuncLib::VictoryLoadLevelInstance(UObject * WorldContextObject, FString mapPath, int32 InstanceNumber, FVector Location, FRotator Rotation)
{
	if (!WorldContextObject) return false;

	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World) return false;
	//~~~~~~~~~~~

	//Full Name
	FString FullName = mapPath;

	FName LevelFName = FName(*FullName);
	FString PackageFileName = FullName;

	ULevelStreamingKismet* StreamingLevel = NewObject<ULevelStreamingKismet>((UObject*)GetTransientPackage(), ULevelStreamingKismet::StaticClass());

	if (!StreamingLevel)
	{
		return false;
	}

	//Long Package Name
	FString LongLevelPackageName = FPackageName::FilenameToLongPackageName(PackageFileName);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Here is where a unique name is chosen for the new level asset
	//    Ensure unique names to gain ability to have multiple instances of same level!
	//	   <3 Rama

	//Create Unique Name based on BP-supplied instance value
	FString UniqueLevelPackageName = LongLevelPackageName;
	UniqueLevelPackageName += "_VictoryInstance_" + FString::FromInt(InstanceNumber);
	//Set!// Associate a package name.
	StreamingLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (World->IsPlayInEditor())
	{
		FWorldContext WorldContext = GEngine->GetWorldContextFromWorldChecked(World);
		StreamingLevel->RenameForPIE(WorldContext.PIEInstance);
	}

	StreamingLevel->LevelColor = FColor::MakeRandomColor();
	StreamingLevel->bShouldBeLoaded = true;
	StreamingLevel->bShouldBeVisible = true;
	StreamingLevel->bShouldBlockOnLoad = false;
	StreamingLevel->bInitiallyLoaded = true;
	StreamingLevel->bInitiallyVisible = true;

	//Transform
	StreamingLevel->LevelTransform = FTransform(Rotation, Location);
	StreamingLevel->PackageNameToLoad = LevelFName;

	if (!FPackageName::DoesPackageExist(StreamingLevel->PackageNameToLoad.ToString(), NULL, &PackageFileName))
	{
		return false;
	}

	//~~~

	//Actual map package to load
	StreamingLevel->PackageNameToLoad = FName(*LongLevelPackageName);

	//~~~

	// Add the new level to world.
	World->StreamingLevels.Add(StreamingLevel);

	//UGameplayStatics::OpenLevel((UObject*s) );
	return false;
}

void UMyBpFuncLib::TestNSLocatext(int32 _dayCount, int32 _hp)
{
	FFormatNamedArguments Args;
	Args.Add("DayCount", _dayCount);
	Args.Add("Hp", _hp);
	FText txt1 = FText::Format(NSLOCTEXT("Solus", "Day", "--- Day1 {DayCount}"), Args);
	FText txt2 = FText::Format(NSLOCTEXT("Solus", "HP", "--- HP1 {Hp}"), Args);

	FFormatOrderedArguments Args2;
	Args2.Add(_dayCount);
	Args2.Add(_hp);
	FText txt3 = FText::Format(NSLOCTEXT("Solus", "Day", "--- Day2 {0}"), Args2);
	FText txt4 = FText::Format(NSLOCTEXT("Solus", "HP", "--- HP2 {1}"), Args2);


	FString str = txt1.ToString()
		+ TEXT("\n")
		+ txt2.ToString()
		+ TEXT("\n")
		+ txt3.ToString()
		+ TEXT("\n")
		+ txt4.ToString();
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
}
