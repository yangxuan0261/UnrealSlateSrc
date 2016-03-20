// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "SkillTypes.generated.h"

UENUM()
namespace ESkillType
{
	enum Type
	{
		Normal = 0,
		Initiative, //Ö÷¶¯
		Passive_A,
		Passive_B,
		Passive_C,
		Passive_Permanent,
		Count
	};
}