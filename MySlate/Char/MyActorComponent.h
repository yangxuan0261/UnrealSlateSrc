// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"
#include "MyActorComponent.generated.h"

UCLASS( ClassGroup="MyCustom", meta=(BlueprintSpawnableComponent) )
class MYSLATE_API UMyActorComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UMyActorComponent();
	virtual ~UMyActorComponent();

	// Called when the game starts
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction ) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorName")
		FString Name;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ActorAge")
		int32 Age;
};
