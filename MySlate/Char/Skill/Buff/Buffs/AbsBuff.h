
#pragma once

#include "../../SkillTypes.h"
#include "AbsBuff.generated.h"

class UAbsPkEvent;
class AMyChar;
class UBufflTemplate;
class UPkMsg;

UCLASS()
class UAbsBuff : public UObject
{
	GENERATED_BODY()

public:
	UAbsBuff();
	virtual ~UAbsBuff();
	virtual void BeginDestroy() override;
	
	virtual void Tick(float DeltaSeconds);

	void BuffStart();
	void BuffOver();
	virtual void RunBeforePk(UPkMsg* msg);
	virtual void RunEndPk(UPkMsg* msg);

	AMyChar*	GetOwnerChar();
	UBufflTemplate*	GetBuffTemp() const { return mBuffTemp; }
	int32		GetBuffId() const { return mBuffId; }
	float		GetDtVal(float _value); //计算每帧伤害值
	void		ChangeState(EBuffState _state) { mBuffState = _state; }
	EBuffState	GetState() const { return mBuffState; }

	void		SetData(UBufflTemplate* _buffTemp, AMyChar* _attacker, AMyChar* _target, int32 _skillId);

private:
	int32		mBuffId;		//
	int32		mSkillId;		//
	//int32		mOwnerId;		//中招者
	AMyChar*	mOwnerChar;		//中招者ptr
	//int32		mAttackerId;	//释放者
	AMyChar*	mAttacker;		//释放者ptr //issue 释放这个可能有多个，这里先暂时一个
	UBufflTemplate*	mBuffTemp;

	float		mTimer;		//计数器
	float		mTotalTime;	//总时间
	int32		mLessTimes;	//剩余次数

	EBuffState	mBuffState;		//buff状态

	TArray<int32>	mEffectUUids;
};
