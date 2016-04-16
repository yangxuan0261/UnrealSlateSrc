// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameTypes.h"

#include "MyChar.generated.h"

class USMyAttachment;
class UCoolDownComp;
class UCoolDown;
class UMyCharDataComp;
class AMyBullet;
class USkillFunction;
class UCharMgr;

UCLASS()
class AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyChar();
	virtual ~AMyChar();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;

public:
	void	OnCDFinish(UCoolDown* _cd);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void	SetUuid(int32 _uuid) { mUuid = _uuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		int32	GetUuid() const { return mUuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		UseSkill(int32 _skillId, int32 _targetId, FVector _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		SetUsingSkillNull() { mUsingSkill = nullptr; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		USkillFunction*	GetUsingSkill() const { return mUsingSkill; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		ChangeState(CharState _state) { mCharState = _state; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar")
		void		OnDeath();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual void Reset();

	//UFUNCTION(BlueprintCallable, Category = "MyChar")
		//void FaceToTarget();
public:
	/* 设置子弹蓝图类 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		TSubclassOf<AMyBullet> BulletClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UCoolDownComp*		mCDComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UMyCharDataComp*	mDataComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		USkillFunction*		mUsingSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		CharState			mCharState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		TArray<UCoolDown*>	mCanUseSkillArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		int32				mUuid;
private:
	UCharMgr*	gCharMgr; //char 管理器
};
