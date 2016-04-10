// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyBullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AMyChar;
class USkillTemplate;

UCLASS()
class AMyBullet : public AActor
{
	GENERATED_BODY()

public:	
	AMyBullet();
	virtual ~AMyBullet();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void LifeSpanExpired() override;
	// End Actor interface

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void InitProjectile(const FVector& ShootDirection, uint8 InTeamNum, int32 ImpactDamage, float InLifeSpan);


	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetAttacker(AMyChar* _attacker);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void SetTarget(AMyChar* _target);
		//void SetTarget_Implementation(AMyChar* _target);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void SetSpeed(float _speed);

	UFUNCTION()
		virtual void OnHit(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void DestroyBullet();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileDestroyed();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileHit(AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void OnCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:

	/** movement component */
	UPROPERTY(VisibleDefaultsOnly, Category = "AMyBullet")
		UProjectileMovementComponent* MovementComp;

	/** collisions */
	UPROPERTY(VisibleDefaultsOnly, Category = "AMyBullet")
		USphereComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		AMyChar*			mAttackActor; //攻击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		AMyChar*			mTargetActor; //受击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		USkillTemplate*		mSkillTemp; //技能模板
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		FVector				mTargetLoc; //目标地点

protected:
	void DealDamage(FHitResult const& HitResult);
	FVector		mLastTargetLoc;

	bool		bInitialized;
	int32		RemainingDamage;
};
