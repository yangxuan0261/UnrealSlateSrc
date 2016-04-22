// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../Skill/Template/SkillTemplate.h"
#include "../GameTypes.h"
#include "MyAnimInstance.generated.h"

class AMyChar;

UCLASS()
class UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();
	virtual ~UMyAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		AMyChar* GetOwnerChar();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_SkillBegin(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_BulletCreate(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_BulletShoot(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_SkillEnd(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_Test(UAnimNotify* Notify);

	virtual	void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		float		mSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		CharState	mCharState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		EAnimType	mAnimType;
};
