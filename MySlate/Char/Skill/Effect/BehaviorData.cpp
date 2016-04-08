// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "BehaviorData.h"

UEffectDataElement::UEffectDataElement()
{
	mEffectID = 0;
	mEffectType = SkillEffectType::SelfFollow;
	mBindPoint = "";
	mDelayTime = 0.f;
	mOffset = FVector(0.f, 0.f, 0.f);
	mScale = FVector(0.f, 0.f, 0.f);
}

UEffectDataElement::~UEffectDataElement()
{

}

UBehaviorData::UBehaviorData() : Super()
{

}

UBehaviorData::~UBehaviorData()
{

}


