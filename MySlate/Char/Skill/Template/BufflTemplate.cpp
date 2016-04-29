
#include "MySlate.h"
#include "BufflTemplate.h"

#include "../Utils/CommonDef.h"
#include "../Function/Funcs/AbsPkEvent.h"
#include "../Function/FuncFactory.h"

UBufflTemplate::UBufflTemplate() : Super()
{
		mId = 0;
		mName = "";
		mDescr = "";
		mBuffTime = 0;
		mCanDisperse = false;
		mCanAdd = false;
		mInterType = EIntervalType::Once;
		mBindPos = "";
		mBehavDataId = 0;

		mAttrsStr = "";
		mBeforePkStr = "";
		mEndPkStr = "";
}

UBufflTemplate::~UBufflTemplate()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::~UBufflTemplate"));
}

void UBufflTemplate::BeginDestroy()
{


	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::BeginDestroy"));
	Super::BeginDestroy();
}

TArray<UAbsPkEvent*>& UBufflTemplate::GetAttrs()
{
	if (mAttrs.Num() == 0 && mAttrsStr.Len() > 0)
	{
		ParseFuncStr(mAttrsStr, mAttrs);
	}
	return mAttrs;
}

TArray<UAbsPkEvent*>& UBufflTemplate::GetBeforePk()
{
	if (mBeforePk.Num() == 0 && mBeforePkStr.Len() > 0)
	{
		ParseFuncStr(mBeforePkStr, mBeforePk);
	}
	return mBeforePk;
}

TArray<UAbsPkEvent*>& UBufflTemplate::GetEndPk()
{
	if (mEndPk.Num() == 0 && mEndPkStr.Len() > 0)
	{
		ParseFuncStr(mEndPkStr, mEndPk);
	}
	return mEndPk;
}

void UBufflTemplate::ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr)
{
	FString paramStr = _funcStr.ToLower();
	TArray<FString> params;
	paramStr.ParseIntoArray(params, Split_Sem, true);
	for (TArray<FString>::TConstIterator iter = params.CreateConstIterator(); iter; ++iter)
	{
		UAbsPkEvent* func = UFuncFactory::GetInstance()->createFunction(*iter);
		if (func != nullptr)
		{
			func->AddToRoot();
			_funcArr.Add(func);
		}
	}
}

