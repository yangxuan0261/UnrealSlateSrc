// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "Function/Funcs/AbsPkEvent.h"

// Sets default values
USkillFunction::USkillFunction() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetId = 0;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);
	if (mPkMsg)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg = nullptr;
	}
}

void USkillFunction::Tick(float DeltaSeconds)
{

}

void USkillFunction::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = _skillTemp->mId;
	mType = _skillTemp->mSkillType;

}

void USkillFunction::UseSkill(int32 _targetId, const FVector& _targetLoc)
{
	mTargetId = _targetId;
	mTargetLoc = _targetLoc;
}



bool USkillFunction::CanAttack()
{
	AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
	if (target)
	{
		float DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).Size();
		float atkDist = mSkillTemplate->mAttackDist;
		return atkDist > DistSq ? true : false;
	}
	return false;
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
	}

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();

	//step1 - 运行给攻击者自己加buff的func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(mPkMsg);
	}

	//step2 - 运行技能前置func, 比如瞬间移动
	const TArray<UAbsPkEvent*>& functions2 =mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(mPkMsg);
	}
}



void USkillFunction::BulletCreate()
{
	if (mBullet != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mBullet != nullptr before"));
	}

	if (mAttacker)
	{
		 //TODO: 创建子弹, 绑定到身体的某个socket部位上
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		mBullet = GetWorld()->SpawnActor<AMyBullet>(mAttacker->BulletClass, mAttacker->GetActorLocation(), mAttacker->GetActorRotation(), SpawnInfo);
	}
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr)
	{
		//TODO: 射击，脱离绑定点，朝目标飞行


		//TODO: 创建pk信息，带上攻击者数据
		UFightData* attackerData = NewObject<UFightData>(UFightData::StaticClass());
		attackerData->AddToRoot();//在pkMsg的析构函数中释放这个对象

		UPkMsg* pkMsg = mPkMsg;
		UFightData* dataComp = mAttacker->GetDataComp()->GetFigthData();
		dataComp->Clone(*attackerData);//将攻击者的战斗数据拷贝到 新建的战斗数据对象中
		pkMsg->SetAttackerData(attackerData);
		mBullet->SetPkMsg(pkMsg);

		mBullet = nullptr;//发射出去后子弹、pkmsg置空
		mPkMsg = nullptr;
	}
}

void USkillFunction::SkillEnd()
{
	//切换状态，使用中的技能置空
	if (mAttacker)
	{
		mAttacker->ChangeState(CharState::IdleRun);
		mAttacker->SetUsingSkillNull();
	}
}

