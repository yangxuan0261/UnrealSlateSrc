// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "SkillTemplate.h"

// Sets default values
USkillTemplate::USkillTemplate() : Super()
{
	mId			= -1;
	mName		= TEXT("Default SkillName");
	mDescr		= TEXT("Default SkillDescr");
	mCoolDown	= 5.f;
}

USkillTemplate::~USkillTemplate()
{

}

