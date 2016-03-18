// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBpFuncLib.generated.h"

class AMyChar;
class USolusDataSingleton;
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

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib", meta = (WorldContext="WorldContextObject"))
		static bool VictoryLoadLevelInstance(
			UObject* WorldContextObject,
			FString mapPath,
			int32 InstanceNumber,
			FVector Location,
			FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestNSLocatext(int32 _dayCount, int32 _hp);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestRefArgs1(UPARAM(Ref) TArray<int32>& _numAry, UPARAM(ref) TArray<int32>& _numAry2);
	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestRefArgs2(UPARAM(Ref) TArray<int32>& _numAry, TArray<int32>& _numAry2);
	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestRefArgs3(TArray<int32>& _numAry2);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestFileWriteCompressed(FString _path);
	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestFileReadCompressed(FString _path);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestFileWriteUnCompressed(FString _path);
	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestFileReadUnCompressed(FString _path);

	UFUNCTION(BlueprintCallable, Category = "Solus Data Singleton")
		static USolusDataSingleton* GetSolusData(bool& IsValid);

	UFUNCTION(BlueprintCallable, Category = "Solus Data Singleton")
		static USolusDataSingleton* GetSolusSingleton(bool& IsValid);

	UFUNCTION(BlueprintCallable, Category = "Async Load")
		static bool TestAsyncLoad(AMyChar* _myChar);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestObjFunc(AMyChar* _myChar,FString _funcName);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestBpDelegate(AMyChar* _myChar, int32 _num);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestDressWeapon(AMyChar* _myChar);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestHasBpImpl(AMyChar* _myChar);

	UFUNCTION(BlueprintCallable, Category = "MyBpFuncLib")
		static void TestBaseDataContain();
};
