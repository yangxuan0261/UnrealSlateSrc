
#pragma once

#include "Engine/DataTable.h"
#include "../../Skill/SkillTypes.h"
#include "SkillInfo.generated.h"

USTRUCT(Blueprintable)
struct FBulletInfo : public FTableRowBase		//振动
{
	GENERATED_USTRUCT_BODY()
public:
	FBulletInfo();
	virtual ~FBulletInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		ELockedType		mLockedType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		FString			mAttachPoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		int32			mTolerance;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		int32			mBulletSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		int32			mFlyDist;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		FVector			mLoc;					//矩阵信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		FVector			mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBulletInfo")
		FRotator		mRotate;
};

USTRUCT(Blueprintable)
struct FSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FSkillInfo();
	virtual ~FSkillInfo();

public:
	//读表属性
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mAttackDist; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		ESkillType		mSkillType;	//TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		EAnimType		mAnimType;//相同类型动画的不同动作枚举
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mBehavId; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mFilterStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforeSkillStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mBeforeEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndPkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mEndSkillStr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FBulletInfo		mBltInfo;
};
