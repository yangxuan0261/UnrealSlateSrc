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

UENUM()
enum class ESkillAttackType : uint8 //技能攻击类型
{
	ATTACK_PHY = 1,	//物理伤害
	ATTACK_MAG,		//魔法伤害
	ATTACK_CURE,	//治疗
	ATTACK_POWER,	//能量
	ATTACK_BUFF,	//buffer
	ATTACK_SUCKHP,	//吸血
	ATTACK_REBOUND	//反伤
};