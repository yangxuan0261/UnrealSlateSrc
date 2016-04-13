// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Func.generated.h"

class UAbsBuff;

UCLASS()
class UFunc : public UObject
{
	GENERATED_BODY()

public:

	struct PkInfo
	{
		PkInfo(int32 attId, int sId, int32 targetId, UAbsBuff* buff)
			:attUniqueId(attId)
			,skillId(sId)
			,targetUniqueId(targetId)
			,buffer(buff)
		{
		}

		uint32_t attUniqueId;	//buffer释放者
		int skillId;			//释放buffer的技能
		uint32_t targetUniqueId;//buffer所有者
		UAbsBuff* buffer;	//buffer
	};

	// Sets default values for this character's properties
	UFunc();
	virtual ~UFunc();

private:
};
