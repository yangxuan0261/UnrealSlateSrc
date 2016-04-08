// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BehaviorData.generated.h"

UENUM()
enum class SkillEffectType : uint8 //特效类型
{
	SelfFollow = 0,
	SelfUnfollow,
	TargetFollow,
	TargetUnfollow,
	Bullet,
	SceneCamera,
	Count,
};

UCLASS()
class UEffectDataElement : public UObject
{
	GENERATED_BODY()
public:
	UEffectDataElement();
	virtual ~UEffectDataElement();

	int32		mEffectID;//特效id
	SkillEffectType	mEffectType;//特效类型
	FString		mBindPoint; //绑定骨骼
	float		mDelayTime;//延时时长
	FVector		mOffset;
	FVector		mScale;
};

UCLASS()
class UBehaviorData : public UObject
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	UBehaviorData();
	virtual ~UBehaviorData();

private:

};
