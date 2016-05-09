
#pragma once

#include "../../Common/ISingleton.h"
#include "ObjMgr.generated.h"

class AMyChar;
class AMyBullet;
class UFightData;

UCLASS()
class UObjMgr : public UObject, public USingleton<UObjMgr>
{
	GENERATED_BODY()

public:
	UObjMgr();
	virtual ~UObjMgr();
	virtual void BeginDestroy() override;

public:
	template<typename TRetType>
	TRetType*		GetObj(UClass* _cls);
	
	void			Recycle(UObject* _obj);

	UFightData*		GetFightData();
	auto&			GetObjMap() { return mObjMap; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<AMyChar>		mCharCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<AMyBullet>		mBulletCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UFightData>		mFightDataCls;

private:
	TMap<FString, TArray<UObject*>>		mObjMap;
};
