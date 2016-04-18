// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkPorcess.h"

#include "PkMsg.h"
#include "char/MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Template/SkillTemplate.h"
#include "../Buff/BuffMgr.h"

UPkPorcess::UPkPorcess() : Super()
{

}

UPkPorcess::~UPkPorcess()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkPorcess::~UPkPorcess"));
	if (mPkMsg != nullptr)
	{
		mPkMsg->ExeNullDlg(); // 攻击者不死，这里释放，USkillFunction中就不释放了，重置指针为null 
		mPkMsg->RemoveFromRoot();
	}
}

void UPkPorcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
	}
	mPkMsg = _pkMsg;
	mPkMsg->AddToRoot();
}

void UPkPorcess::Run()
{
	AMyChar* targetActor = nullptr;
	
	Filter();
	const TArray<UParam*>& targets = mPkMsg->GetTargets();
	for (int32 i = 0; i < targets.Num(); ++i)
	{
		targetActor = targets[i]->mTarget;
	}

	RunEndPk(); //给攻击者加buff
	PkPrice();
}

bool UPkPorcess::CheckCanPk()
{
	return false;
}

void UPkPorcess::Filter()
{
	UAbsFilter* filter = nullptr;
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	if (skillTemp)
	{
		filter = skillTemp->GetFilter();
	}

	if ( filter != nullptr)
	{
		filter->Filter(mPkMsg);
	}
}

void UPkPorcess::RunBeforePk()
{
}

void UPkPorcess::RunBeforeSkill()
{
}

void UPkPorcess::PkLogic()
{
	//战斗伤害值
	float dmg = mPkMsg->GetAttackerData()->GetAttackPhy();
	mPkMsg->SetAttackDmgValue(dmg, -1, false);
}

void UPkPorcess::RunEndSkill()
{

}

void UPkPorcess::RunEndPk()
{
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	const TArray<UAbsPkEvent*> functions = skillTemp->GetEndPk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunEndPk(mPkMsg);
	}

	UBuffMgr::GetInstance()->RunEndPkBuffs(mPkMsg->GetAttackerId(), mPkMsg);
}

void UPkPorcess::PkPrice()
{

}
