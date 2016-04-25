// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "ResMgr.h"

#include "ResDataBase.h"

UResMgr::UResMgr() : Super()
{
	mAssetLoader = new FStreamableManager();
	//加载UResDataBase蓝图类
	UObject* obj = mAssetLoader->SynchronousLoad(FStringAssetReference(TEXT("/Game/TopDownCPP/Blueprints/Data/ResDataBaseBp")));
	mResDB = Cast<UResDataBase>(obj);
	if ( mResDB != nullptr)
	{
		UE_LOG(ResLogger, Warning, TEXT("--- UResMgr::UResMgr, load ResDataBaseBp success"));
	}
}

UResMgr::~UResMgr()
{
	UE_LOG(ResLogger, Warning, TEXT("--- UResMgr::~UResMgr"));
}

void UResMgr::BeginDestroy()
{

	UE_LOG(ResLogger, Warning, TEXT("--- UResMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UResMgr::TestAsyncLoad()
{

	if (mAssetLoader == nullptr || mResDB == nullptr)
	{
		UE_LOG(ResLogger, Error, TEXT("--- UResMgr::TestAsyncLoad, mAssetLoader == nullptr || mResDB == nullptr"));
		return;
	}

	TArray<FStringAssetReference> objToLoad;
	for (int32 i = 0; i < mResDB->mMeshList.Num(); ++i)
	{
		objToLoad.AddUnique(mResDB->mMeshList[i].mMeshAsset.ToStringReference());
	}
	for (int32 i = 0; i < mResDB->mParticleList.Num(); ++i)
	{
		objToLoad.AddUnique(mResDB->mParticleList[i].mParticleAsset.ToStringReference());
	}

	//请求异步加载
	mAssetLoader->RequestAsyncLoad(objToLoad, FStreamableDelegate::CreateUObject(this, &UResMgr::AsyncCallback));
}

void UResMgr::AsyncCallback()
{
	UE_LOG(ResLogger, Warning, TEXT("--- UResMgr::AsyncCallback, assets load over"));
}

