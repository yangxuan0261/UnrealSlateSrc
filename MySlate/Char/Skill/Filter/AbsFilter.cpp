// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AbsFilter.h"

#include "Char/BpFuncLib/GolbalFunc.h"
#include "Char/MyChar.h"
#include "Char/CharMgr.h"
#include "../Pk/PkMsg.h"

UAbsFilter::UAbsFilter()
{
	mKey = "";
	mSelectType = ESelectType::Enemy; //默认敌方
	mCount = -1; //不限人数
}

UAbsFilter::~UAbsFilter()
{

}

void UAbsFilter::BeginDestroy()
{

	Super::BeginDestroy();
}

void UAbsFilter::Filter(UPkMsg* _msg, EFilterType _filterType /* = EFilterType::Locked */, float _radius /* = 0.f */, const FVector& _boxSize /* = FVector::ZeroVector */)
{
	mDestChars.Empty();
	if (_filterType == EFilterType::Locked)
	{
		return;
	}

	int32 targetId = _msg->GetTargetId();
	AMyChar* target = targetId > 0 ? UCharMgr::GetInstance()->GetChar(targetId) : nullptr;
	FVector targetLoc = FVector::ZeroVector;
	if (target != nullptr) //锁定目标，有可能飞行中目标死亡，所以去Char管理器中拿比较靠谱
	{
		targetLoc = target->GetActorLocation();
	}
	else //锁定地点,或者 "死亡目标"的地点
	{
		targetLoc = _msg->GetTargetLoc();
	}

	if (targetLoc.SizeSquared() > 0.f)
	{
		TArray<AMyChar*> ignoreChars; //如果有目标的话忽略目标，因为锁定目标会自己结算一次
		if (target != nullptr)
		{
			ignoreChars.Add(target);
		}

		ETeam ignoreTeam = UCharMgr::GetInstance()->GetIgnoreTeam(_msg->GetAttackerTeam(), mSelectType);
		UCharMgr::GetInstance()->GetIgnoreCharsByTeam(ignoreTeam, ignoreChars);

		TArray<AActor*> ignoreActors;
		UCharMgr::GetInstance()->ConvertCharsToActors(ignoreChars, ignoreActors);

		//ignoreChars.Add(_actor);
		TArray<TEnumAsByte<EObjectTypeQuery>>  destObjectTypes; //目的类型集合
		destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_Pawn); //这里强转一下，一一对应的

		TArray<AActor*> destActors;
		if (_filterType == EFilterType::Circle)
		{
			UKismetSystemLibrary::SphereOverlapActors_NEW(GWorld, targetLoc, _radius, destObjectTypes, AMyChar::StaticClass(), ignoreActors, destActors);
		}
		else if (_filterType == EFilterType::Rect)
		{
			UKismetSystemLibrary::BoxOverlapActors_NEW(GWorld, targetLoc, _boxSize, destObjectTypes, AMyChar::StaticClass(), ignoreActors, destActors);
		}

		//为减少多次遍历，直接在cast后加入pkMsg目标集合中
		AMyChar* tmpTarget = nullptr;
		int32 tmpTargetId = 0;
		int32 counter = mCount;
		//把选中的人丢进pkMsg目标集合中
		for (AActor* destTarget : destActors)
		{
			if (mCount > 0)//有人数限制
			{
				if (counter == 0)
				{
					break; //选定人数已经达到
				}
			}

			tmpTarget = Cast<AMyChar>(destTarget);
			tmpTargetId = tmpTarget != nullptr ? tmpTarget->GetUuid() : 0;
			tmpTarget = tmpTargetId > 0 ? UCharMgr::GetInstance()->GetChar(tmpTargetId) : nullptr; //防止死亡的char被选中
			if (tmpTarget)
			{
				_msg->AddTarget(tmpTarget);
				mDestChars.Add(tmpTarget);
				--counter;
			}
		}
	

		//DEBUG: 绘制一下选中的目标集合线段
		for (AMyChar* tmpChar : mDestChars)
		{
			UGolbalFunc::DrawSegment(targetLoc, tmpChar->GetActorLocation());
		}
	}
	else
	{
		UE_LOG(FilterLogger, Error, TEXT("--- URectFilter::Filter, targetLoc.SizeSquared() == 0.f"));
	}
}

void UAbsFilter::DebugDraw(const FVector& _start, const TArray<AMyChar*>& _targets)
{
	for (AMyChar* tmp : _targets)
	{
		UGolbalFunc::DrawSegment(_start, tmp->GetActorLocation());
	}
}
