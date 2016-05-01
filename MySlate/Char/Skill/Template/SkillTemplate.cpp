
#include "MySlate.h"
#include "SkillTemplate.h"

#include "../Function/FuncFactory.h"
#include "../Filter/AbsFilter.h"
#include "../Utils/CommonDef.h"
#include "../Function/Funcs/AbsPkEvent.h"

USkillTemplate::USkillTemplate() : Super()
{
	mId = -1;
	mName = TEXT("Default SkillName");
	mDescr = TEXT("Default SkillDescr");
	mCoolDown = 5;
	mLockedType = ELockedType::Loc;
	mAttackDist = 10;
	mTolerance = 0;
	mBulletSpeed = 0;
	mFlyDist = 0;
	mSkillType = ESkillType::Normal;
	mFilterStr = "";
	mFilter = nullptr;

	mBeforeSkillStr = "";
	mBeforePkStr = "";
	mBeforeEvnsStr = "";
	mEndEvnsStr = "";
	mEndPkStr= "";
	mEndSkillStr = "";
	mAnimType = EAnimType::None;
}

USkillTemplate::~USkillTemplate()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UBufflTemplate::~UBufflTemplate"));
}

void USkillTemplate::BeginDestroy()
{
	if (mFilter != nullptr)
	{
		mFilter->RemoveFromRoot();
		mFilter->ConditionalBeginDestroy();
		mFilter = nullptr;
	}

	ReleaseArray(mBeforeSkill);
	ReleaseArray(mBeforePk);
	ReleaseArray(mBeforeEvns);
	ReleaseArray(mEndEvns);
	ReleaseArray(mEndPk);
	ReleaseArray(mEndSkill);

	UE_LOG(SkillLogger, Warning, TEXT("--- USkillTemplate::BeginDestroy"));
	Super::BeginDestroy();
}

void USkillTemplate::ReleaseArray(TArray<UAbsPkEvent*>& _arr)
{
	for (UAbsPkEvent* func : _arr)
	{
		func->RemoveFromRoot();
		func->ConditionalBeginDestroy();
	}
	_arr.Empty();
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforeSkill()
{
	if (mBeforeSkill.Num() ==0 && mBeforeSkillStr.Len() > 0)
	{
		ParseFuncStr(mBeforeSkillStr, mBeforeSkill);
	}
	return mBeforeSkill;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforePk()
{
	if (mBeforePk.Num() == 0 && mBeforePkStr.Len() > 0)
	{
		ParseFuncStr(mBeforePkStr, mBeforePk);
	}
	return mBeforePk;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetBeforeEvns()
{
	if (mBeforeEvns.Num() == 0 && mBeforeEvnsStr.Len() > 0)
	{
		ParseFuncStr(mBeforeEvnsStr, mBeforeEvns);
	}
	return mBeforeEvns;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndEvns()
{
	if (mEndEvns.Num() == 0 && mEndEvnsStr.Len() > 0)
	{
		ParseFuncStr(mEndEvnsStr, mEndEvns);
	}
	return mEndEvns;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndPk()
{
	if (mEndPk.Num() == 0 && mEndPkStr.Len() > 0)
	{
		ParseFuncStr(mEndPkStr, mEndPk);
	}
	return mEndPk;
}

const TArray<UAbsPkEvent*>& USkillTemplate::GetEndSkill()
{
	if (mEndSkill.Num() == 0 && mEndSkillStr.Len() > 0)
	{
		ParseFuncStr(mEndSkillStr, mEndSkill);
	}
	return mEndSkill;
}

UAbsFilter* USkillTemplate::GetFilter()
{
	if (mFilter == nullptr && mFilterStr.Len() > 0)
	{
		ParseFilterStr(mFilterStr);
	}
	return mFilter;
}

void USkillTemplate::ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr)
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

void USkillTemplate::ParseFilterStr(const FString& _filterStr)
{
	mFilter = UFuncFactory::GetInstance()->createFilter(_filterStr);
	if (mFilter != nullptr)
	{
		mFilter->AddToRoot();
	}
}
