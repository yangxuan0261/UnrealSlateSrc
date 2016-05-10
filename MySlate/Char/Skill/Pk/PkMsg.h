
#pragma once

#include "Char/Skill/SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "Char/GameTypes.h"

#include "PkMsg.generated.h"

class AMyChar;
class USkillTemplate;
class UFightData;

UCLASS()
class UParam : public UObject, public IObjInterface
{
	GENERATED_BODY()
public:
	UParam();
	virtual ~UParam();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

	void Init();

	UFightData*		mFightData;			//战斗数据
	AMyChar*		mTarget;			//目标

	float			mDmgPhyValue = 0.0f;						//物理总伤害
	float			mDmgMagValue = 0.0f;						//法术总伤害
};

UCLASS()
class UPkMsg : public UObject, public IObjInterface
{
	GENERATED_BODY()
public:
	UPkMsg();
	virtual ~UPkMsg();
	void virtual BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

	void	SetData(USkillTemplate* _skillTemp, AMyChar* _attacker, AMyChar* _target, const FVector& _targetLoc);
	const TArray<UParam*>& GetTargets() const { return mTargetArr; }
	void	AddTarget(AMyChar* _char);
	USkillTemplate*	GetSkillTemp() const { return mSkillTemp; }

	//void	ExeNullDlg();
	void	SetAttackerData(UFightData* _data);
	UFightData*	GetAttackerData() const { return mAttackerData; }
	AMyChar*	GetAttacker() const { return mAttacker; }
	void	SetTarget(AMyChar* _char) {  mTargetLocked = _char; } //设置被锁定的目标
	AMyChar*	GetTarget() const { return mTargetLocked; }
	void	SetTargetLoc(const FVector& _Loc) { mTargetLoc = _Loc; } //设置被锁定的Loc
	const FVector&	GetTargetLoc() const { return mTargetLoc; }
	int32	GetTargetId() const { return mTargetId; }
	void	SetTargetId(int32 _id) { mTargetId = _id; }
	void	SetAttackerTeam(const ETeam& _type) { mTeamType = _type; }
	const ETeam&	GetAttackerTeam() const { return mTeamType; }
	void	SetCurrTarget(UParam* _target);
	UParam*	GetCurrTarget() const { return mCurrTarget; }

	//--------------- Begin
	void SetAttackDmgValue(float _value, int _limitId = -1, bool _isAdd = true);			//伤害增加(数值)(受击者)

	//--------------- Begin
private:
	bool			mCanLog;
	int32			mSkillId;						//技能id
	USkillTemplate*	mSkillTemp;		
	ESkillAttackType	mSkillLogicType;			//技能逻辑类型 SKILL_ATTACK_TYPE
	int32			mAttackerId;					//攻击者 唯一id
	AMyChar*		mAttacker;						//攻击者
	int32			mTargetId;						//锁定目标者 唯一id
	AMyChar*		mTargetLocked;					//锁定目标者
	TArray<UParam*>	mTargetArr;						//目标集
	UParam*			mCurrTarget;					//目标集的每个个体临时指针
	UFightData*		mAttackerData;					//攻击者参数
	UFightData*		mAttackerDataForCacul;			//攻击者参数,用于计算
	FVector			mTargetLoc;						//目标位置
	ETeam			mTeamType;						//攻击者队伍标记
};
