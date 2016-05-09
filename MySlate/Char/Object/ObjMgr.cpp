
#include "MySlate.h"
#include "ObjMgr.h"

#include "../Skill/Pk/FightData.h"

UObjMgr::UObjMgr() : Super()
{

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

	return NewObject<TRetType>(TRetType::StaticClass());
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

UFightData* UObjMgr::GetFightData()
{
	UFightData* ret = mFightDataCls != nullptr ? GetObj<UFightData>(mFightDataCls) : nullptr;
	ret->AddToRoot();
	return ret;
}
