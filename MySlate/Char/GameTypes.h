// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameTypes.generated.h"

UENUM()
enum class EGroup : uint8 //¶ÓÎé±àºÅ
{
	None = 0,
	Group1,
	Group2,
	Group3,
	Group4,
	Count,
};

UENUM()
enum class ETeam : uint8 //ÊÇµÐÊÇÓÑ
{
	None = 0,
	Teammate,
	Enemy,
};

UENUM(BlueprintType)
enum class CharState : uint8 //¶¯»­×´Ì¬
{
	IdleRun = 0,
	Attack,
	Injured,
	Death,
	Count,
};