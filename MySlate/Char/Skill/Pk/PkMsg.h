// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class UFightData;

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	ESkillAttackType	mSkillLogicType;				//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	int32			mTargetId;						//锁定目标者 唯一id
	AMyChar*		mAttackerPtr;					//攻击者
	AMyChar*		mTargetPtr;						//锁定目标者
};
