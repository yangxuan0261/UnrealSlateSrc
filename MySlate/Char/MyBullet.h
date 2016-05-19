
#pragma once

#include "./ExtInter/BehavInter.h"

#include "MyBullet.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class AMyChar;
class USkillTemplate;
class UPkMsg;
class UPkProcess;
class UDamageInfo;
class UBehavElem;

/*
set target order
SetSkillTemplate
SetTargetLoc
SetSpeed
*/

UCLASS()
class AMyBullet : public AActor, public IBehavInterface
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
		void SetPkMsg(UPkMsg* _pkMsg); 

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetFly(bool _fly);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void CallbackPkOver(TArray<UDamageInfo*> _dmgArr);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void CreatePk();

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void BulletJump();

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetSkillTemplate(USkillTemplate* _skillTemp) { mSkillTemp = _skillTemp; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void SetMeshComp(TArray<UStaticMeshComponent*> _meshCompVec) { MeshCompVec = _meshCompVec; }

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void DestroyBullet();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileDestroyed();

	UFUNCTION(BlueprintImplementableEvent, Category = "AMyBullet")
		void OnProjectileHit(AActor* HitActor, const FVector& HitLocation, const FVector& HitNormal);

	UFUNCTION(BlueprintCallable, Category = "AMyBullet")
		void OnMyCollisionCompBeginOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

public:
	//子弹的基础组件：移动和碰撞，粒子和mesh组件动态增加，都在UEffectMgr中生成并绑定
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UProjectileMovementComponent* MovementComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		UShapeComponent* CollisionComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		TArray<UStaticMeshComponent*> MeshCompVec;

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
		bool				mFlying;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyBullet")
		int32				mSpeed;
private:
	FVector		mStartPos; //出生点
	TMap<int32, TArray<UBehavElem*>>	mBehavMap;
};
