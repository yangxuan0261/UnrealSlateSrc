// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsFilter.generated.h"

/*
一般定义：
float		mValue; //数值
int32		mOwner; //所属者 -- 1:攻击者，-1:受击者
int32		mLimitId; //技能限制
*/

class AMyChar;
class UPkMsg;

UCLASS()
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* msg) {}//过虑可选actor
	virtual UAbsFilter* Clone() { return nullptr; }
	virtual void Parser(const TArray<FString>& _params) {}//解释数据

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;

};
