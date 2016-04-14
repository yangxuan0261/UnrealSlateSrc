// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyBullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AMyChar;
class USkillTemplate;

/*
set target order
SetSkillTemplate or SetSpeed
SetTargetLoc
*/

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
	// End Actor interface

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void InitProjectile(const FVector& ShootDirection, uint8 InTeamNum, int32 ImpactDamage, float InLifeSpan);


	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetAttackerId(int32 _attackerId) { mAttackerId = _attackerId; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void SetTargetId(int32 _targetId) { mTargetId = _targetId; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		virtual void SetSpeed(float _speed);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetTargetLoc(UPARAM(ref) const FVector& _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetSkillTemplate(USkillTemplate* _skillTemp);

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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UProjectileMovementComponent* MovementComp;

	/** collisions */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		USphereComponent* CollisionComp;

	/** Mesh */
	UPROPERTY(VisibleDefaultsOnly, Category = "AMyBullet")
		USkeletalMeshComponent* MeshComp;
public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		int32				mAttackerId; //攻击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		int32				mTargetId; //受击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		USkillTemplate*		mSkillTemp; //技能模板
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		FVector				mTargetLoc; //目标地点

protected:
	void DealDamage(FHitResult const& HitResult);
	FVector		mLastTargetLoc;

	bool		bInitialized;
	int32		RemainingDamage;
	float		mDist; //攻击距离
};
