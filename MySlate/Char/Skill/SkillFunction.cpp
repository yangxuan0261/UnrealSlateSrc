// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"

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
	//运行技能前置func
	const TArray<UAbsPkEvent*>& functions =mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions)
	{
		
	}
}



void USkillFunction::BulletCreate()
{
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
		//射击，脱离绑定点，朝目标飞行


		//TODO: 创建pk信息，带上攻击者数据
		UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
		pkMsg->AddToRoot();
		FSetNullDlg dlg;
		dlg.BindUObject(this, &USkillFunction::SetDataNull);
		pkMsg->SetNullDlg(dlg);

		mBullet = nullptr;//发射出去后子弹置空
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

void USkillFunction::SetDataNull()
{
	mPkMsg = nullptr;//其他地方销毁通知一下这里，防止析构时野指针奔溃
}

