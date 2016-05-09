
#include "MySlate.h"
#include "FightData.h"

#include "../../Object/ObjMgr.h"

UFightData::UFightData() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);

	Reset();
}

UFightData::~UFightData()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::~UFightData"));
}

void UFightData::BeginDestroy()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UFightData::BeginDestroy"));
	Super::BeginDestroy();
}

void UFightData::Reset()
{
	mAttackPhy = 0.f;
	mLv = 1;
}

UFightData* UFightData::Clone()
{
	UFightData* data = NewObject<UFightData>(UFightData::StaticClass());
	data->Copy(this);
	return data;
}

void UFightData::Copy(UFightData* _fightData)
{
	this->mAttackPhy = _fightData->mAttackPhy;
	this->mLv = _fightData->mLv;
}