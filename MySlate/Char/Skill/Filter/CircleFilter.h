// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CircleFilter.generated.h"

class AMyChar;
class UPkMsg;

UCLASS()
class UCircleFilter : public UAbsFilter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCircleFilter();
	virtual ~UCircleFilter();

	virtual void Filter(UPkMsg* msg) override;
	virtual UAbsFilter* Clone() override;
	virtual void Parser(const TArray<FString>& _params);

	static UCircleFilter* CreateFilter(const FString& _key);

public:
	//int32		mCenterType;	//中心点 -- 1:攻击者，-1:受击着
	int32		mSelectType;	//选人 -- 1:攻击方，-1:受击方
	int32		mCount;			//选人数量
	int32		mRadius;		//选人半径
};
