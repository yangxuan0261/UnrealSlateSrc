// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "AnimNotifyStateSkill.h"

#include "Char/MyChar.h"

// Sets default values
UAnimNotifyStateSkill::UAnimNotifyStateSkill(): Super()
{
	mMyChar = nullptr;
}

UAnimNotifyStateSkill::~UAnimNotifyStateSkill()
{

}

void UAnimNotifyStateSkill::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	//if (mMyChar == nullptr)
	//	mMyChar = Cast<AMyChar>(MeshComp->GetOwner());

	//if (mMyChar != nullptr)
	//{
	//	//create bullet

	//}
	//else
	//{
	//	UE_LOG(AnimLogger, Warning, TEXT("--- UAnimNotifyStateSkill::NotifyBegin, mMyChar == nullptr"));

	//}

}

void UAnimNotifyStateSkill::NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime);
	if (mMyChar != nullptr)
	{

	}
}

void UAnimNotifyStateSkill::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	Super::NotifyEnd(MeshComp, Animation);
	if (mMyChar != nullptr)
	{
		//begin shoot

	}
}
