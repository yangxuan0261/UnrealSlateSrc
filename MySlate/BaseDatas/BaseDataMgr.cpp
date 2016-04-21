// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BaseDataMgr.h"

#include "Datas/CharData.h"
#include "Char/Skill/Pk/FightData.h"

UBaseDataMgr::UBaseDataMgr() : Super()
{

}

UBaseDataMgr::~UBaseDataMgr()
{
	for (TMap<int32, UCharData*>::TConstIterator iter = mCharDataMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mCharDataMap.Empty();
}

void UBaseDataMgr::InitFakeData()
{
	UCharData* charData = NewObject<UCharData>(UCharData::StaticClass());
	charData->AddToRoot();
	charData->mId = 90001;
	charData->mName = TEXT("CharA");
	charData->mDescr = TEXT("Descr of CharA");
	charData->mHeath = 100.f;
	charData->mFightData->mLv = 2;
	charData->mFightData->mAttackPhy = 10.f;
	mCharDataMap.Add(charData->mId, charData);

	UCharData* charData2 = NewObject<UCharData>(UCharData::StaticClass());
	charData2->AddToRoot();
	charData2->mId = 90002;
	charData2->mName = TEXT("CharB");
	charData2->mDescr = TEXT("Descr of CharB");
	charData2->mHeath = 100.f;
	charData2->mFightData->mLv = 1;
	charData2->mFightData->mAttackPhy = 15.f;
	mCharDataMap.Add(charData2->mId, charData2);
}

void UBaseDataMgr::LoadCharData()
{

}

UCharData* UBaseDataMgr::GetCharData(int32 _id)
{
	UCharData** data = mCharDataMap.Find(_id);
	return data != nullptr ? *data : nullptr;
}
