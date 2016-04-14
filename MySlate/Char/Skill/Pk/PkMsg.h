// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;

UCLASS()
class UParam : public UObject
{
	GENERATED_BODY()
public:
	UParam();
	virtual ~UParam();
	void Init();

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

	void	Init();
	void	SetData(int32 _skillId, const FVector& _targetLoc, int32 _attackerId, int32 _targetId = 0);
	const TArray<UParam*>& GetTargets() const { return mTargetArr; }
	void	AddTarget(AMyChar* _char);
	USkillTemplate*	GetSkillTemp() const { return mSkillTemp; }

private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;				//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	int32			mTargetId;						//锁定目标者 唯一id
	AMyChar*		mAttacker;
	AMyChar*		mTarget;
	TArray<UParam*>	mTargetArr;						//目标集
	UFightData*		mAttackerData;					//攻击者参数
	FVector			mTargetLoc;						//目标位置
};
