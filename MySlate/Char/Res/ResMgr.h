
#pragma once

#include "../../Common/ISingleton.h"
#include "ResMgr.generated.h"

struct FStreamableManager;
class UResDataBase;
class UDataTable;

UENUM()
enum class EInfoType : uint8 //加载不同表的枚举
{
	None = 0,
	Skill,
	Buff,
	Behav,
	Char,
};

UCLASS()
class UResMgr : public UObject, public USingleton<UResMgr>
{
	GENERATED_BODY()

public:
	UResMgr();
	virtual ~UResMgr();
	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UResMgr")
		void TestAsyncLoad();
	void AsyncCallback();

	FStreamableManager*		GetAssetLoader() const { return mAssetLoader; }
	UParticleSystem*		GetParticle(int32 _id);

	UDataTable*				GetInfoTable(EInfoType _infoType);

private:
	FStreamableManager*		mAssetLoader;
	UResDataBase*			mResDB;
};
