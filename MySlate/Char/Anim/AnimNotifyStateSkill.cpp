// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AnimNotifyStateSkill.h"

#include "Char/MyChar.h"
#include "../Skill/SkillFunction.h"

UAnimNotifyStateSkill::UAnimNotifyStateSkill(): Super()
{
	mOwnerChar = nullptr;
}

UAnimNotifyStateSkill::~UAnimNotifyStateSkill()
{

}

void UAnimNotifyStateSkill::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	if (mOwnerChar == nullptr)
		mOwnerChar = Cast<AMyChar>(MeshComp->GetOwner());

	if (mOwnerChar != nullptr)
	{
		mOwnerChar->GetUsingSkill()->SkillBegin();
	}
	else
	{
		UE_LOG(AnimLogger, Error, TEXT("--- UAnimNotifyStateSkill::NotifyBegin, mOwnerChar == nullptr"));
	}
}

void UAnimNotifyStateSkill::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (mOwnerChar != nullptr)
	{

	}
}

void UAnimNotifyStateSkill::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (mOwnerChar != nullptr)
	{
		mOwnerChar->GetUsingSkill()->SkillEnd();
	}
}
