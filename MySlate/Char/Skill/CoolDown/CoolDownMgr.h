// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"

#include "CoolDownMgr.generated.h"

UCLASS()
class UCoolDownMgr : public UObject, public USingleton<UCoolDownMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCoolDownMgr();
	virtual ~UCoolDownMgr();

};
