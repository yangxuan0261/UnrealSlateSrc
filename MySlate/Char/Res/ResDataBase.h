
#pragma once

#include "ResDataBase.generated.h"

USTRUCT()
struct FMeshItem
{
	GENERATED_USTRUCT_BODY()
public:
	FMeshItem()
	{
		mId = 0;
		mMeshAsset = FStringAssetReference("");
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMeshItem")
		int32 mId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMeshItem")
		TAssetPtr<USkeletalMesh> mMeshAsset;
};

USTRUCT()
struct FParticleItem
{
	GENERATED_USTRUCT_BODY()
public:
	FParticleItem()
	{
		mId = 0;
		mParticleAsset = FStringAssetReference("");
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FParticleItem")
		int32 mId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FParticleItem")
		TAssetPtr<UParticleSystem> mParticleAsset;
};

UCLASS()
class UResDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UResDataBase();
	virtual ~UResDataBase();
	virtual void BeginDestroy() override;

	TArray<FParticleItem>&		GetParticles() { return mParticleList; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TArray<FMeshItem> mMeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TArray<FParticleItem> mParticleList;

private:

	//TMap<int32, UBehaviorData*>		mBehaviorDataMap;//存放技能数据
};
