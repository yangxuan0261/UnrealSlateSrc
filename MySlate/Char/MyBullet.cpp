// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"

#include "AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/Comp/MyCharDataComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "CharMgr.h"
#include "Skill/Pk/PkMsg.h"
//#include "Skill/Pk/PkPorcess.h"

AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	USphereComponent* sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	sphereComp->InitSphereRadius(1.0f);
	CollisionComp = sphereComp;
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	//CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	//CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 300.f;
	MovementComp->InitialSpeed = 0.f;

	//TODO: mesh component
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->AttachTo(CollisionComp);

	mTargetId = 0;
	mSkillTemp = nullptr;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mPkMsg = nullptr;
	mPkPorcess = nullptr;
	mFlying = false;
	mSpeed = 0.f;
}

AMyBullet::~AMyBullet()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::~AMyBullet"));
}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();

}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (!mFlying)
	{
		return;
	}

	if (mTargetId > 0) //锁定目标
	{
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr) //目标未死亡，每帧修正到目标的飞行方向
		{
			FVector targetLoc = target->GetActorLocation();
			if (mTargetLoc != targetLoc)
			{
				FVector bulletLoc = GetActorLocation();
				FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
				SetActorRotation(rota);
				MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //子弹移动方向
				mTargetLoc = targetLoc;
			}
		}
	}

	//到达到Loc，结算，子弹弹射
	if (mTargetLoc == GetActorLocation())
	{
		CreatePk();
		BulletJump();
	}
}

void AMyBullet::SetTargetId(int32 _targetId)
{
	mTargetId = _targetId;
}

void AMyBullet::SetTargetLoc(UPARAM(ref) const FVector& _targetLoc)
{
	mTargetLoc = _targetLoc;
}

void AMyBullet::SetTargetAndLoc(int32 _targetId, UPARAM(ref) const FVector& _targetLoc)
{
	mTargetId = _targetId;
	mTargetLoc = _targetLoc;
}

void AMyBullet::SetFly(bool _fly)
{
	//开始飞行，设置移动组件的的速度矢量，并朝向目标 or Loc
	mFlying = mFlying;

	if (mSpeed > 0.f)
	{
		if (mTargetId > 0)
		{
			AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
			if (target != nullptr)
			{
				mTargetLoc = target->GetActorLocation();
			}
		}
		MovementComp->InitialSpeed = mSpeed;
		MovementComp->MaxSpeed = mSpeed;
		MovementComp->Velocity = MovementComp->GetMaxSpeed() * (mTargetLoc - GetActorLocation()).GetSafeNormal(); //子弹移动方向

		//朝向目标
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTargetLoc));
	}
	else
	{
		UE_LOG(BulletLogger, Error, TEXT("--- AMyBullet::SetFly, mSpeed == 0.f"));
	}
}

void AMyBullet::CallbackPkOver(TArray<FDamageInfo>& _dmgArr)
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CallbackPkOver, _dmgArr size:%d"), _dmgArr.Num());

}

void AMyBullet::CreatePk()
{
	//TODO: 做技能表现， 技编数据


	//TODO: 结算
	if (mPkPorcess == nullptr)
	{
		mPkPorcess = NewObject<UPkPorcess>(UPkPorcess::StaticClass());
		mPkPorcess->AddToRoot();
		mPkPorcess->GetPkOverDlg().BindUObject(this, &AMyBullet::CallbackPkOver);

		//设置本次结算被锁定的目标
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr)
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock != null, id:%d"), target->GetUuid());
		}
		else
		{
			UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::CreatePk, target lock is null"));
		}
		mPkMsg->SetTarget(target);
		mPkPorcess->SetMsg(mPkMsg);
		mPkPorcess->Run();

		mPkPorcess->RemoveFromRoot();
		mPkPorcess = nullptr;
	}
}

//子弹跳跃
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

	if (mPkPorcess != nullptr)
	{
		mPkPorcess->RemoveFromRoot();
		mPkPorcess = nullptr;
	}
	if (mPkMsg != nullptr)
	{
		mPkMsg->RemoveFromRoot();
		mPkMsg = nullptr;
	}

	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyChar* OtherChar = Cast<AMyChar>(OtherActor);
	//TODO：这里不针对锁定目标做结算，因为到达锁定目标的Loc后会做结算
	//		只针对飞行过程中碰撞框碰撞到的目标，即时结算
	//if (mTargetId > 0)//锁定目标，碰撞检测只检测是否为目标
	//{
	//	AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
	//	if (target != nullptr) //如果有目标对象，且碰撞到的对象为目标对象，开始结算
	//	{
	//		if (target == OtherChar)
	//		{
	//			//TODO: 这里做受击表现，结算，销毁子弹
	//			CreatePk();
	//			DestroyBullet();
	//		}
	//	}
	//}
	//else
	//{
		//TODO: 锁定目标，子弹飞往目的地过程中，碰撞款撞到的敌人都应该做一次战斗结算，
		if (mPkMsg->GetAttackerTeam() != OtherChar->GetDataComp()->GetTeamType()) //不是同一队的
		{
			//

		}
	//}

	//if (target == nullptr)
	//{
	//	UE_LOG(BulletLogger, Error, TEXT("--- Bullet Overlap, mTargetId > 0, but target ptr == null"));
	//	return;
	//}
}
