// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyAnimInstance.h"
#include "Engine.h"
#include "MyChar.h"
#include "MyBullet.h"

DECLARE_LOG_CATEGORY_EXTERN(MyAnimInstLogger, Log, All);
DEFINE_LOG_CATEGORY(MyAnimInstLogger)

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
	ACharacter* character = GetOwnerChar();
	if (!character)
		return false;

	float wallSpeed = FVector::DotProduct(character->GetVelocity(), character->GetActorRotation().Vector());
	return wallSpeed > 0.f ? true : false;
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
	
	if (mOwnerChar)
	{
		UE_LOG(MyAnimInstLogger, Warning, TEXT("--- AnimNotify_BulletCreate"));


	}
}

void UMyAnimInstance::AnimNotify_BulletShoot(UAnimNotify * Notify)
{
	if (mOwnerChar)
	{
		//UE_LOG(MyAnimInstLogger, Warning, TEXT("--- AnimNotify_BulletShoot"));
		
		// spawn a bullet
		//FActorSpawnParameters SpawnInfo;
		//SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

		//AMyBullet* bullet = GetWorld()->SpawnActor<AMyBullet>(mOwnerChar->BulletClass, mOwnerChar->GetActorLocation(), mOwnerChar->GetActorRotation(), SpawnInfo);
		//bullet->SetAttacker(mOwnerChar);
	}
	
}

void UMyAnimInstance::AnimNotify_AttackOver(UAnimNotify * Notify)
{
	if (mOwnerChar) //攻击完切回正常状态
	{
		if (mOwnerChar->mCharState == CharState::Attack)
		{
			mOwnerChar->mCharState = CharState::IdleRun;
		}
	}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (!mOwnerChar)
	{
		mOwnerChar = GetOwnerChar();
	}

	if (mOwnerChar)
	{
		mSpeed = mOwnerChar->GetVelocity().Size(); //设置速度
		mCharState = mOwnerChar->mCharState; //设置动画状态
	}
}
