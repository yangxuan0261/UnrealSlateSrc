
#pragma once

#include "../SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "PkProcess.generated.h"

class UPkMsg;
class UDamageInfo;
class AMyChar;

DECLARE_DELEGATE_OneParam(FPkOverDlg, TArray<UDamageInfo*>);
DECLARE_DELEGATE_OneParam(RunSkillBeforeCallBack, UPkMsg*);

UCLASS()
class UDamageInfo : public UObject, public IObjInterface
{
	GENERATED_BODY()

public:
	UDamageInfo();
	virtual ~UDamageInfo();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

	int32		mTargetId;			//目标唯一id
	AMyChar*	mTarget;		//目标
	ESkillAtkType	type;	//伤害类型 (物理伤害、魔法伤害、治疗、吸血)
	float		mValue;				//伤害值
	bool		mIsDodge;			//闪避
	bool		mIsCrit;			//暴击
	bool		mIsPhyDmgImmunity;	//物理免疫
	bool		mIsMagDmgImmunity;	//魔法免疫
};

UCLASS()
class UPkProcess : public UObject, public IObjInterface
{
	GENERATED_BODY()
public:
	UPkProcess();
	virtual ~UPkProcess();
	virtual void BeginDestroy() override;
	virtual void Reset() override;
	virtual void Recycle() override;

public:
	void SetMsg(UPkMsg* _pkMsg);
	void Run();
	FPkOverDlg&	GetPkOverDlg() { return mCallBack; }
	void SetPkOverDlg(const FPkOverDlg& _dlg) { mCallBack = _dlg; }

private:
	bool CheckCanPk();//判断能否pk
	void Filter();//选取攻击对象逻辑
	void RunEndEvns(); 

	void PkLogicEvns();// pk逻辑运算，之前的方法已把对象消耗的值算好，这里不用再计算，直接进行逻辑运算即可
	void RunEndPk();//
	void PkPrice();//奖历分配，组织协议，是否战斗已结束
	void PkDamage(TArray<UDamageInfo*> _dmgVec);

private:
	UPkMsg* mPkMsg;
	FPkOverDlg mCallBack; //结算完的回调
	RunSkillBeforeCallBack m_runSkillBeforeCallBack;
};
