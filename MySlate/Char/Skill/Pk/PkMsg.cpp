// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkMsg.h"

#include "../../CharMgr.h"
#include "../../MyChar.h"
#include "../../Comp/MyCharDataComp.h"
#include "../Template/SkillTemplate.h"
#include "../Utils/SkillDataMgr.h"


UParam::UParam()
{
	mFightData = nullptr;
	mTarget = nullptr;
}

UParam::~UParam()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UParam::~UParam"));
}

void UParam::BeginDestroy()
{
	if (mFightData != nullptr)
	{
		mFightData->RemoveFromRoot();
		mFightData->ConditionalBeginDestroy();
		mFightData = nullptr;
	}

	UE_LOG(PkLogger, Warning, TEXT("--- UParam::BeginDestroy"));
	Super::BeginDestroy();
}

void UParam::Init()
{
	mFightData = NewObject<UFightData>(UFightData::StaticClass());
	mFightData->AddToRoot();
}


//-------------------------------- UPkMsg Begin
UPkMsg::UPkMsg()
	: Super()
{
	mCanLog = false;
	mSkillId = 0;					
	mSkillLogicType = ESkillAttackType::ATTACK_PHY;
	mTeamType = ETeam::None;
	mAttackerId = 0;				
	mTargetId = 0;
	mAttackerData = nullptr;
	mAttackerDataForCacul = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mSkillTemp = nullptr;
	mCurrTarget = nullptr;
	mTargetLocked = nullptr;
}

UPkMsg::~UPkMsg()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::~UPkMsg"));
}

void UPkMsg::BeginDestroy()
{
	if (mAttackerData != nullptr)
	{
		mAttackerData->RemoveFromRoot();
		mAttackerData->ConditionalBeginDestroy();
		mAttackerData = nullptr;
	}
	if (mAttackerDataForCacul != nullptr)
	{
		mAttackerDataForCacul->RemoveFromRoot();
		mAttackerDataForCacul->ConditionalBeginDestroy();
		mAttackerDataForCacul = nullptr;
	}
	for (int32 i = 0; i < mTargetArr.Num(); ++i)
	{
		mTargetArr[i]->RemoveFromRoot();
		mTargetArr[i]->ConditionalBeginDestroy();
	}
	mTargetArr.Empty();

	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::BeginDestroy"));
	Super::BeginDestroy();
}

void UPkMsg::SetData(USkillTemplate* _skillTemp, AMyChar* _attacker, AMyChar* _target, const FVector& _targetLoc)
{
	mSkillTemp = _skillTemp;
	if (mSkillTemp)
	{
		mSkillId = _skillTemp->mId;

		//target 
		if (_target != nullptr)
		{
			mTargetLocked = _target; //防止，发动技能过程中，目标死亡的情况
			mTargetId = _target->GetUuid();
			mTargetLoc = mTargetLocked->GetActorLocation();

			//死亡回调
			auto charDeathCallback = [&](AMyChar* _deathChar)->void {
				mTargetLocked = nullptr;
				UE_LOG(BuffLogger, Warning, TEXT("--- UPkMsg::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
			};

			mTargetLocked->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
		}
		else
		{
			mTargetLoc = _targetLoc;
		}

		//attack //TODO:不是必要，可以技能过程中攻击者死亡，后在拷贝战斗数据，一般情况下只需用指针获取攻击者战斗数据
		if (_attacker != nullptr)
		{
			mAttackerId = _attacker->GetUuid();
		}
		else
		{
			UE_LOG(BuffLogger, Error, TEXT("--- UPkMsg::SetData, _attacker == nullptr"));
		}
	}
}

void UPkMsg::AddTarget(AMyChar* _char)
{
	UParam* param = NewObject<UParam>(UParam::StaticClass());
	param->AddToRoot();
	param->Init(); 
	param->mTarget = _char;
	param->mFightData->Copy(_char->GetDataComp()->GetFigthData());//复制目标的战斗数据
	mTargetArr.Add(param);
}

void UPkMsg::SetAttackerData(UFightData* _data)
{
	mAttackerData = _data; //备份数据

	mAttackerDataForCacul = NewObject<UFightData>(UFightData::StaticClass());
	mAttackerDataForCacul->AddToRoot();
	mAttackerDataForCacul->Copy(mAttackerData);
}

void UPkMsg::SetCurrTarget(UParam* _target)
{
	mCurrTarget = _target;

	//重置攻击者数据为备份数据，因为对每个对象的伤害计算都需要修改 攻击者计算数据
	mAttackerDataForCacul->Copy(mAttackerData);
}

void UPkMsg::SetAttackDmgValue(float _value, int _limitId /* = -1 */, bool _isAdd /* = true */)
{
	if (mCurrTarget && (_limitId == -1 || mSkillId == _limitId))
	{
		switch (mSkillLogicType)
		{
		case ESkillAttackType::ATTACK_PHY: // 物理伤害
		{
			if (_isAdd)
				mCurrTarget->mDmgPhyValue += _value;
			else
				mCurrTarget->mDmgPhyValue -= _value;

			UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::SetAttackDmgValue, ATTACK_PHY:%f"), _value);
			break;
		}
		case ESkillAttackType::ATTACK_MAG: // 法术伤害
		{
			if (_isAdd)
				mCurrTarget->mDmgMagValue += _value;
			else
				mCurrTarget->mDmgMagValue -= _value;

			UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::SetAttackDmgValue, ATTACK_MAG:%f"), _value);
			break;
		}
		default:
			break;
		}
	}
}