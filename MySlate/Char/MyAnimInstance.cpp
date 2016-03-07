// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyAnimInstance.h"
#include "Engine.h"
#include "MyChar.h"

UMyAnimInstance::UMyAnimInstance()
{
	mOwnerChar = nullptr;
}

bool UMyAnimInstance::IsMoving()
{
	ACharacter* character = GetOwnerChar();
	if (!character)
		return false;

	float wallSpeed = FVector::DotProduct(character->GetVelocity(), character->GetActorRotation().Vector());
	return wallSpeed > 0.f ? true : false;
}

ACharacter* UMyAnimInstance::GetOwnerChar()
{
	if (!mOwnerChar)
	{
		APawn* owner = TryGetPawnOwner();
		mOwnerChar = owner ? Cast<ACharacter>(owner) : nullptr;
	}
	return mOwnerChar;
}

void UMyAnimInstance::AnimNotify_Begin(UAnimNotify * Notify)
{
	AMyChar* mychar = Cast<AMyChar>(GetOwnerChar());
	if (mychar)
	{
		FString str = FString::Printf(TEXT("--- AnimNotify_Begin - %d"), mychar->mHealth);
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	}
}

void UMyAnimInstance::AnimNotify_End(UAnimNotify * Notify)
{
	FString str = FString::Printf(TEXT("--- AnimNotify_End"));
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str);
}
