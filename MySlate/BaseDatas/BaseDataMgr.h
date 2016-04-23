/*
基础数据管理器
*/
#pragma once

#include "Common/ISingleton.h"
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

	void InitFakeData();
	void LoadCharData();

public:
	UCharData*		GetCharData(int32 _id);
public:
	TMap<int32, UCharData*> mCharDataMap;
};
