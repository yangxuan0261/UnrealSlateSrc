// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "StandardHUD.h"

#include "StandardSlateWidget.h"
#include "Engine.h"

AStandardHUD::AStandardHUD()
{

}

void AStandardHUD::BeginPlay()
{
	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////So far only TSharedPtr<SMyUIWidget> has been created, now create the actual object.
	/////Create a SMyUIWidget on heap, our MyUIWidget shared pointer provides handle to object
	/////Widget will not self-destruct unless the HUD's SharedPtr (and all other SharedPtrs) destruct first.

	MyUIWidget = SNew(SStandardSlateWidget)
		.OwnerHUD(this)
		.OnConfirmClicked(FOnClicked::CreateUObject(this, &AStandardHUD::OnConfirmClicked));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Pass our viewport a weak ptr to our widget
	/////Viewport's weak ptr will not give Viewport ownership of Widget
	GEngine->GameViewport->AddViewportWidgetContent(SNew(SWeakWidget).PossiblyNullContent(MyUIWidget.ToSharedRef()));

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/////Set widget's properties as visible (sets child widget's properties recursively)
	MyUIWidget->SetVisibility(EVisibility::Visible);
}

FReply AStandardHUD::OnConfirmClicked()
{
	FString str = FString::Printf(TEXT("--- AStandardHUD::OnConfirmClicked hello world - %d"), 789);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	FReply Result = FReply::Unhandled();
	return Result;
}
