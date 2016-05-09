
#pragma once

#include "Engine/DataTable.h"
#include "../../Skill/SkillTypes.h"
#include "BehavInfo.generated.h"

USTRUCT(Blueprintable)
struct FEffElemInfo : public FTableRowBase		//特效
{
	GENERATED_USTRUCT_BODY()
public:
	FEffElemInfo();
	virtual ~FEffElemInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mResId;					//粒子资源id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//所属者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EFollowType	mFollowType;			//
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FString		mBindPoint;				//绑定骨骼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;				//延时时长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mLoc;					//矩阵信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FRotator	mRotate;
};

USTRUCT(Blueprintable)
struct FShakeInfo : public FTableRowBase		//振动
{
	GENERATED_USTRUCT_BODY()
public:
	FShakeInfo();
	virtual ~FShakeInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mA;						//振幅
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mW;						//角速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mTime;					//持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		bool		mIsX;					//X方向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//所属者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;				//延时时长
};

USTRUCT(Blueprintable)
struct FBehavInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBehavInfo();
	virtual ~FBehavInfo();

public:
	//读表属性
	int32		mId;//表现id

	//攻击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mAtkEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mAtkShkVec;

	//子弹者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mBltEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mBltShkVec;

	//受击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mTarEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mTarShkVec;

	//场景
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mSceEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FShakeInfo>		mSceShkVec;
};
