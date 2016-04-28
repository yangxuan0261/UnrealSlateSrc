// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Skill/Pk/PkProcess.h"

#include "MyBullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AMyChar;
class USkillTemplate;
class UPkMsg;
class UPkProcess;
//struct FDamageInfo;

/*
set target order
SetSkillTemplate
SetTargetLoc
SetSpeed
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
	virtual void Destroyed() override;
	// End Actor interface

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetTargetAndLoc(AMyChar* _target, const FVector& _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetSpeed(int32 _speed) { mSpeed = _speed; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetPkMsg(UPkMsg* _pkMsg) { mPkMsg = _pkMsg; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetFly(bool _fly);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void CallbackPkOver(TArray<FDamageInfo>& _dmgArr);

	//UFUNCTION()
	//	virtual void OnHit(const FHitResult& HitResult);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void CreatePk();

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void BulletJump();

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetSkillTemplate(USkillTemplate* _skillTemp) { mSkillTemp = _skillTemp; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void DestroyBullet();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileDestroyed();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileHit(AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	/** movement component */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UProjectileMovementComponent* MovementComp;

	//TODO: 这几个组件暂时由蓝图中编辑，后期动态生成碰撞形状、Mesh、粒子
	/** collisions root*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UShapeComponent* CollisionComp;

	/** Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UStaticMeshComponent* MeshComp;

	/** Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		TArray<UParticleSystemComponent*> Particles;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		int32				mTargetId; //受击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		AMyChar*			mTarget; //受击者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		USkillTemplate*		mSkillTemp; //技能模板
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		FVector				mTargetLoc; //目标地点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UPkMsg*				mPkMsg; //
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UPkProcess*			mPkProcess; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		bool				mFlying;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		int32				mSpeed;
private:
	FVector		mStartPos; //出生点
};
