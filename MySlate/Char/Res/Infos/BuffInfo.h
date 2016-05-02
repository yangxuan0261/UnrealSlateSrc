
#pragma once

#include "Engine/DataTable.h"
#include "BuffInfo.generated.h"

USTRUCT(Blueprintable)
struct FBuffInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBuffInfo();
	virtual ~FBuffInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mBuffTime; //持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		bool			mCanDisperse; //是否驱散
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		bool			mCanAdd; //可否缀加
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mInterType; //buff周期性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		float			mInterTime; //buff周期性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		int32			mBehavDataId; //表现数据id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mAttrsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBuffInfo")
		FString			mEndPkStr;
};
