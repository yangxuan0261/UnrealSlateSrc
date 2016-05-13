
#include "MySlate.h"
#include "MyCharDataComp.h"

#include "../Skill/Pk/FightData.h"
#include "../CharData.h"
#include "../CharMgr.h"
#include "../Object/ObjMgr.h"

UMyCharDataComp::UMyCharDataComp()
	: Super()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	bAllowAnyoneToDestroyMe = true;

	mGroup = EGroup::None;
	mTeam = ETeam::None;
	mHealth = 0.f;
	mHealthMax = 0.f;
	mFightData = nullptr;
	mCharData = nullptr;
}

UMyCharDataComp::~UMyCharDataComp()
{
	UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::~UMyCharDataComp"));
}

void UMyCharDataComp::BeginPlay()
{
	Super::BeginPlay();
	mFightData = gGetObj()->GetObj<UFightData>(gGetObj()->mFightDataCls);//战斗时数据对象
}

void UMyCharDataComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::TickComponent"));
}

void UMyCharDataComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{
	if (mFightData != nullptr)
	{
		mFightData->Recycle();
		mFightData = nullptr;
	}

	UE_LOG(CompLogger, Warning, TEXT("--- UMyCharDataComp::DestroyComponent"));
	Super::DestroyComponent(bPromoteChildren);
}

void UMyCharDataComp::SetCharData(int32 _id)
{
	UCharData* data = gGetChar()->GetCharData(_id);

	if (data != nullptr)
	{
		mCharData = data;
		mHealth = data->mHeath;
		mHealthMax = data->mHeathMax;
		mFightData->Copy(data->GetFightData());//角色模板中的基础数据拷到 战斗数据对象中
	}
	else
	{
		UE_LOG(CompLogger, Error, TEXT("--- UMyCharDataComp::SetCharData, data == nullptr, id:%d"), _id);
	}
}
