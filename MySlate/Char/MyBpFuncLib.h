// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBpFuncLib.generated.h"

class AMyChar;

/**
 * 
 */
UCLASS(Blueprintable)
class UMyBpFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static bool TestChangeCharAnimInstance(AMyChar* _myChar, FString _pathMesh, FString _pathAnim);

};
