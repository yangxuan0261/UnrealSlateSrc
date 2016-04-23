// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyChar.h"

#include "MyGameInstance.h"
#include "Level/MyLevelScriptActor.h"
#include "Skill/CoolDown/CoolDownComp.h"
#include "Skill/CoolDown/CoolDown.h"
#include "Skill/SkillFunction.h"
#include "Comp/MyCharDataComp.h"
#include "CharMgr.h"
#include "BaseDatas/BaseDataMgr.h"
#include "BaseDatas/Datas/CharData.h"
#include "Skill/Buff/BuffMgr.h"

// Sets default values
AMyChar::AMyChar() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//--------- 
	gCharMgr = nullptr;
	mCDComp = nullptr;
	mDataComp = nullptr;
	mUsingSkill = nullptr;
	mCharState = CharState::IdleRun;
	mUuid = 0;
	mCharData = nullptr;

}

AMyChar::~AMyChar()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::~AMyChar"));
}

void AMyChar::BeginPlay()
{
	Super::BeginPlay();
	gCharMgr = UCharMgr::GetInstance();

	//设置默认AI控制类，并生成一下
	AIControllerClass = AMyAIController::StaticClass();
	SpawnDefaultController();

	//注册cd组件
	mCDComp = NewObject<UCoolDownComp>(this, TEXT("CDComponent"));
	mCDComp->RegisterComponent();
	mCDComp->SetOwner(this);

	//注册data组件
	mDataComp = NewObject<UMyCharDataComp>(this, TEXT("CharDataComponent"));
	mDataComp->RegisterComponent();

	//绑定buff管理器
	mDeathDlg.AddDynamic(UBuffMgr::GetInstance(), &UBuffMgr::CharDeathNotify);

	//GetMesh()->SetSkeletalMesh(nullptr);
}

void AMyChar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	
	if (mCDComp != nullptr)
	{
		mCDComp->MyTick(DeltaTime);
	}

	if (mUsingSkill != nullptr)
	{
		mUsingSkill->Tick(DeltaTime);
	}
}

void AMyChar::Destroyed()
{

	if (mCDComp != nullptr)
	{
		mCDComp->DestroyComponent();
		mCDComp = nullptr;
	}

	if (mDataComp != nullptr)
	{
		mDataComp->DestroyComponent();
		mDataComp = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::Destroyed"));
	Super::Destroyed();
}

void AMyChar::OnCDFinish(UCoolDown* _cd)
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::OnCDFinish, skillId:%d"), _cd->GetSkillId());
	mCanUseSkillArr.AddUnique(_cd);
}

void AMyChar::SetCharData(int32 _id)
{
	UCharData* data = UBaseDataMgr::GetInstance()->GetCharData(_id);
	mDataComp->SetCharData(data);
}

bool AMyChar::IsAlive() const
{
	return mDataComp->mHealth > 0.f ? true : false;
}

bool AMyChar::UseSkill(int32 _skillId, int32 _targetId, FVector _targetLoc /* = FVector::ZeroVector */)
{
	bool canUse = false;
	if (mUsingSkill == nullptr)
	{
		USkillFunction* skillFunc = mCDComp->CanUseSkill(_skillId);
		if (skillFunc != nullptr)
		{
			skillFunc->UseSkill(_targetId, _targetLoc);
			mUsingSkill = skillFunc;
			canUse = true;
		}
	}		
	else
	{
		UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	}

	return canUse;
}

void AMyChar::ChangeState(CharState _state)
{
	mCharState = _state;
	//for test
	//USkillFunction* sdf = GetUsingSkill();
	//bool b = sdf != nullptr ? sdf->CanAttack() : false;
	//if (b)
	//{
	//	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	//}
}

void AMyChar::FaceToTargetLoc(const FVector& _targetLoc)
{
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _targetLoc));
}


void AMyChar::Death()
{
	mDeathDlg.Broadcast(this); //通知所有绑定了的代理

	//施放技能中被打死，释放创建的子弹和pkMsg
	if (mUsingSkill != nullptr)
	{
		mUsingSkill->ReleaseData();
		mUsingSkill = nullptr;
	}

	//TODO: 从管理器中移除，这里应该做回收，而不是销毁，暂时先销毁
	gCharMgr->RemoveChar(mUuid);

	OnDeath(); //通知一下蓝图

	ChangeState(CharState::Death);//等动画状态机通知销毁
}

void AMyChar::Reset()
{

}
