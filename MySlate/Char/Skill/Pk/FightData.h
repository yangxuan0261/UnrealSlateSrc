// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include "../Utils/CommonDef.h"
#include "FightData.generated.h"

UCLASS()
class UFightData : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UFightData();
	virtual ~UFightData();
	void Clone(UFightData& _fightData);

	float GetAttackPhy() const { return mAttackPhy; }
	float GetLv() const { return mLv; }

public:
	//原始属性
	float		mAttackPhy;		//物理攻击

public:
	//成长相关
	int			mLv;			//等级

public:
};
