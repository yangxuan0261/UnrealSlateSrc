#pragma once

#include "Engine/StreamableManager.h"
#include "SolusDataSingleton.generated.h"

UCLASS(Blueprintable, BlueprintType)
class USolusDataSingleton : public UObject
{
	GENERATED_BODY()
public:
	USolusDataSingleton(const FObjectInitializer& ObjectInitializer);

	static USolusDataSingleton* Get(); 	// Get method to access this object
	FStreamableManager AssetLoader;		// Your asset loader

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		TArray<UClass*> SolusTreeBlueprints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		UTexture2D* SolusT2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		FVector SolusEssentialVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		FString SolusCoreFilePath;
};