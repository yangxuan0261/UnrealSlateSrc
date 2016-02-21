// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyGameInstance.h"

//#include "MoviePlayer.h"

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

//void UMyGameInstance::Init()
//{
//	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::MyBeginLoadingScreen);
//	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UMyGameInstance::MyEndLoadingScreen);
//}
//
//void UMyGameInstance::MyBeginLoadingScreen()
//{
//	FLoadingScreenAttributes LoadingScreen;
//	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
//	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
//
//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
//}
//
//void UMyGameInstance::MyEndLoadingScreen()
//{
//}
