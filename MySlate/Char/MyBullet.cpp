
#include "MySlate.h"
#include "MyBullet.h"

#include "./AI/MyAIController.h"
#include "./MyChar.h"
#include "./Comp/MyCharDataComp.h"
#include "./Skill/Template/SkillTemplate.h"
#include "./CharMgr.h"
#include "./Skill/Pk/PkMsg.h"
#include "Skill/Pk/PkProcess.h"

#include "./Object/ObjMgr.h"

AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("MySphereComp"));
	sphereComp->InitSphereRadius(1.0f);
	CollisionComp = sphereComp;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	//CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	//sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp2"));
	//sphereComp->InitSphereRadius(2.0f);
	//MyRoot = sphereComp;
	//MyRoot->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	////CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	////CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	////CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	//MyRoot->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	//MyRoot->AttachTo(RootComponent);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("MyProjectileComp"));
	MovementComp->SetUpdatedComponent(RootComponent);
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 0.f;
	MovementComp->InitialSpeed = 0.f;

	//TODO: mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyMeshComp"));
	MeshComp->AttachTo(CollisionComp);

	mTargetId = 0;
	mSkillTemp = nullptr;
	mTargetLoc = FVector::ZeroVector;
	mPkMsg = nullptr;
	mPkProcess = nullptr;
	mFlying = false;
	mSpeed = 0;
	mStartPos = FVector::ZeroVector;
	mTarget = nullptr;
}

AMyBullet::~AMyBullet()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::~AMyBullet"));
}

void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	IBehavInterface::BehavTick(DeltaSeconds);

	if (!mFlying)
	{
		return;
	}


	if (mTargetId > 0) //锁定目标
	{
		AMyChar* target = mTarget;
		if (target != nullptr) //目标未死亡，每帧修正到目标的飞行方向
		{
			FVector targetLoc = target->GetActorLocation();
			if (mTargetLoc != targetLoc)
			{
				FVector bulletLoc = GetActorLocation();
				FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
				SetActorRotation(rota);
				MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //子弹移动方向
				
				mPkMsg->SetTargetLoc(targetLoc); // 调整Loc都是为了结算时目标死亡，影响选人逻辑
				mTargetLoc = targetLoc;
			}
		}
	}

	if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc)
	{
		if (mSkillTemp->mBltElem->mFlyDist > 0)
		{
			float distSq = FVector::DistSquared(GetActorLocation(), mStartPos);
			float flyDist = FMath::Pow((float)mSkillTemp->mBltElem->mFlyDist, 2.f);

			if (distSq > flyDist)
			{
				DestroyBullet();
				UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Tick, distSq > flyDist"));
			}
		}
	}
	else if (mSkillTemp->mBltElem->mLockedType == ELockedType::Char) //被锁定目标死亡情况，不做任何结算
	{
		if (mPkMsg->GetTargetId() > 0 && mPkMsg->GetTarget() == nullptr)
		{
			if (GetActorLocation().Equals(mTargetLoc, mSkillTemp->mBltElem->mTolerance))
			{
				DestroyBullet();
				UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Tick, target death, bullet arrival"));
				//CreatePk();
				//BulletJump();
			}
		}
	}
}

void AMyBullet::Destroyed()
{
	if (MovementComp != nullptr)
	{
		MovementComp->DestroyComponent();
	}	
	//if (MyRoot != nullptr)
	//{
	//	MyRoot->DetachFromParent();
	//	MyRoot->DestroyComponent();
	//}	
	if (MeshComp != nullptr)
	{
		MeshComp->DetachFromParent();
		MeshComp->DestroyComponent();
	}
	if (CollisionComp != nullptr)
	{
		CollisionComp->DetachFromParent();
		CollisionComp->DestroyComponent();
	}
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::Destroyed"));
	Super::Destroyed();
}

void AMyBullet::SetTargetAndLoc(AMyChar* _target, const FVector& _targetLoc)
{
	mTargetLoc = _targetLoc;
	
	if (_target != nullptr)
	{
		mTarget = _target;
		mTargetId = _target->GetUuid();

		//死亡回调
		auto charDeathCallback = [&](AMyChar* _deathChar)->void {
			mTarget = nullptr;
			UE_LOG(BuffLogger, Warning, TEXT("--- AMyBullet::SetTargetAndLoc, id:%d"), _deathChar->GetUuid());
		};

		_target->AddDeathNotify(FDeathOneNotify::CreateLambda(charDeathCallback));
	}
}

void AMyBullet::SetPkMsg(UPkMsg* _pkMsg)
{
	mPkMsg = _pkMsg;
	UE_LOG(BuffLogger, Warning, TEXT("--- AMyBullet::SetPkMsg"));
}

void AMyBullet::SetFly(bool _fly)
{
	mFlying = _fly;
	if (_fly) //开始飞行，设置移动组件的的速度矢量，并朝向目标 or Loc
	{
		mStartPos = GetActorLocation();//记录一下开始点

		if (mTarget != nullptr)
		{
			mTargetLoc = mTarget->GetActorLocation();
			SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTargetLoc));//朝向目标
		}

		MovementComp->InitialSpeed = (float)mSpeed;
		MovementComp->MaxSpeed = (float)mSpeed;
		MovementComp->Velocity = MovementComp->GetMaxSpeed() * (mTargetLoc - GetActorLocation()).GetSafeNormal(); //子弹移动方向
		CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnMyCollisionCompBeginOverlap);

		//如果锁定地点，且飞行距离 > 0，则飞行距离一定大于开始点与目标点的距离，比如黑暗游侠的箭，会飞行一定的距离才消失
		if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc && mSkillTemp->mBltElem->mFlyDist > 0)
		{
			float distSq = (mTargetLoc, mStartPos).Size();
			float flyDist = mSkillTemp->mBltElem->mFlyDist;

			if (flyDist < distSq)
			{
				UE_LOG(BulletLogger, Error, TEXT("--- AMyBullet::SetFly, flyDist < distSq, %f < %f "), flyDist, distSq);
			}
		}

		if (mSpeed == 0)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::SetFly, bullet speed == 0 "));
		}
	}
	else
	{
		MovementComp->Velocity = FVector::ZeroVector;
	}
}

void AMyBullet::CallbackPkOver(TArray<UDamageInfo*> _dmgArr)
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CallbackPkOver, _dmgArr size:%d"), _dmgArr.Num());

}

void AMyBullet::CreatePk()
{
	//TODO: 技编数据, 做技能表现
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, targetId:%d"), mPkMsg->GetTargetId());

	//设置本次结算被锁定的目标
	AMyChar* target = mPkMsg->GetTarget();
	if (target != nullptr)
	{
		target->TempNotifyB();
	}
	//return; //for test

	//TODO: 暂时不做结算
	if (mPkProcess == nullptr)
	{
		if (target != nullptr)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock != null, id:%d"), target->GetUuid());

			mPkProcess = GetObjMgr()->GetObj<UPkProcess>(GetObjMgr()->mPkProcessCls);
			mPkProcess->SetPkOverDlg(FPkOverDlg::CreateUObject(this, &AMyBullet::CallbackPkOver));
			mPkMsg->SetTarget(target);
			mPkProcess->SetMsg(mPkMsg);
			mPkProcess->Run();

			mPkProcess->Recycle();
			mPkProcess = nullptr;
		}
		else
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock is null"));
		}
	}
}

//子弹弹射
void AMyBullet::BulletJump()
{
	int32 count = 0; //getBulletFunc->getcount();暂时不弹射
	if (count > 0)
	{
	}
	else //不弹射直接销毁子弹
	{
		DestroyBullet();
	}
}

//void AMyBullet::OnHit(const FHitResult& HitResult)
//{
//	DealDamage(HitResult);
//	OnProjectileHit(HitResult.Actor.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal);
//
//	if (RemainingDamage <= 0)
//		DestroyBullet();
//}

void AMyBullet::DestroyBullet()
{
	IBehavInterface::RemoveBehavElemAll();

	if (mPkProcess != nullptr)
	{
		mPkProcess->Recycle();
		mPkProcess = nullptr;
	}
	if (mPkMsg != nullptr) //如果子弹发射出去了， pkMsg应该跟随子弹释放
	{	
		mPkMsg->Recycle();
		mPkMsg = nullptr;
	}

	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyChar* target = Cast<AMyChar>(OtherActor);
	if (target == nullptr)
	{
		return;
	}

	//TODO: 暂时先只对敌方,飞行过程中碰撞框碰撞到的目标，即时结算
	if (mSkillTemp->mBltElem->mLockedType == ELockedType::Loc && mSkillTemp->mBltElem->mFlyDist > 0)
	{
		if (target->GetDataComp()->GetTeamType() != mPkMsg->GetAttackerTeam())
		{
			mPkMsg->SetTargetId(target->GetUuid());
			mPkMsg->SetTarget(target);
			CreatePk();
		}
	}
	else if (mSkillTemp->mBltElem->mLockedType == ELockedType::Char) //TODO: 暂时先只对敌方锁定目标造成伤害
	{
		int32 targetId = target->GetUuid();
		if (mPkMsg->GetTargetId() > 0 && mPkMsg->GetTarget() != nullptr)
		{
			CreatePk();
			BulletJump();
		}
	}
}
