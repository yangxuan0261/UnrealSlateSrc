
#include "MySlate.h"
#include "ResMgr.h"

#include "./ResDataBase.h"
#include "./TestData.h"

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

void UResMgr::TestloadCSV()
{
	UObject* obj = mAssetLoader->SynchronousLoad(mResDB->mTestData.ToStringReference());
	UDataTable* data = Cast<UDataTable>(obj);
	if (data != nullptr)
	{
		UE_LOG(ResLogger, Warning, TEXT("--- UResMgr::TestloadCSV success"));
		FTestData* tmpPtr = nullptr;
		for (auto it : data->RowMap)
		{
			// it.Key has the key from first column of the CSV file
			// it.Value has a pointer to a struct of data. You can safely cast it to your actual type, e.g FMyStruct* data = (FMyStruct*)(it.Value);
			tmpPtr = (FTestData*)(it.Value);
			UE_LOG(ResLogger, Warning, TEXT("--- row:%s, key:%d, name:%s"), *it.Key.ToString(), tmpPtr->mId, *tmpPtr->mName);
		}
	}
}

UParticleSystem* UResMgr::GetParticle(int32 _id)
{
	TArray<FParticleItem>& parArr = mResDB->GetParticles();
	FParticleItem* result = parArr.FindByPredicate([&](const FParticleItem& _pi)->bool {
		return _pi.mId == _id;
	});

	UParticleSystem* dstps = nullptr;
	if (result != nullptr)
	{
		UObject* obj = mAssetLoader->SynchronousLoad(result->mParticleAsset.ToStringReference());
		dstps = obj != nullptr ? Cast<UParticleSystem>(obj) : nullptr;
	}

	return dstps;
}

