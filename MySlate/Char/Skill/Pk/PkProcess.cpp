
#include "MySlate.h"
#include "PkProcess.h"

#include "./PkMsg.h"
#include "../../MyChar.h"
#include "../Filter/AbsFilter.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Template/SkillTemplate.h"
#include "../Buff/BuffMgr.h"
#include "./FightData.h"

UPkProcess::UPkProcess() : Super()
{

}

UPkProcess::~UPkProcess()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkProcess::~UPkProcess"));
}

void UPkProcess::BeginDestroy()
{


	UE_LOG(PkLogger, Warning, TEXT("--- UPkProcess::BeginDestroy"));
	Super::BeginDestroy();
}

void UPkProcess::SetMsg(UPkMsg* _pkMsg)
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
	}
	mPkMsg = _pkMsg;
	mPkMsg->AddToRoot();
}

void UPkProcess::Run()
{
	UParam* currtarge = nullptr;
	
	Filter();
	const TArray<UParam*>& targets = mPkMsg->GetTargets();
	for (int32 i = 0; i < targets.Num(); ++i)
	{
		currtarge = targets[i];
		mPkMsg->SetCurrTarget(currtarge);

		PkLogic();//pk逻辑运算，之前的方法已把对象消耗的值算好,还有是否闪避和暴击等，这里不用再计算，直接进行逻辑运算即可
		RunEndEvns(); //每个受击者加buff
	}

	RunEndPk(); //给攻击者加buff
	PkPrice();
}

bool UPkProcess::CheckCanPk()
{
	return false;
}

void UPkProcess::Filter()
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

void UPkProcess::RunEndEvns()
{
	const TArray<UAbsPkEvent*>& functions2 = mPkMsg->GetSkillTemp()->GetEndEvns();
	for (UAbsPkEvent* func : functions2)
	{

		//step4 - 运行对目标集中的每个个体的func
		func->RunEndEvns(mPkMsg);
	}
}

void UPkProcess::PkLogic()
{
	//战斗伤害值
	float dmg = mPkMsg->GetAttackerData()->GetAttackPhy();
	mPkMsg->SetAttackDmgValue(dmg, -1, false);
}

void UPkProcess::RunEndPk()
{
	//step5 - 运行释放者pk后置事件
	USkillTemplate* skillTemp = mPkMsg->GetSkillTemp();
	const TArray<UAbsPkEvent*> functions = skillTemp->GetEndPk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunEndPk(mPkMsg);
	}

	//UBuffMgr::GetInstance()->RunEndPkBuffs(mPkMsg->GetAttackerId(), mPkMsg);
}

void UPkProcess::PkPrice()
{
	TArray<FDamageInfo> dmgArr;

	mCallBack.ExecuteIfBound(dmgArr);
}
