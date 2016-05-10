
#include "MySlate.h"
#include "Attack.h"

#include "../../../Object/ObjMgr.h"

UAttack::UAttack() : Super()
{

}

UAttack::~UAttack()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttack::~UAttack"));
}

void UAttack::BeginDestroy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAttack::BeginDestroy"));
	Super::BeginDestroy();
}

void UAttack::Reset()
{
	mValue = 0.f;
	mOwner = 1; //攻击者
	mLimitId = -1; //不限制技能
}

UAttack* UAttack::CreateFunction(const FString& _key)
{
	UAttack* func = GetObjMgr()->GetObj<UAttack>(GetObjMgr()->mAttackCls);
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UAttack::Clone()
{
	return CreateFunction(mKey);
}

void UAttack::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 3)
	{
		CheckPercent(_params[0]);
		mOwner = FCString::Atoi(*_params[1]);
		mLimitId = FCString::Atoi(*_params[2]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- UAttack::Parser, params num < 2"));
	}
}

void UAttack::RunBeforePk(UPkMsg* msg)
{

}
