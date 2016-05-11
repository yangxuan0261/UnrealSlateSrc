
#include "MySlate.h"
#include "PkMsg.h"

#include "../../CharMgr.h"
#include "../../MyChar.h"
#include "../../Comp/MyCharDataComp.h"
#include "../Template/SkillTemplate.h"
#include "./FightData.h"

#include "../../Object/ObjMgr.h"

UParam::UParam() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UParam::~UParam()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UParam::~UParam"));
}

void UParam::BeginDestroy()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UParam::BeginDestroy"));
	Super::BeginDestroy();
}

void UParam::Reset()
{
	mFightData = nullptr;
	mTarget = nullptr;
	mIsLocked = false;

	mDmgPhyValue = 0.0f;
	mDmgMagValue = 0.0f;
	mSuckUp = 0.0f;
	mCureRank = 0.0f;
	mRebound = 0.0f;
	mReboundPer = 1.0f;
	mDeath = false;
	mCrit = false;
	mDodge = false;
	mRebond = false;
}

void UParam::Recycle()
{
	if (mFightData != nullptr)
	{
		mFightData->Recycle();
		mFightData = nullptr;
	}

	IObjInterface::Recycle();
}

void UParam::Init()
{
	mFightData = GetObjMgr()->GetObj<UFightData>(GetObjMgr()->mFightDataCls);
}


//-------------------------------- UPkMsg Begin
UPkMsg::UPkMsg() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UPkMsg::~UPkMsg()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::~UPkMsg"));
}

void UPkMsg::BeginDestroy()
{
	UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::BeginDestroy"));
	Super::BeginDestroy();
}

void UPkMsg::Reset()
{
	mCanLog = false;
	mSkillId = 0;
	mSkillLogicType = ESkillAttackType::Physics;
	mTeamType = ETeam::None;
	mAttackerId = 0;
	mTargetId = 0;
	mAttackerData = nullptr;
	mAttackerDataForCacul = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mSkillTemp = nullptr;
	mCurrTarget = nullptr;
	mTargetLocked = nullptr;
	mAttacker = nullptr;
}

void UPkMsg::Recycle()
{
	if (mAttackerData != nullptr)
	{
		mAttackerData->Recycle();
		mAttackerData = nullptr;
	}
	if (mAttackerDataForCacul != nullptr)
	{
		mAttackerDataForCacul->Recycle();
		mAttackerDataForCacul = nullptr;
	}
	
	ClearTargets();

	IObjInterface::Recycle();
}

void UPkMsg::SetData(USkillTemplate* _skillTemp, AMyChar* _attacker, AMyChar* _target, const FVector& _targetLoc)
{
	mSkillTemp = _skillTemp;
	mAttacker = _attacker;
	mTargetLocked = _target;

	if (mSkillTemp)
	{
		mSkillId = _skillTemp->mId;

		//target 
		if (_target != nullptr)
		{
			mTargetId = _target->GetUuid(); //防止，发动技能过程中，目标死亡的情况
			mTargetLoc = mTargetLocked->GetActorLocation();

			//死亡回调
			auto charDeathCallback = [&](AMyChar* _deathChar)->void {
				mTargetLocked = nullptr;
				UE_LOG(BuffLogger, Warning, TEXT("--- UPkMsg::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
			};

			_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
		}
		else
		{
			mTargetLoc = _targetLoc;
		}

		//attack //TODO:不是必要，可以技能过程中攻击者死亡，后在拷贝战斗数据，一般情况下只需用指针获取攻击者战斗数据
		if (_attacker != nullptr)
		{
			mAttackerId = _attacker->GetUuid();

			//死亡回调
			auto charDeathCallback = [&](AMyChar* _deathChar)->void {
				mAttacker = nullptr;
				UE_LOG(BuffLogger, Warning, TEXT("--- UPkMsg::SetData, charDeathCallback, id:%d"), _deathChar->GetUuid());
			};

			_attacker->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
		}
		else
		{
			UE_LOG(BuffLogger, Error, TEXT("--- UPkMsg::SetData, _attacker == nullptr"));
		}
	}
}

void UPkMsg::AddTarget(AMyChar* _char, bool _isLocked /* = false */)
{
	UParam* param = GetObjMgr()->GetObj<UParam>(GetObjMgr()->mPkParamCls);
	param->Init(); 
	param->mTarget = _char;
	param->mIsLocked = _isLocked;
	param->mFightData->Copy(_char->GetDataComp()->GetFigthData());//复制目标的战斗数据
	mTargetArr.Add(param);
}

//每次pk完都清除目标集，持续进行pk
void UPkMsg::ClearTargets()
{
	for (UParam* param : mTargetArr)
	{
		param->Recycle();
	}
	mTargetArr.Empty();
}

void UPkMsg::SetAttackerData(UFightData* _data)
{
	mAttackerData = _data; //备份数据
	mAttackerDataForCacul = GetObjMgr()->GetObj<UFightData>(GetObjMgr()->mFightDataCls);
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
		case ESkillAttackType::Physics: // 物理伤害
		{
			if (_isAdd)
				mCurrTarget->mDmgPhyValue += _value;
			else
				mCurrTarget->mDmgPhyValue -= _value;

			UE_LOG(PkLogger, Warning, TEXT("--- UPkMsg::SetAttackDmgValue, ATTACK_PHY:%f"), _value);
			break;
		}
		case ESkillAttackType::Magic: // 法术伤害
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