// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
//#include "TestChar.h"
#include "MyChar.generated.h"

DECLARE_DELEGATE_OneParam(FMyDelegate1, int32);

class Test;

UCLASS()
class AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMyChar();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//---------- 测试delegate的各种bind
	void testDelegateUObject(int32 _num);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
	void runAllDelegate();

	TSharedPtr<Test> testSp;

	FMyDelegate1 mMyDelegate1;
	FMyDelegate1 mMyDelegate2;
	FMyDelegate1 mMyDelegate3;
	FMyDelegate1 mMyDelegate4;
	FMyDelegate1 mMyDelegate5;

	//---------- 测试调用指定蓝图方法，并传参数 
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void runBpFunc(FString _funcName, FString _arg1, int32 _arg2);

	//---------- 测试async load
	void TestAsyncLoad();

	//---------- 测试ufunction
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void TestFunction(int32 _num, FString _str);

public:
	int32		mHealth;
};
