#pragma once

#include "Engine/DataAsset.h"
#include "ItemInfoDatabase.generated.h"

USTRUCT()
struct FVCharPartInfo
{
	GENERATED_USTRUCT_BODY()
	UPROPERTY(EditAnywhere, Category = "DATA")
		int32 MeshID;

	UPROPERTY(EditAnywhere, Category = "DATA")
		TAssetPtr<USkeletalMesh> MeshResource;

	FVCharPartInfo()
	{
		MeshID = 0;
		MeshResource = FStringAssetReference("");
	}
};

//Holds a dynamic collection of character parts
UCLASS(BlueprintType)
class UItemInfoDatabase : public UDataAsset
{
	GENERATED_UCLASS_BODY()
	UPROPERTY(EditAnywhere, Category = "Model List") //Exposes the array as editable on editor
	TArray<FVCharPartInfo> MeshList;

public:
	UItemInfoDatabase();
};