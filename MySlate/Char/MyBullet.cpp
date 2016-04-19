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

	//到达到Loc，结算
	if (mTargetLoc == GetActorLocation())
	{
		CreatePk();
		DestroyBullet();
	}
}

void AMyBullet::SetTargetId(int32 _targetId)
{
	mTargetId = _targetId;

	AMyChar* target = UCharMgr::GetInstance()->GetChar(_targetId);
	if (target != nullptr)
	{
		mTargetLoc = target->GetActorLocation();
		SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTargetLoc));
	}
}

void AMyBullet::SetTargetLoc(UPARAM(ref) const FVector& _targetLoc)
{
	mTargetLoc = _targetLoc;
	SetActorRotation(UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), _targetLoc));
}

void AMyBullet::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemp = _skillTemp;
}

void AMyBullet::SetFly(bool _fly)
{
	mFlying = mFlying;

	if (mSpeed > 0.f)
	{
		MovementComp->InitialSpeed = mSpeed;
		MovementComp->MaxSpeed = mSpeed;
		MovementComp->Velocity = MovementComp->GetMaxSpeed() * (mTargetLoc - GetActorLocation()).GetSafeNormal(); //子弹移动方向
	}
	else
	{
		UE_LOG(BulletLogger, Error, TEXT("--- AMyBullet::SetFly, mSpeed == 0.f"));
	}
}

void AMyBullet::PkOverCallback(TArray<FDamageInfo>& _dmgArr)
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyBullet::PkOverCallback, _dmgArr size:%d"), _dmgArr.Num());

}

void AMyBullet::CreatePk()
{
	//TODO: 做技能表现， 技编数据

	//TODO: 结算
	//mPkPorcess = NewObject<UPkPorcess>(UPkPorcess::StaticClass());
	//mPkPorcess->AddToRoot();
	//mPkPorcess->GetPkOverDlg().BindUObject(this, &AMyBullet::PkOverCallback);
	//mPkPorcess->SetMsg(mPkMsg);
	//mPkPorcess->Run();
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
	if (mTargetId > 0)//锁定目标，碰撞检测只检测是否为目标
	{
		AMyChar* target = UCharMgr::GetInstance()->GetChar(mTargetId);
		if (target != nullptr) //如果有目标对象，且碰撞到的对象为目标对象，开始结算
		{
			if (target == OtherChar)
			{
				//TODO: 这里做受击表现，结算，销毁子弹
				CreatePk();
				DestroyBullet();
			}
		}
	}
	else
	{
		//TODO: 锁定目标，子弹飞往目的地过程中，碰撞款撞到的敌人都应该做一次战斗结算，
		if (mPkMsg->GetAttackerTeam() != OtherChar->GetDataComp()->GetTeamType()) //不是同一队的
		{
			//

		}
	}

	//if (target == nullptr)
	//{
	//	UE_LOG(BulletLogger, Error, TEXT("--- Bullet Overlap, mTargetId > 0, but target ptr == null"));
	//	return;
	//}
}
