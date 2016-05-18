
#include "MySlate.h"
#include "CharMgr.h"

#include "./MyChar.h"
#include "./Comp/MyCharDataComp.h"
#include "./Skill/Template/SkillTemplate.h"
#include "./Res/Infos/CharInfo.h"
#include "./Res/ResMgr.h"
#include "./CharData.h"
#include "./Skill/Pk/FightData.h"

static int32 uuid = 1;
static int32 IdGenerator()
{
	return uuid++;
}

UCharMgr::UCharMgr() : Super()
{

}

UCharMgr::~UCharMgr()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UCharMgr::~UCharMgr"));
}

void UCharMgr::BeginDestroy()
{
	for (auto Iter = mGroupCharMap.CreateConstIterator(); Iter; ++Iter)
	{
		for (TMap<int32, AMyChar*>::TConstIterator Iter2 = Iter->Value.CreateConstIterator(); Iter2; ++Iter2)
			Iter2->Value->Destroy();
	}
	mGroupCharMap.Empty();

	for (TMap<int32, UCharData*>::TConstIterator Iter = mCharDataMap.CreateConstIterator(); Iter; ++Iter)
	{
		Iter->Value->RemoveFromRoot();
		Iter->Value->ConditionalBeginDestroy();
	}
	mCharDataMap.Empty();

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UCharMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UCharMgr::AddChar(AMyChar* _char)
{
	if (_char != nullptr)
	{
		int32 uuid = ::IdGenerator();
		_char->SetUuid(uuid);

		TMap<int32, AMyChar*>& dstGroup = mGroupCharMap.FindOrAdd(_char->GetTeamType());
		dstGroup.Add(uuid, _char);
	}
}

AMyChar* UCharMgr::GetChar(int32 _id)
{
	AMyChar** mychar = nullptr;
	for (auto Iter = mGroupCharMap.CreateIterator(); Iter; ++Iter)
	{
		mychar = Iter->Value.Find(_id);
		if (mychar != nullptr)
		{
			return *mychar;
		}
	}
	return nullptr;
}

void UCharMgr::RemoveChar(AMyChar* _target)
{
	if (_target != nullptr)
	{
		TMap<int32, AMyChar*>* dstGroup = mGroupCharMap.Find(_target->GetTeamType());
		if (dstGroup != nullptr)
		{
			dstGroup->Remove(_target->GetUuid());
		}
	}
}

ETeam UCharMgr::GetDestTeam(ETeam _atkTeam, ESelectType _flag)
{
	//_flag: 1:攻击方，0:受击方
	if (_flag == ESelectType::Self)
	{
		return _atkTeam;
	}
	else
	{
		if (_atkTeam == ETeam::Teammate)
		{
			return ETeam::Enemy;
		}
		else
		{
			return ETeam::Teammate;
		}
	}
}

ETeam UCharMgr::GetIgnoreTeam(ETeam _atkTeam, ESelectType _flag)
{
	//_flag: 1:攻击方，0:受击方
	if (_flag == ESelectType::Enemy)
	{
		return _atkTeam;
	}
	else
	{
		if (_atkTeam == ETeam::Teammate)
		{
			return ETeam::Enemy;
		}
		else
		{
			return ETeam::Teammate;
		}
	}
}

void UCharMgr::GetDstCharVec(ETeam _dstType, float _radius, const FVector& _loc, TArray<AMyChar*>& _outCharVec)
{
	AMyChar* dstChar = nullptr;
	TMap<int32, AMyChar*>* charMap = mGroupCharMap.Find(_dstType);
	if (charMap != nullptr)
	{
		for (auto Iter = charMap->CreateConstIterator(); Iter; ++Iter)
		{
			dstChar = Iter->Value;
			float dst = FVector::DistSquared(_loc, dstChar->GetActorLocation());
			if (dst > FMath::Pow(_radius, 2))
			{
				_outCharVec.Add(dstChar);
			}
		}
	}
}

AMyChar* UCharMgr::GetCloseChar(const TArray<AMyChar*>& _inVec, const FVector& _loc)
{
	float smaller = MAX_FLT;
	AMyChar* dstChar = nullptr;
	for (AMyChar* target : _inVec)
	{
		float val = FVector::Dist(_loc, target->GetActorLocation());
		if (val < smaller)
		{
			smaller = val;
			dstChar = target;
		}
	}
	return dstChar;
}

//void UCharMgr::GetIgnoreCharsByTeam(ETeam _type, UPARAM(ref) TArray<AMyChar*>& _outChars) const
//{
//	AMyChar* target = nullptr;
//	for (TMap<int32, AMyChar*>::TConstIterator Iter = mAllCharMap.CreateConstIterator(); Iter; ++Iter)
//	{
//		target = Iter->Value;
//		if (target->GetTeamType() == _type)
//		{
//			_outChars.Add(target);
//		}
//	}
//}
//
//void UCharMgr::ConvertCharsToActors(UPARAM(ref) const TArray<AMyChar*>& _srcChars, TArray<AActor*>& _outActors)
//{
//	for (AMyChar* tmpChar : _srcChars)
//	{
//		_outActors.Add(tmpChar);
//	}
//}
//
//void UCharMgr::ConvertActorsToChars(UPARAM(ref) const TArray<AActor*>& _srcActors, TArray<AMyChar*>& _outChars)
//{
//	AMyChar* target = nullptr;
//	for (AActor* tmpActor : _srcActors)
//	{
//		target = Cast<AMyChar>(tmpActor);
//		if (target != nullptr)
//		{
//			_outChars.Add(target);
//		}
//	}
//}

UCharData* UCharMgr::GetCharData(int32 _id)
{
	UCharData** data = mCharDataMap.Find(_id);
	return data != nullptr ? *data : nullptr;
}

void UCharMgr::LoadCharData()
{
	UDataTable* dataTab = UResMgr::GetInstance()->GetInfoTable(EInfoType::Char);
	if (dataTab != nullptr)
	{
		FCharInfo* tmpPtr = nullptr;
		for (auto Iter : dataTab->RowMap)
		{
			tmpPtr = (FCharInfo*)(Iter.Value);
			tmpPtr->mId = FCString::Atoi(*Iter.Key.ToString());
			UCharData* char1 = NewObject<UCharData>(UCharData::StaticClass());
			char1->Init();
			char1->mId = tmpPtr->mId;
			char1->mName = tmpPtr->mName;
			char1->mDescr = tmpPtr->mDescr;
			char1->mHeath = tmpPtr->mHeath;
			char1->mHeathMax = tmpPtr->mHeathMax;
			char1->mWarnRange = tmpPtr->mWarnRange;

			//战斗基础属性
			char1->mFightData->mLv = tmpPtr->mFightInfo.mLv;
			char1->mFightData->mAttackPhy = tmpPtr->mFightInfo.mAttackPhy;

			char1->AddToRoot();
			mCharDataMap.Add(char1->mId, char1);
			UE_LOG(GolbalFuncLogger, Warning, TEXT("--- key:%d, name:%s"), tmpPtr->mId, *tmpPtr->mName);
		}
	}
	else
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::LoadSkillData, dataTab is nullptr"));
	}
}
