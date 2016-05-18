
#include "MySlate.h"
#include "SkillFunction.h"

#include "./Template/SkillTemplate.h"
#include "./Pk/PkMsg.h"
#include "../MyBullet.h"
#include "../CharMgr.h"
#include "../MyChar.h"
#include "../Comp/MyCharDataComp.h"
#include "./CoolDown/CoolDown.h"
#include "./Function/Funcs/AbsPkEvent.h"
#include "./Pk/FightData.h"
#include "../Effect/EffectMgr.h"
#include "../Object/ObjMgr.h"

USkillFunction::USkillFunction() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

USkillFunction::~USkillFunction()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction"));
}

void USkillFunction::BeginDestroy()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BeginDestroy:%d"), mSkillId);
	Super::BeginDestroy();
}

void USkillFunction::Reset()
{
	mSkillId = 0;
	mSkillTemplate = nullptr;
	mType = ESkillType::Normal;
	mPkMsg = nullptr;
	mBullet = nullptr;
	mAttacker = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mCanAttack = false;
	mMoving = false;
	mIsOver = false;
	mTarget = nullptr;
	mTargetId = 0;
}

void USkillFunction::Recycle()
{
	if (mPkMsg != nullptr)
	{
		mPkMsg->Recycle();
		mPkMsg = nullptr;
	}

	IObjInterface::Recycle();
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
			FVector targetLoc = mTarget != nullptr ? mTarget->GetActorLocation() : mTargetLoc;
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

void USkillFunction::UseSkill(AMyChar* _target, const FVector& _targetLoc)
{
	if (_target != nullptr)
	{
		mTarget = _target;
		mTargetId = _target->GetUuid();
		mTargetLoc = _target->GetActorLocation();

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mTarget = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- USkillFunction::UseSkill, charDeathCallback, id:%d"), _deathChar->GetUuid());
		};


		_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
	else
	{
		mTargetLoc = _targetLoc;
	}

}

bool USkillFunction::CanAttack()
{
	float DistSq = 0.f;
	AMyChar* target = mTarget;
	if (target != nullptr) //锁定目标，未死
	{
		DistSq = (target->GetActorLocation() - mAttacker->GetActorLocation()).SizeSquared();
	}
	else if (mTargetId > 0) //锁定目标，已死
	{
		if (mMoving) //移动中需要取消移动
		{
			mAttacker->GetController()->StopMovement();
		}
		CancelSkill();
		return false;
	}
	else //锁定地点
	{
		DistSq = (mTargetLoc - mAttacker->GetActorLocation()).SizeSquared();
	}
	float atkDist = mSkillTemplate->mAttackDist;
	bool ret = FMath::Pow(atkDist, 2) > DistSq ? true : false;

	if (ret)
	{
		if (mMoving) //移动中需要取消移动
		{
			mAttacker->GetController()->StopMovement();
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, stop moving, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		else
		{
			UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, dont need move, atkDist > DistSq, %f > %f"), atkDist, FMath::Sqrt(DistSq));
		}
		mMoving = false;
	}
	else
	{
		if (!mMoving)
		{
			if (target != nullptr) 
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to target"));
				UNavigationSystem::SimpleMoveToActor(mAttacker->GetController(), target);
			}
			else
			{
				UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CanAttack, move to location"));
				UNavigationSystem::SimpleMoveToLocation(mAttacker->GetController(), mTargetLoc);
			}
			mMoving = true;
		}
	}
	return ret;
}

void USkillFunction::CancelSkill()
{
	//向锁定的目标奔跑时，目标死亡，取消技能
	mTargetId = 0;
	mTarget = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mAttacker->ChangeState(CharState::IdleRun);
	mAttacker->SetUsingSkillNull();
	mCanAttack = false;
	mMoving = false;
	UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::CancelSkill"));
}

void USkillFunction::SkillBegin()
{
	if (mPkMsg != nullptr || mAttacker == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mPkMsg != nullptr before"));
		return;
	}

	//TODO: 技编数据, 做技能表现
	//mAttacker->TempNotifyA();
	mIsOver = false;

	mOwnerCD->Restart();

	UPkMsg* pkMsg = gGetObjMgr()->GetObj<UPkMsg>(gGetObjMgr()->mPkMsgCls);
	mPkMsg = pkMsg;
	pkMsg->SetData(mSkillTemplate, mAttacker, mTarget, mTargetLoc);

	UFightData* attackerData = mAttacker->GetDataComp()->GetFigthData()->Clone();//将攻击者的战斗数据拷贝到 新建的战斗数据对象中
	pkMsg->SetAttackerData(attackerData);
	pkMsg->SetAttackerTeam(mAttacker->GetTeamType());
	//step1 - 运行技能前置func, 比如瞬间移动
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetBeforeSkill();
	for (UAbsPkEvent* func : functions2)
	{
		func->RunBeforeSkill(pkMsg);
	}

	//step2 - 运行释放者pk前置事件，一般用于放技能前要buff，运行给攻击者自己加buff的func
	const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforePk();
	for (UAbsPkEvent* func : functions)
	{
		func->RunBeforePk(pkMsg);
	}

	//---------- 生产子弹
	//TODO: 创建子弹,带上pk信息, 绑定到身体的某个socket部位上
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mBullet = GWorld->SpawnActor<AMyBullet>(mAttacker->BulletClass, SpawnInfo);
	mBullet->SetPkMsg(pkMsg);
	mBullet->SetSkillTemplate(mSkillTemplate);
	mBullet->SetTargetAndLoc(pkMsg->GetTarget(), pkMsg->GetTargetLoc());
	mBullet->SetSpeed(mSkillTemplate->mBltElem->mBulletSpeed);
	mBullet->SetFly(false);
	mBullet->SetActorHiddenInGame(true); //创建子弹是才开始显示

	if (mSkillTemplate->mBltElem->mAttachPoint.Len() > 0) //有绑定部位
	{
		//TODO: 技编数据, 设置矩阵信息transform
		mBullet->AttachRootComponentTo(mAttacker->GetMesh(), FName(*mSkillTemplate->mBltElem->mAttachPoint));
		mBullet->SetActorRelativeLocation(mSkillTemplate->mBltElem->mLoc);
		mBullet->SetActorRelativeRotation(mSkillTemplate->mBltElem->mRotate);
		mBullet->SetActorRelativeScale3D(mSkillTemplate->mBltElem->mScale);
	}
	else
	{
		mBullet->SetActorLocation(mAttacker->GetActorLocation() + mSkillTemplate->mBltElem->mLoc);
		mBullet->SetActorRotation(mAttacker->GetActorRotation() + mSkillTemplate->mBltElem->mRotate);
		mBullet->SetActorScale3D(mSkillTemplate->mBltElem->mScale);
	}

	//---------- 技编, 特效数据逻辑
	gGetEffectMgr()->AttachBehav(mAttacker, EOwnType::Self, mBullet, mSkillTemplate->mBehavId);

	//---------- 技编, Mesh数据逻辑
	gGetEffectMgr()->AttachMesh(mBullet, mSkillTemplate);
}

void USkillFunction::BulletCreate()
{
	if (mBullet == nullptr)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::BulletCreate, mBullet == nullptr before"));
		return;
	}
	mBullet->SetActorHiddenInGame(false);
}

void USkillFunction::BulletShoot()
{
	if (mBullet != nullptr && mPkMsg != nullptr)
	{
		//step3 - 运行给攻击者自己提升攻击力的func，对每个单体目标而言
		const TArray<UAbsPkEvent*>& functions = mSkillTemplate->GetBeforeEvns();
		for (UAbsPkEvent* func : functions)
		{
			func->RunBeforeEvns(mPkMsg);
		}

		//TODO: 射击，脱离绑定点，朝目标飞行，绑定碰撞组件碰撞事件
		mBullet->DetachRootComponentFromParent();
		mBullet->SetFly(true);

		UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::BulletShoot, mBullet = nullptr"));
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
	//step6 - 运行技能后置事件, 比如瞬间移动移回原地
	const TArray<UAbsPkEvent*>& functions2 = mSkillTemplate->GetEndSkill();
	for (UAbsPkEvent* func : functions2)
	{	//issue mPkMsg is nullptr befor
		func->RunEndSkill(mPkMsg);
	}

	mIsOver = true;
	CancelSkill();
	ReleaseData();
}

void USkillFunction::ReleaseData()
{
	if (!mIsOver)
	{
		UE_LOG(SkillLogger, Error, TEXT("--- USkillFunction::ReleaseData, mIsOver == false"));

		CancelSkill();

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
				//mPkMsg->RemoveFromRoot();
				//mPkMsg->ConditionalBeginDestroy();
				mPkMsg->Recycle();
				mPkMsg = nullptr;
			}
		}
	}
}

