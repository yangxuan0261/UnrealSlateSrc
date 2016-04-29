
#pragma once

#include "../../../Common/CommonHeader.h"
#include "../SkillTypes.h"
#include "../Utils/CommonDef.h"

#include "SkillTemplate.generated.h"

class UAbsPkEvent;
class UAbsFilter;

UCLASS(Blueprintable, BlueprintType)
class USkillTemplate : public UObject
{
	GENERATED_BODY()

public:
	USkillTemplate();
	virtual ~USkillTemplate();
	virtual void BeginDestroy() override;

	void ReleaseArray(TArray<UAbsPkEvent*>& _arr);
public:
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	int32			GetId() { return mId; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetName() { return mName; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	FString			GetDescr() { return mDescr; }
	//UFUNCTION(BlueprintCallable, Category = "USkillTemplate")
	//	float			GetCoolDown() { return mCoolDown; }

public:
	//before类 都是给攻击者提升攻击力、加buff、做动作的func
	const TArray<UAbsPkEvent*>& GetBeforeSkill();
	const TArray<UAbsPkEvent*>& GetBeforePk();
	const TArray<UAbsPkEvent*>& GetBeforeEvns();
	const TArray<UAbsPkEvent*>& GetEndEvns();
	const TArray<UAbsPkEvent*>& GetEndPk();
	const TArray<UAbsPkEvent*>& GetEndSkill();
	UAbsFilter*	GetFilter();

	void ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr);
	void ParseFilterStr(const FString& _filterStr);
public:
	TArray<UAbsPkEvent*> mBeforeSkill;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mBeforeEvns;
	TArray<UAbsPkEvent*> mEndEvns;
	TArray<UAbsPkEvent*> mEndPk;
	TArray<UAbsPkEvent*> mEndSkill;
	UAbsFilter*		mFilter;
public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		ELockedType		mLockedType; //TODO: 技编数据 锁定 人or地
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mAttackDist; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mTolerance; //TODO: 技编数据 //子弹到targetLoc的容许误差
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mBulletSpeed; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mFlyDist; //TODO: 技编数据 子弹飞行距离
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		ESkillType		mSkillType;	//TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mAttachPoint;//TODO: 技编数据 子弹绑定点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		EAnimType		mAnimType;//TODO: 技编数据 相同类型动画的不同动作枚举

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mFilterStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeSkillStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforeEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndEvnsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndPkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndSkillStr;
};
