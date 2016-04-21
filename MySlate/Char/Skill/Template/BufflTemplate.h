// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/CommonHeader.h"

#include "BufflTemplate.generated.h"

UCLASS()
class UBufflTemplate : public UObject
{
	GENERATED_BODY()

public:
	UBufflTemplate();
	virtual ~UBufflTemplate();
	virtual void BeginDestroy() override;

};
