// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"
#include "FightData.h"
#include "Char/GameTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;

DECLARE_DELEGATE(FSetNullDlg);

UCLASS()
class UParam : public UObject
{
	GENERATED_BODY()
public:
	UParam();
	virtual ~UParam();
	void Init();

	UFightData*		mFightData;			//战斗数据
	AMyChar*		mTarget;			//目标

};

UCLASS()
class UPkMsg : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UPkMsg();
	virtual ~UPkMsg();

	void	SetData(USkillTemplate* _skillTemp, const FVector& _targetLoc, int32 _attackerId, int32 _targetId = 0);
	const TArray<UParam*>& GetTargets() const { return mTargetArr; }
	void	AddTarget(AMyChar* _char);
	USkillTemplate*	GetSkillTemp() const { return mSkillTemp; }

	void	SetNullDlg(FSetNullDlg _dlg) { mSetNullDlg = _dlg; }
	void	ExeNullDlg();
	void	SetAttackerData(UFightData* _data) { mAttackerData = _data; }

private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;				//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	int32			mTargetId;						//锁定目标者 唯一id
	AMyChar*		mTarget;
	TArray<UParam*>	mTargetArr;						//目标集
	UFightData*		mAttackerData;					//攻击者参数
	FVector			mTargetLoc;						//目标位置
	ETeam			mTeamType;						//敌友标记

	FSetNullDlg		mSetNullDlg;		//运用别处释放对象时，通知之前创建的地方set null
};
