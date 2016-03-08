// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyChar.h"

#include "MyGameInstance.h"
#include "Engine.h"
#include "Level/MyLevelScriptActor.h"

// Sets default values
AMyChar::AMyChar() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mHealth = 987;
}



// Called every frame
void AMyChar::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	UMyGameInstance* mgi = Cast<UMyGameInstance>(GetGameInstance());
	if (mgi)
	{
		mgi->InterLevelPersistentValue++;
		//FString str = FString::Printf(TEXT("--- Cast myGameInstance Success - %d"), mgi->InterLevelPersistentValue);
		/*GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);*/
	}

	AMyLevelScriptActor* msa = Cast<AMyLevelScriptActor>(GetWorld()->GetLevelScriptActor());
	if (msa)
	{
		FString str = FString::Printf(TEXT("--- Cast AMyLevelScriptActor Success - %d"), msa->Counter);
		//GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	}

}

// Called to bind functionality to input
void AMyChar::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

class Test : public TSharedFromThis<Test>
{
public:
	void output(int32 _num)
	{
		FString str = FString::Printf(TEXT("--- Test  output - %d"), _num);
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, str);
	}
};

static void gOutput(int32 _num)
{
	FString str = FString::Printf(TEXT("--- gOutput - %d"), _num);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Black, str);
}

// Called when the game starts or when spawned
void AMyChar::BeginPlay()
{
	Super::BeginPlay();

	auto lambdaFunc = [&](int32 _num)->void {
		FString str = FString::Printf(TEXT("--- lambdaFunc - %d"), _num);
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
	};

	testSp = TSharedPtr<Test>(new Test); //new一个共享指针

	mMyDelegate1.BindUObject(this, &AMyChar::testDelegateUObject); //只能绑定继承自UObject的类
	mMyDelegate2.BindSP(testSp.Get(), &Test::output);//绑定继承自模板TSharedFromThis<xxx>的类
	mMyDelegate3.BindStatic(&gOutput);//绑定静态方法
	mMyDelegate4.BindLambda(lambdaFunc);//绑定lambda表达式
	mMyDelegate5.BindUFunction(this, "testDelegateUFunctionBp");//绑定蓝图中的方法
}


void AMyChar::testDelegateUObject(int32 _num)
{
	FString str = FString::Printf(TEXT("--- testDelegateUObject - %d"), _num);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str);
}

void AMyChar::runAllDelegate()
{
	mMyDelegate1.Execute(111);
	bool b2 = mMyDelegate2.ExecuteIfBound(222);
	bool b3 = mMyDelegate3.ExecuteIfBound(333);
	bool b4 = mMyDelegate4.ExecuteIfBound(444);
	bool b5 = mMyDelegate5.ExecuteIfBound(555);
}

void AMyChar::runBpFunc(FString _funcName, FString _arg1, int32 _arg2)
{
	FOutputDeviceNull ar;
	FString command = FString::Printf(TEXT("%s \"%s\" %d"), *_funcName, *_arg1, _arg2);
	CallFunctionByNameWithArguments(*command, ar, nullptr, true);
}

void AMyChar::TestAsyncLoad()
{
	FString str = FString::Printf(TEXT("--- AMyChar::TestAsyncLoad callback"));
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Red, str);
}

void AMyChar::TestFunction(int32 _num)
{
	FString str = FString::Printf(TEXT("--- AMyChar::TestFunction - %d"), _num);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
}


