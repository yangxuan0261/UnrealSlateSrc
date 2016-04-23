// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillFunction.h"

#include "Template/SkillTemplate.h"
#include "Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "CoolDown/CoolDown.h"
#include "Function/Funcs/AbsPkEvent.h"

USkillFunction::USkillFunction() : Super()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetId = 0;
	mTargetLoc = FVector::ZeroVector;
	mCanAttack = false;
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction"));
}

void USkillFunction::BeginDestroy()
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg->ConditionalBeginDestroy();
		mPkMsg = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BeginDestroy:%d"), mSkillId);
	Super::BeginDestroy();
}

void USkillFunction::Tick(float DeltaSeconds)
{
	if (!mCanAttack)
	{
		mCanAttack = CanAttack();
	}

	if (mCanAttack)
	{
		if (mAttacker->GetState() != CharState::Attack)
		{
			mAttacker->ChangeState(CharState::Attack);
			//朝向敌人
			AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
			FVector targetLoc = target != nullptr ? target->GetActorLocation() : mTargetLoc;
			mAttacker->FaceToTargetLoc(targetLoc);
		}
	}
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
	return true; //for test

	AMyChar* target = mTargetId > 0 ? UCharMgr::GetInstance()->GetChar(mTargetId) : nullptr;
	float DistSq = 0.f;
	if (target) //锁定目标
	{
		DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).SizeSquared();
	}
	else //锁定地点
	{
		DistSq = (mTargetLoc - mAttacker->GetActorLocation()).SizeSquared();
	}
	float atkDist = mSkillTemplate->mAttackDist;
	return FMath::Pow(atkDist, 2) > DistSq ? true : false;
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
	}

	mOwnerCD->Restart();

	UPkMsg* pkMsg = NewObject<UPkMsg>(UPkMsg::StaticClass());
	pkMsg->AddToRoot();
	mPkMsg = pkMsg;

	pkMsg->SetData(mSkillTemplate, mAttacker->GetUuid(), mTargetId, mTargetLoc);

	UFightData* attackerData = mAttacker->GetDataComp()->GetFigthData()->Clone();//将攻击者的战斗数据拷贝到 新建的战斗数据对象中
	attackerData->AddToRoot();//在pkMsg的析构函数中释放这个对象
	pkMsg->SetAttackerData(attackerData);
	pkMsg->SetAttackerTeam(mAttacker->GetDataComp()->GetTeamType());
	//step1 - 运行技能前置func, 比如瞬间移动
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(mPkMsg);
	}

	//step2 - 运行buff前置事件 一般用于放技能前要buff，运行给攻击者自己加buff的func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(mPkMsg);
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
		 //TODO: 创建子弹,带上pk信息, 绑定到身体的某个socket部位上
		FActorSpawnParameters SpawnInfo;
		SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		mBullet = GWorld->SpawnActor<AMyBullet>(mAttacker->BulletClass, SpawnInfo);
		mBullet->SetPkMsg(mPkMsg);
		mBullet->SetSkillTemplate(mSkillTemplate);
		mBullet->SetTargetAndLoc(mTargetId, mTargetLoc);  
		mBullet->SetSpeed(mSkillTemplate->mBulletSpeed);
		mBullet->SetFly(false);

		if (mSkillTemplate->mAttachPoint.Len() > 0) //有绑定部位
		{
			//TODO: 技编数据, 设置矩阵信息transform
			mBullet->AttachRootComponentTo(mAttacker->GetMesh(), FName(*mSkillTemplate->mAttachPoint));
			mBullet->SetActorRelativeLocation(FVector::ZeroVector);
			mBullet->SetActorRelativeRotation(FRotator::ZeroRotator);
			mBullet->SetActorRelativeScale3D(FVector(1.f, 1.f, 1.f));
		}
		else
		{
			mBullet->SetActorLocation(mAttacker->GetActorLocation());
			mBullet->SetActorRotation(mAttacker->GetActorRotation());
		}
	}
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr && mPkMsg != nullptr)
	{
		//step3 - 运行给攻击者自己提升攻击力的func
		const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforeEvns();
		for (UAbsPkEvent* func : functions)
		{
			func->RunBeforeEvns(mPkMsg);
		}

		//TODO: 射击，脱离绑定点，朝目标飞行，绑定碰撞组件碰撞事件
		//mBullet->GetRootComponent()->DetachFromParent();
		mBullet->DetachRootComponentFromParent();

		mBullet->SetFly(true);
		mBullet->CollisionComp->OnComponentBeginOverlap.AddDynamic(mBullet, &AMyBullet::OnMyCollisionCompBeginOverlap);

		mBullet = nullptr;//发射出去后子弹、pkMsg置空，由子弹去释放pkMsg
		mPkMsg = nullptr;
	}
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletShoot, mBullet or mPkMsg is nullptr"));
	}
}

void USkillFunction::SkillEnd()
{
	//切换状态，使用中的技能置空
	if (mAttacker)
	{
		//step6 - 运行技能后置func, 比如瞬间移动移回原地
		const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetEndSkill();
		for (UAbsPkEvent* func : functions2)
		{	//issue mPkMsg is nullptr befor
			func->RunEndSkill(mPkMsg);
		}

		mAttacker->ChangeState(CharState::IdleRun);
		mAttacker->SetUsingSkillNull();
		mCanAttack = false;

		ReleaseData();
	}
}

void USkillFunction::ReleaseData()
{
	mAttacker->SetUsingSkillNull();
	mCanAttack = false;

	//尝试释放内存
	if (mBullet != nullptr) //创建子弹但没发射出去，技能就被打断，需要销毁子弹,pkMsg在里面会跟着销毁
	{
		mBullet->DestroyBullet();
		mBullet = nullptr;
		mPkMsg = nullptr;
	}
	else //还没有创建子弹，就必须这里销毁pkMsg
	{
		if (mPkMsg != nullptr)
		{
			mPkMsg->RemoveFromRoot();
			mPkMsg->ConditionalBeginDestroy();
			mPkMsg = nullptr;
		}
	}
}

