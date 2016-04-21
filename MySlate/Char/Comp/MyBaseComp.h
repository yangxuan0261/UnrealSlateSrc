// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyBaseComp.generated.h"

UCLASS()
class UMyBaseComp : public UActorComponent
{
	GENERATED_BODY()

public:	
	UMyBaseComp();
	virtual ~UMyBaseComp();

	virtual void BeginPlay() override;
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;
	virtual void DestroyComponent(bool bPromoteChildren = false);

public:
	virtual void Reset();
};
