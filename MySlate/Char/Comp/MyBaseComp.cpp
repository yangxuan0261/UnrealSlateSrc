// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBaseComp.h"


// Sets default values for this component's properties
UMyBaseComp::UMyBaseComp()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

UMyBaseComp::~UMyBaseComp()
{

}

void UMyBaseComp::BeginPlay()
{
	Super::BeginPlay();
}

void UMyBaseComp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UMyBaseComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{

	Super::DestroyComponent(bPromoteChildren);
}

void UMyBaseComp::Reset()
{

}

