
#include "MySlate.h"
#include "AttackPhy.h"

#include "../../Buff/Buffs/AbsBuff.h"
#include "../../../Comp/MyCharDataComp.h"
#include "../../../MyChar.h"
#include "../../../Object/ObjMgr.h"

UAttackPhy::UAttackPhy() : Super()
{

}

UAttackPhy::~UAttackPhy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::~UAttackPhy"));
}

void UAttackPhy::BeginDestroy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::BeginDestroy"));
	Super::BeginDestroy();
}

void UAttackPhy::Reset()
{
	//buff
	mDtVal = 0.f;
	mDurable = true;

	//skill
	mValue = 0.f;
	mOwner = 1; //攻击者
	mLimitId = -1; //不限制技能
}

UAttackPhy* UAttackPhy::CreateFunction(const FString& _key)
{
	UAttackPhy* func = gGetObjMgr()->GetObj<UAttackPhy>(gGetObjMgr()->mAttackPhyCls);
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UAttackPhy::Clone()
{
	return CreateFunction(mKey);
}

void UAttackPhy::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 3)
	{
		CheckPercent(_params[0]);
		mOwner = FCString::Atoi(*_params[1]);
		mLimitId = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- UAttackPhy::Parser, params num < 2"));
	}
}

void UAttackPhy::RunTick(float DeltaSeconds)
{
	if (mDurable)
	{
		if (mOwnerChar != nullptr) //buff使用mOwnerChar
		{
			mOwnerChar->GetDataComp()->Hurt(mDtVal);
		}
	}
}

void UAttackPhy::RunStart()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::RunStart"));
	if (mBuff == nullptr)
	{
		UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::RunStart, mBuff == nullptr"));
	}

	//mDurable = mBuff->IsDurable();
	//if (mDurable)
	//{
	//	mDtVal = mBuff->GetDtVal(mValue);
	//}
}

void UAttackPhy::RunOver()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttackPhy::RunOver"));
}
