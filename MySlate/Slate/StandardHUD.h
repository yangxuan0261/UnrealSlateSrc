// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/HUD.h"
#include "StandardHUD.generated.h"

class SStandardSlateWidget;

UCLASS()
class AStandardHUD : public AHUD
{
	GENERATED_BODY()
public:
	AStandardHUD();

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Reference to an SCompoundWidget, TSharedPtr adds to the refcount of MyUIWidget
	/////MyUIWidget will not self-destruct as long as refcount > 0
	/////MyUIWidget refcount will be (refcout-1) if HUD is destroyed.
	TSharedPtr<SStandardSlateWidget> MyUIWidget;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Called as soon as game starts, create SCompoundWidget and give Viewport access
	virtual void BeginPlay() override;

	FReply OnConfirmClicked();

};