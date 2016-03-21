// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.generated.h"

UENUM()
enum class ESkillType : uint8 //技能类型
{
	Normal = 0,
	Initiative, //主动
	Passive_A,
	Passive_B,
	Passive_C,
	Passive_Permanent,
	Count
};
