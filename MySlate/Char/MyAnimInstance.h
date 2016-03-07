// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Animation/AnimInstance.h"
#include "MyAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class MYSLATE_API UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		ACharacter* GetOwnerChar();

	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		void AnimNotify_Begin(UAnimNotify* Notify);
	UFUNCTION(BlueprintCallable, Category = "MyAnim")
		void AnimNotify_End(UAnimNotify* Notify);
private:
	ACharacter* mOwnerChar;
};
