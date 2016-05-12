
#pragma once

#include "ResDataBase.generated.h"

class UDataTable;

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
struct FStaticMeshItem
{
	GENERATED_USTRUCT_BODY()
public:
	FStaticMeshItem()
	{
		mId = 0;
		mMeshAsset = FStringAssetReference("");
	}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMeshItem")
		int32 mId;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FMeshItem")
		TAssetPtr<UStaticMesh> mMeshAsset;
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
	UResDataBase();
	virtual ~UResDataBase();
	virtual void BeginDestroy() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TArray<FMeshItem>		mMeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TArray<FParticleItem>	mParticleList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TArray<FStaticMeshItem>	mStaticMeshList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TAssetPtr<UDataTable>	mSkillInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TAssetPtr<UDataTable>	mBuffInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TAssetPtr<UDataTable>	mBehavInfo;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UResMgr")
		TAssetPtr<UDataTable>	mCharInfo;

private:

	//TMap<int32, UBehaviorData*>		mBehaviorDataMap;//存放技能数据
};
