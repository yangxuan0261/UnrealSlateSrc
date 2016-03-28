// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "MyBullet.generated.h"

UCLASS()
class AMyBullet : public AActor
{
	GENERATED_BODY()

public:	
	AMyBullet();
	virtual ~AMyBullet();

	// Called when the game starts
	virtual void BeginPlay() override;
	

};
