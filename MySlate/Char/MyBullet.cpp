// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Char/MyChar.h"
#include "Char/MyCharDataComp.h"
#include "Kismet/KismetMathLibrary.h"

DECLARE_LOG_CATEGORY_EXTERN(BulletLogger, Log, All);
DEFINE_LOG_CATEGORY(BulletLogger)

// Sets default values for this component's properties
AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;

	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(1.0f);
	CollisionComp->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	//CollisionComp->SetCollisionObjectType(COLLISION_PROJECTILE);
	CollisionComp->SetCollisionResponseToAllChannels(ECR_Ignore);
	CollisionComp->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CollisionComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 300.f;
	MovementComp->InitialSpeed = 300.f;

	bInitialized = false;
	mAttackActor = nullptr;
	mTargetActor = nullptr;
	mSkillTemp = nullptr;
	MovementComp->InitialSpeed = 0.f;
	mTargetLoc = FVector(0.f, 0.f, 0.f);
	mLastTargetLoc = FVector(0.f, 0.f, 0.f);
	RemainingDamage = 50.f;
}

AMyBullet::~AMyBullet()
{

}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();

	CollisionComp->OnComponentBeginOverlap.AddDynamic(this, &AMyBullet::OnCollisionCompBeginOverlap);//绑定碰撞组件碰撞事件
}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//每帧修正到目标的飞行方向
	if (mTargetActor != nullptr)
	{
		FVector targetLoc = mTargetActor->GetActorLocation();
		if ( mLastTargetLoc != targetLoc)
		{
			FVector bulletLoc = GetActorLocation();
			FRotator rota = UKismetMathLibrary::FindLookAtRotation(bulletLoc, targetLoc);
			SetActorRotation(rota);
			MovementComp->Velocity = MovementComp->GetMaxSpeed() * (targetLoc - bulletLoc).GetSafeNormal(); //子弹移动方向
			mLastTargetLoc = targetLoc;
		}
	}
}

void AMyBullet::LifeSpanExpired()
{
	OnProjectileDestroyed();
	Super::LifeSpanExpired();
}

void AMyBullet::InitProjectile(const FVector& Direction, uint8 InTeamNum, int32 ImpactDamage, float InLifeSpan)
{
	MovementComp->OnProjectileStop.AddDynamic(this, &AMyBullet::OnHit);
	MovementComp->Velocity = MovementComp->InitialSpeed * Direction;

	SetLifeSpan(InLifeSpan);

	RemainingDamage = ImpactDamage;
	bInitialized = true;
}

void AMyBullet::SetAttacker(AMyChar* _attacker)
{
	mAttackActor = _attacker;
}

void AMyBullet::SetTarget(AMyChar * _target)
{
	mTargetActor = _target;
}

void AMyBullet::SetSpeed(float _speed)
{
	MovementComp->InitialSpeed = _speed;
	MovementComp->MaxSpeed = _speed;
}

void AMyBullet::OnHit(const FHitResult& HitResult)
{
	DealDamage(HitResult);
	OnProjectileHit(HitResult.Actor.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal);

	if (RemainingDamage <= 0)
		DestroyBullet();
}

void AMyBullet::DestroyBullet()
{
	OnProjectileDestroyed();
	Destroy();
}

void AMyBullet::OnCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	AMyChar* OtherChar = Cast<AMyChar>(OtherActor);

	if (mTargetActor != nullptr) //如果有目标对象，碰撞到非目标对象直接返回
	{
		if (OtherChar == mTargetActor)
			DestroyBullet();
	}

	//if (!bInitialized)
	//	return;

	//AMyChar* OtherChar = Cast<AMyChar>(OtherActor);
	////if (!OtherChar || !mAttackActor)
	////	return;

	//if (mTargetActor != nullptr) //如果有目标对象，碰撞到非目标对象直接返回
	//{
	//	if (OtherChar == mTargetActor)
	//		DestroyBullet();
	//}


	////add enemy
	//if (mAttackActor->mDataComp->mTeam != OtherChar->mDataComp->mTeam)
	//{
	//	FHitResult PawnHit;
	//	PawnHit.Actor = OtherChar;
	//	PawnHit.Component = OtherChar->GetCapsuleComponent();
	//	PawnHit.bBlockingHit = true;
	//	PawnHit.Location = PawnHit.ImpactPoint = GetActorLocation();
	//	PawnHit.Normal = PawnHit.ImpactNormal = -MovementComp->Velocity.GetSafeNormal();

	//	OnHit(PawnHit);
	//}
}

void AMyBullet::DealDamage(FHitResult const& HitResult)
{
	//const AStrategyChar* HitChar = Cast<AStrategyChar>(HitResult.Actor.Get());
	//const float PrevHealth = HitChar ? HitChar->Health : 0.0f;

	////UGameplayStatics::ApplyPointDamage(HitResult.Actor.Get(), RemainingDamage, -HitResult.ImpactNormal, HitResult, NULL, this, UDamageType::StaticClass());

	//if (HitChar && !ConstantDamage)
	//{
	//	RemainingDamage -= FMath::TruncToInt(PrevHealth - HitChar->Health);
	//}
}