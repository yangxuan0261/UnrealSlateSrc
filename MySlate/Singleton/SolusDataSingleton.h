#pragma once

#include "SolusDataSingleton.generated.h"

struct FStreamableManager;
class UItemInfoDatabase;

UCLASS(Blueprintable, BlueprintType)
class USolusDataSingleton : public UObject
{
	GENERATED_BODY()
public:
	USolusDataSingleton(const FObjectInitializer& ObjectInitializer);
	virtual ~USolusDataSingleton();

	static USolusDataSingleton* Get(); 	// Get method to access this object
	struct FStreamableManager* AssetLoader;		// Your asset loader
	class UItemInfoDatabase* ItemDatabase;		

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		TArray<UClass*> SolusTreeBlueprints;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		UTexture2D* SolusT2D;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		FVector SolusEssentialVector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Solus Data Singleton")
		FString SolusCoreFilePath;
};