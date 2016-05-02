
#pragma once

#include "Engine/DataTable.h"
#include "SkillInfo.generated.h"

USTRUCT(Blueprintable)
struct FSkillInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FSkillInfo();
	virtual ~FSkillInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mLockedType; //TODO: 技编数据 锁定 人or地
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mAttackDist; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mTolerance; //TODO: 技编数据 //子弹到targetLoc的容许误差
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mBulletSpeed; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mFlyDist; //TODO: 技编数据 子弹飞行距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mSkillType;	//TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		FString			mAttachPoint;//TODO: 技编数据 子弹绑定点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FSkillInfo")
		int32			mAnimType;//TODO: 技编数据 相同类型动画的不同动作枚举

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
};
