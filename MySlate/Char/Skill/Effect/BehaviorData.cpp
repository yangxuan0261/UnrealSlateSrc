// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BehaviorData.h"

UEffectDataElement::UEffectDataElement()
{
	mEffectID = 0;
	mEffectType = SkillEffectType::SelfFollow;
	mBindPoint = "";
	mDelayTime = 0.f;
	mOffset = FVector::ZeroVector;
	mScale = FVector::ZeroVector;
}

UEffectDataElement::~UEffectDataElement()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UEffectDataElement::~UEffectDataElement"));
}

UBehaviorData::UBehaviorData() : Super()
{

}

UBehaviorData::~UBehaviorData()
{

}


