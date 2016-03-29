// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Char/MyChar.h"
#include "Char/MyCharDataComp.h"

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
	CollisionComp->bCanEverAffectNavigation = false;
	RootComponent = CollisionComp;

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	MovementComp->UpdatedComponent = CollisionComp;
	MovementComp->ProjectileGravityScale = 0.0f;
	MovementComp->MaxSpeed = 300.f;
	MovementComp->InitialSpeed = 300.f;

	bInitialized = false;
	mAttackActor = nullptr;
	mSkillTemp = nullptr;
}

AMyBullet::~AMyBullet()
{

}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
}

void AMyBullet::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AMyBullet::LifeSpanExpired()
{
	OnProjectileDestroyed();
	Super::LifeSpanExpired();
}

void AMyBullet::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	if (!bInitialized)
		return;

	AMyChar* OtherChar = Cast<AMyChar>(OtherActor);
	if (!OtherChar || !mAttackActor)
		return;

	if (mTargetActors.Find(OtherChar) != INDEX_NONE)
		return;

	//add enemy
	if (mAttackActor->mDataComp->mTeam != OtherChar->mDataComp->mTeam)
	{
		mTargetActors.AddUnique(OtherChar);

		FHitResult PawnHit;
		PawnHit.Actor = OtherChar;
		PawnHit.Component = OtherChar->GetCapsuleComponent();
		PawnHit.bBlockingHit = true;
		PawnHit.Location = PawnHit.ImpactPoint = GetActorLocation();
		PawnHit.Normal = PawnHit.ImpactNormal = -MovementComp->Velocity.GetSafeNormal();

		OnHit(PawnHit);
	}
}

void AMyBullet::InitProjectile(const FVector& Direction, uint8 InTeamNum, int32 ImpactDamage, float InLifeSpan)
{
	MovementComp->OnProjectileStop.AddDynamic(this, &AMyBullet::OnHit);
	MovementComp->Velocity = MovementComp->InitialSpeed * Direction;

	SetLifeSpan(InLifeSpan);

	RemainingDamage = ImpactDamage;
	bInitialized = true;
}

void AMyBullet::OnHit(FHitResult const& HitResult)
{
	DealDamage(HitResult);
	OnProjectileHit(HitResult.Actor.Get(), HitResult.ImpactPoint, HitResult.ImpactNormal);

	if (RemainingDamage <= 0)
	{
		OnProjectileDestroyed();
		Destroy();
	}
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