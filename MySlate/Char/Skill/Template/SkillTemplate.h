// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"
#include "Char/Skill/SkillTypes.h"
#include "../Utils/CommonDef.h"

#include "SkillTemplate.generated.h"

class UAbsPkEvent;
class UAbsFilter;

UENUM()
enum class EAnimType : uint8 //技能动画
{
	None = 0,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Skill_5,
	Skill_6,
	Skill_7,
	Injure_1,
	Injure_2,
	Victory_1,
	Victory_2,
	Victory_3,
	Count,
};

UCLASS()
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mCoolDown;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mAttackDist; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mTolerance; //TODO: 技编数据 //子弹到targetLoc的容许误差
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mBulletSpeed; //TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		float			mFlyDist; //TODO: 技编数据 子弹飞行距离
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		ESkillType		mSkillType;	//TODO: 技编数据
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		FString			mAttachPoint;//TODO: 技编数据 子弹绑定点
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "USkillTemplate")
		EAnimType		mAnimType;//TODO: 技编数据 相同类型动画的不同动作枚举

	FString	mFilterStr;
	FString mBeforeSkillStr;
	FString mBeforePkStr;
	FString mBeforeEvnsStr;
	FString mEndEvnsStr;
	FString mEndPkStr;
	FString mEndSkillStr;
};
