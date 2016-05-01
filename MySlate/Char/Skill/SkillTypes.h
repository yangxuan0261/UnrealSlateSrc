
#pragma once

#include "SkillTypes.generated.h"

UENUM()
enum class EAnimType : uint8 //技能动画
{
	None = 0,
	Skill_1,
	Skill_2,
	Skill_3,
	Skill_4,
	Skill_5,
	Skill_6,
	Skill_7,
	Injure_1,
	Injure_2,
	Victory_1,
	Victory_2,
	Victory_3,
	Count,
};

UENUM()
enum class EIntervalType : uint8 //buff类型周期
{
	Once = 0,	//一次性
	Interval,	//间隔性
	Durable,	//持续性
};

UENUM()
enum class EBuffState : uint8 //buff状态
{
	Idle = 0,
	Start,
	Break,
	Over,
};

UENUM()
enum class ESkillType : uint8 //技能类型
{
	Normal = 0,
	Initiative, //主动
	Passive_A,
	Passive_B,
	Passive_C,
	Passive_Permanent,
	Count,
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
	ATTACK_REBOUND,	//反伤
	Count,
};

//------------------- 
UENUM()
enum class EFilterType : uint8 //选人类型
{
	Locked = 0,	//锁定一人
	Circle,		//圆形
	Rect,		//矩形
	Count,
};

UENUM()
enum class ESelectType : uint8 //选人标记
{
	Enemy = 0,	//敌
	Self,		//我
	Count,
};

UENUM()
enum class ELockedType : uint8 //锁定类型
{
	Loc = 0,	//地点
	Char,		//人
	Count,
};