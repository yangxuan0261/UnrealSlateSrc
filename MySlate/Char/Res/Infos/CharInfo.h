
#pragma once

#include "Engine/DataTable.h"
#include "CharInfo.generated.h"

USTRUCT()
struct FFightDataInfo
{
	GENERATED_USTRUCT_BODY()
public:
	FFightDataInfo();
	virtual ~FFightDataInfo();

public:
	//原始属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mAttackPhy;		//物理攻击

public:
	//成长相关
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		int			mLv;			//等级
};

USTRUCT(Blueprintable)
struct FCharInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FCharInfo();
	virtual ~FCharInfo();

public:
	//读表属性
		int32		mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FString		mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FString		mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mHeathMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		float		mWarnRange;

	//----------- 战斗数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FCharInfo")
		FFightDataInfo	mFightInfo;


};
