// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"

#include "PkMsg.generated.h"

class AMyChar;

class UParam
{
	UParam()
	{
		mFightData = NewObject<UFightData>(UFightData::StaticClass());
		mFightData->AddToRoot();
	}
	~UParam() { mFightData->RemoveFromRoot(); }

	UFightData*		mFightData;			//战斗数据
	int32			mTargetId;
};

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

	const TArray<UParam*>& GetTargets() const { return mTargetArr; }

private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	ESkillAttackType	mSkillLogicType;				//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	int32			mTargetId;						//锁定目标者 唯一id
	TArray<UParam*>	mTargetArr;						//目标集
	UFightData*		mAttackerData;					//攻击者参数，不用指针是防止攻击死亡的情况
};
