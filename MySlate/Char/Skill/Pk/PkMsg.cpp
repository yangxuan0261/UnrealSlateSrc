// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "PkMsg.h"

#include "../../CharMgr.h"
#include "../../MyChar.h"
#include "../../Comp/MyCharDataComp.h"
#include "../Template/SkillTemplate.h"
#include "../Utils/SkillDataMgr.h"

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
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mSkillTemp = nullptr;
	mCurrTarget = nullptr;
}

UPkMsg::~UPkMsg()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::~UPkMsg"));
	if (mAttackerData != nullptr)
	{
		mAttackerData->RemoveFromRoot();
		mAttackerData = nullptr;
	}
	if (mAttackerData != nullptr)
	{
		mAttackerDataForCacul->RemoveFromRoot();
		mAttackerDataForCacul = nullptr;
	}
	for (int32 i = 0; i < mTargetArr.Num(); ++i)
	{
		mTargetArr[i]->RemoveFromRoot();
	}
	mTargetArr.Empty();
}

void UPkMsg::SetData(USkillTemplate* _skillTemp, const FVector& _targetLoc, int32 _attackerId, int32 _targetId /* = 0 */)
{
	mSkillTemp = _skillTemp;
	if (mSkillTemp)
	{
		mSkillId = mSkillTemp->mId;
		mTargetLoc = _targetLoc;
		mTarget = UCharMgr::GetInstance()->GetChar(_targetId);
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

//void UPkMsg::ExeNullDlg()
//{
//	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::ExeNullDlg"));
//	mSetNullDlg.ExecuteIfBound();
//}

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

//-------------------------------- UParam Begin

UParam::UParam()
{
	mFightData = nullptr;
	mTarget = nullptr;
}

UParam::~UParam()
{
	if (mFightData)
	{
		mFightData->RemoveFromRoot();
		mFightData = nullptr;
	}
}

void UParam::Init()
{
	mFightData = NewObject<UFightData>(UFightData::StaticClass());
	mFightData->AddToRoot();
}
