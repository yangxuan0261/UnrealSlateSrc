// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbsPkEvent.generated.h"

class UPkMsg;
class UAbsBuff;

UCLASS()
class UAbsPkEvent : public UObject
{
	GENERATED_BODY()

public:
	struct PkInfo
	{
		PkInfo(int32 attId, int sId, int32 targetId, UAbsBuff* buff)
			:attUniqueId(attId)
			, skillId(sId)
			, targetUniqueId(targetId)
			, buffer(buff)
		{
		}

		uint32_t attUniqueId;	//buffer释放者
		int skillId;			//释放buffer的技能
		uint32_t targetUniqueId;//buffer所有者
		UAbsBuff* buffer;	//buffer
	};

public:
	// Sets default values for this character's properties
	UAbsPkEvent();
	virtual ~UAbsPkEvent();

	virtual UAbsPkEvent* Clone();

	virtual void RunBeforeSkill(UPkMsg* msg) {}
	virtual void RunBeforePk(UPkMsg* msg) {}
	virtual void RunBeforeEvns(UPkMsg* msg) {}
	virtual void RunEndEvns(UPkMsg* msg) {}
	virtual void RunEndPk(UPkMsg* msg) {}
	virtual void RunEndSkill(UPkMsg* msg) {}

	virtual void Paser(const TArray<FString>& _params) {}//解释数据

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UAbsFilter")
		FString		mKey;

};
