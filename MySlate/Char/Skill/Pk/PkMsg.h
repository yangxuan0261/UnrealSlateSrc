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

	float			mDmgPhyValue = 0.0f;						//物理总伤害
	float			mDmgMagValue = 0.0f;						//法术总伤害

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

	void	SetNullDlg(const FSetNullDlg& _dlg) { mSetNullDlg = _dlg; }
	void	ExeNullDlg();
	void	SetAttackerData(UFightData* _data);
	UFightData*	GetAttackerData() const { return mAttackerData; }
	void	SetAttackerId(int32 _id) { mAttackerId = _id; }
	int32	GetAttackerId() const { return mAttackerId;}
	void	SetAttackerTeam(const ETeam& _type) { mTeamType = _type; }
	const ETeam&	GetAttackerTeam() const { return mTeamType; }
	void	SetCurrTarget(UParam* _target);

	//--------------- Begin
	void SetAttackDmgValue(float _value, int _limitId = -1, bool _isAdd = true);			//伤害增加(数值)(受击者)

	//--------------- Begin
private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;				//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	int32			mTargetId;						//锁定目标者 唯一id
	AMyChar*		mTarget;
	TArray<UParam*>	mTargetArr;						//目标集
	UParam*			mCurrTarget;					//目标集的每个个体临时指针
	UFightData*		mAttackerData;					//攻击者参数
	UFightData*		mAttackerDataForCacul;			//攻击者参数,用于计算
	FVector			mTargetLoc;						//目标位置
	ETeam			mTeamType;						//攻击者队伍标记

	FSetNullDlg		mSetNullDlg;		//运用别处释放对象时，通知之前创建的地方set null
};
