// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../SkillTypes.h"
#include "PkPorcess.generated.h"

class UPkMsg;
struct DamageInfo;

DECLARE_DELEGATE_OneParam(PkProcessCallBack, TArray<DamageInfo>&);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

struct DamageInfo
{
	int32 targetUniqueId = 0;//目标唯一id
	ESkillAttackType type;				//伤害类型 (物理伤害、魔法伤害、治疗、吸血)
	float value = 0;			//伤害值
	bool isDodge = false;		//闪避
	bool isCrit = false;		//暴击
	bool isPhyDmgImmunity = false;//物理免疫
	bool isMagDmgImmunity = false;//魔法免疫
};

UCLASS()
class UPkPorcess : public UObject
{
	GENERATED_BODY()
public:


public:
	UPkPorcess();
	virtual ~UPkPorcess();

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();

private:
	bool CheckCanPk();//判断能否pk
	void FilterVS();//选取攻击对象逻辑

	void RunBeforePk();// 第一个循环 运行buff前置事件 一般用于放技能前要buff
	void RunBeforeSkill(); //pk逻辑完成前技能逻辑
	void PkLogic();// pk逻辑运算，之前的方法已把对象消耗的值算好，这里不用再计算，直接进行逻辑运算即可
	void RunEndSkill();//pk逻辑完成后技能逻辑，如吸血，加蓝等
	void RunEndPk();//运行完buff后置事件
	void PkPrice();//奖历分配，组织协议，是否战斗已结束

private:
	UPkMsg* mPkMsg;
	PkProcessCallBack m_callBack;
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
