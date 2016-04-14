// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameTypes.h"
#include "MyBaseComp.h"
#include "MyCharDataComp.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UMyCharDataComp : public UMyBaseComp
{
	GENERATED_BODY()

public:
	UMyCharDataComp();
	virtual ~UMyCharDataComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //组件被new的时候立即调用
	virtual void BeginDestroy() override; //引擎在gc的时候调用，并不是立即调用
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End UActorComponent Interface.

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		EGroup			mGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		ETeam			mTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealth;
};