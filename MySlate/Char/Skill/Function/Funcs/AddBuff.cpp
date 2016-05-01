
#include "MySlate.h"
#include "AddBuff.h"

#include "../../Buff/Buffs/AbsBuff.h"
#include "../../../MyChar.h"
#include "../../Pk/PkMsg.h"
#include "../../Buff/BuffMgr.h"
#include "../../Template/SkillTemplate.h"

UAddBuff::UAddBuff() : Super()
{
	//skill
	mBuffId = 0;
}

UAddBuff::~UAddBuff()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAddBuff::~UAddBuff"));
}

void UAddBuff::BeginDestroy()
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAddBuff::BeginDestroy"));
	Super::BeginDestroy();
}

UAddBuff* UAddBuff::CreateFunction(const FString& _key)
{
	UAddBuff* func = NewObject<UAddBuff>(UAddBuff::StaticClass());
	func->SetKey(_key);
	return func;
}

UAbsPkEvent* UAddBuff::Clone()
{
	return CreateFunction(mKey);
}

void UAddBuff::Parser(const TArray<FString>& _params)
{
	if (_params.Num() == 1)
	{
		mBuffId = FCString::Atoi(*_params[0]);
	}
	else
	{
		UE_LOG(FuncLogger, Error, TEXT("--- UAddBuff::Parser, params num < 1"));
	}
}

void UAddBuff::RunEndEvns(UPkMsg* msg)
{
	UE_LOG(FuncLogger, Warning, TEXT("--- UAddBuff::RunEndEvns, targetId:%d, buffId:%d"), msg->GetCurrTarget()->mTarget->mUuid, mBuffId);

	UBuffMgr::GetInstance()->AddBuff(msg->GetAttacker(), msg->GetCurrTarget()->mTarget, msg->GetSkillTemp()->mId, mBuffId);
}
