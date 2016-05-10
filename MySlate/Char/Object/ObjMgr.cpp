
#include "MySlate.h"
#include "ObjMgr.h"

#include "../Skill/Pk/FightData.h"
#include "../Skill/Pk/PkProcess.h"
#include "../Skill/Pk/PkMsg.h"

#include "../Skill/Filter/CircleFilter.h"
#include "../Skill/Filter/LockFilter.h"
#include "../Skill/Filter/RectFilter.h"

#include "../Skill/CoolDown/CoolDown.h"
#include "../Skill/SkillFunction.h"

#include "../Skill/Buff/Buffs/AppendBuff.h"
#include "../Skill/Buff/Buffs/CommonBuff.h"

#include "../Skill/Function/Funcs/AddBuff.h"
#include "../Skill/Function/Funcs/Attack.h"
#include "../Skill/Function/Funcs/AttackPhy.h"
#include "../Skill/Function/Funcs/Suckup.h"


UObjMgr::UObjMgr() : Super()
{
	//default cpp class
	mFightDataCls		= UFightData::StaticClass();
	mPkProcessCls		= UPkProcess::StaticClass();
	mPkMsgCls			= UPkMsg::StaticClass();
	mPkParamCls			= UParam::StaticClass();

	mCircleFltCls		= UCircleFilter::StaticClass();
	mLockFltCls			= ULockFilter::StaticClass();
	mRectFltCls			= URectFilter::StaticClass();

	mCoolDownCls		= UCoolDown::StaticClass();
	mSkillFuncCls		= USkillFunction::StaticClass();

	mAppBuffCls			= UAppendBuff::StaticClass();
	mComBuffCls			= UCommonBuff::StaticClass();

	mAddBuffCls			= UAddBuff::StaticClass();
	mAttackCls			= UAttack::StaticClass();
	mAttackPhyCls		= UAttackPhy::StaticClass();
	mSuckupCls			= USuckup::StaticClass();
}

UObjMgr::~UObjMgr()
{
	UE_LOG(ObjLogger, Warning, TEXT("--- UObjMgr::~UObjMgr"));
}

void UObjMgr::BeginDestroy()
{
	for (auto Iter = mObjMap.CreateConstIterator(); Iter; ++Iter)
	{
		for (UObject* obj : Iter->Value)
		{
			obj->RemoveFromRoot();
			obj->ConditionalBeginDestroy();
		}
	}
	mObjMap.Empty();

	UE_LOG(ObjLogger, Warning, TEXT("--- UObjMgr::BeginDestroy"));
	Super::BeginDestroy();
}

template<typename TRetType>
TRetType* UObjMgr::GetObj(UClass* _cls)
{
	TArray<UObject*>* findObjVec = mObjMap.Find(_cls->GetName());
	if (findObjVec != nullptr)
	{
		if (findObjVec->Num() > 0)
		{
			UObject* obj = findObjVec->Pop();
			return Cast<TRetType>(obj);
		}
	}

	TRetType* ret = NewObject<TRetType>(TRetType::StaticClass());
	UObject* obj = (UObject*)ret;
	obj->AddToRoot();
	return ret;
}

void UObjMgr::Recycle(UObject* _obj)
{
	FString clsName = _obj->GetClass()->GetName();
	TArray<UObject*>* objVec = mObjMap.Find(clsName);
	if (objVec != nullptr)
	{
		objVec->Push(_obj);
	}
	else
	{
		TArray<UObject*> tmp;
		tmp.Add(_obj);
		mObjMap.Add(clsName, tmp);
	}
}
