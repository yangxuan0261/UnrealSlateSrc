// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyAnimInstance.h"

#include "../MyChar.h"
#include "../MyBullet.h"
#include "../Skill/SkillFunction.h"

UMyAnimInstance::UMyAnimInstance()
{
	mOwnerChar = nullptr;
	mSpeed = 0.f;
	mCharState = CharState::IdleRun;
}

UMyAnimInstance::~UMyAnimInstance()
{

}

bool UMyAnimInstance::IsMoving()
{
	return GetOwnerChar()->GetVelocity().Size() > 0.f ? true : false;
}

AMyChar* UMyAnimInstance::GetOwnerChar()
{
	if (!mOwnerChar)
	{
		APawn* owner = TryGetPawnOwner();
		mOwnerChar = owner ? Cast<AMyChar>(owner) : nullptr;
	}
	return mOwnerChar;
}

void UMyAnimInstance::AnimNotify_BulletCreate(UAnimNotify * Notify)
{
	if (mOwnerChar != nullptr)
	{
		mOwnerChar->GetUsingSkill()->BulletCreate();
	}
}

void UMyAnimInstance::AnimNotify_BulletShoot(UAnimNotify * Notify)
{
	if (mOwnerChar != nullptr)
	{
		mOwnerChar->GetUsingSkill()->BulletCreate();
	}
}

void UMyAnimInstance::AnimNotify_Test(UAnimNotify* Notify)
{
	if (mOwnerChar != nullptr)
	{
		mSpeed = mOwnerChar->GetVelocity().Size(); //设置速度
		mCharState = mOwnerChar->mCharState; //设置动画状态
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (mOwnerChar == nullptr)
	{
		mOwnerChar = GetOwnerChar();
	}

	if (mOwnerChar != nullptr)
	{
		mSpeed = mOwnerChar->GetVelocity().Size(); //设置速度
		mCharState = mOwnerChar->mCharState; //设置动画状态
	}
}
