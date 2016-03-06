// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyAnimInstance.h"

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
