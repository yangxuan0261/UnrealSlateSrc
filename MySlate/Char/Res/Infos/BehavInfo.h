
#pragma once

#include "Engine/DataTable.h"
#include "../../Skill/SkillTypes.h"
#include "BehavInfo.generated.h"

USTRUCT(Blueprintable)
struct FEffElemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FEffElemInfo();
	virtual ~FEffElemInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mResId;					//粒子资源id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		ESkillEffectType		mEffectType;	//特效类型
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FString		mBindPoint;				//绑定骨骼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		float		mDelayTime;			//延时时长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mLoc;					//矩阵信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		FRotator	mRotate;
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		TArray<FEffElemInfo>	mEffectVec;
};
