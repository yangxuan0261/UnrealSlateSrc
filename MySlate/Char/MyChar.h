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
class UCharData;
class USkeletalMeshComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDeathDlg, AMyChar*, MyCharBp);

UCLASS()
class AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	AMyChar();
	virtual ~AMyChar();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void Destroyed() override; //用于释放成员，调用Destroy();会立即调用
public:
	void	OnCDFinish(UCoolDown* _cd);
	FDeathDlg&	GetDeathDlg() { return mDeathDlg; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void	SetUuid(int32 _uuid) { mUuid = _uuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void	SetCharData(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		int32	GetUuid() const { return mUuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		UseSkill(int32 _skillId, int32 _targetId, FVector _targetLoc = FVector(0.f, 0.f, 0.f));

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		SetUsingSkillNull() { mUsingSkill = nullptr; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		USkillFunction*	GetUsingSkill() const { return mUsingSkill; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		ChangeState(CharState _state) { mCharState = _state; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		const CharState&	GetState() const { return mCharState; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar")
		void		OnDeath();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual void Reset();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual UMyCharDataComp* GetDataComp() const { return mDataComp; }

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UCharData*			mCharData;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		FDeathDlg		mDeathDlg; //绑定： buff管理器、

private:
	UCharMgr*	gCharMgr; //char 管理器
};
