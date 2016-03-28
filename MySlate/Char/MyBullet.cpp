// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBullet.h"


// Sets default values for this component's properties
AMyBullet::AMyBullet()
{
	PrimaryActorTick.bCanEverTick = true;
}

AMyBullet::~AMyBullet()
{

}

// Called when the game starts
void AMyBullet::BeginPlay()
{
	Super::BeginPlay();
}

