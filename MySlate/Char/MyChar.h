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
	void OnCDFinish(UCoolDown* _cd);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		IsAlive();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar")
		void		OnDeath();

	//UFUNCTION(BlueprintCallable, Category = "MyChar")
		//void FaceToTarget();
public:
	/** The class of minion to spawn. */
	UPROPERTY(EditDefaultsOnly, Category = Category = "MyChar")
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
public:

};
