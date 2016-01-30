// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyGameMode.h"

#include "StandardHUD.h"

AMyGameMode::AMyGameMode() : Super()
{
	//Set the hud class to use our custom HUD by default.
	this->HUDClass = AStandardHUD::StaticClass();
}