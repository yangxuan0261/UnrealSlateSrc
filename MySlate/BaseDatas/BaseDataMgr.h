/*
基础数据管理器
*/
#pragma once

#include "../Common/ISingleton.h"
#include "BaseDataMgr.generated.h"

class UCharData;

UCLASS()
class UBaseDataMgr : public UObject, public USingleton<UBaseDataMgr>
{
	GENERATED_BODY()

public:
	UBaseDataMgr();
	virtual ~UBaseDataMgr();
	virtual void BeginDestroy() override;

	void LoadCharData();

public:
	UFUNCTION(BlueprintCallable, Category = "UBaseDataMgr")
		UCharData*		CreateCharData(int32 _id);

private:
	void InitFakeData();

public:
	UCharData*		GetCharData(int32 _id);
public:
	TMap<int32, UCharData*> mCharDataMap;
};
