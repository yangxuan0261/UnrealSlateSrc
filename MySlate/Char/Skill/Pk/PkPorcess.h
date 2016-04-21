// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SkillTypes.h"
#include "PkPorcess.generated.h"

class UPkMsg;
struct FDamageInfo;

DECLARE_DELEGATE_OneParam(FPkOverDlg, TArray<FDamageInfo>&);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

USTRUCT()
struct FDamageInfo
{
	GENERATED_BODY()

public:
	FDamageInfo()
	{
		mTargetId = 0;
		mValue = 0.f;
		mIsDodge = false;
		mIsCrit = false;
		mIsPhyDmgImmunity = false;
		mIsMagDmgImmunity = false;
	}

	int32	mTargetId;//目标唯一id
	ESkillAttackType	type;		//伤害类型 (物理伤害、魔法伤害、治疗、吸血)
	float	mValue;				//伤害值
	bool	mIsDodge;			//闪避
	bool	mIsCrit;			//暴击
	bool	mIsPhyDmgImmunity;	//物理免疫
	bool	mIsMagDmgImmunity;	//魔法免疫
};

UCLASS()
class UPkPorcess : public UObject
{
	GENERATED_BODY()
public:
	UPkPorcess();
	virtual ~UPkPorcess();
	virtual void BeginDestroy() override;

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();
	FPkOverDlg&	GetPkOverDlg() { return mCallBack; }

private:
	bool CheckCanPk();//判断能否pk
	void Filter();//选取攻击对象逻辑
	void RunEndEvns(); 

	void PkLogic();// pk逻辑运算，之前的方法已把对象消耗的值算好，这里不用再计算，直接进行逻辑运算即可
	void RunEndPk();//
	void PkPrice();//奖历分配，组织协议，是否战斗已结束

private:
	UPkMsg* mPkMsg;
	FPkOverDlg mCallBack; //结算完的回调
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
