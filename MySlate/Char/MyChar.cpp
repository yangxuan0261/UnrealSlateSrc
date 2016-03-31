// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyChar.h"

#include "MyGameInstance.h"
#include "Engine.h"
#include "Level/MyLevelScriptActor.h"
#include "AI/MyAIController.h"
#include "BlueprintNodeHelpers.h"
#include "Skill/CoolDown/CoolDownComp.h"
#include "Skill/CoolDown/CoolDown.h"
#include "MyCharDataComp.h"

DECLARE_LOG_CATEGORY_EXTERN(AMyCharLogger, Log, All);
DEFINE_LOG_CATEGORY(AMyCharLogger)

// Sets default values
AMyChar::AMyChar() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Weapon1 = nullptr;
	mMon1 = nullptr;

	//检测是否有蓝图实现
	UClass* selfClass = AMyChar::StaticClass();
	hasOnDeathImplementEvent = BlueprintNodeHelpers::HasBlueprintFunction(TEXT("OnDeath"), this, selfClass);

	//--------- 
	mCDComp = nullptr;
	mDataComp = nullptr;
	mUsingSkill = -1;

	//设置ai控制类
	AIControllerClass = AMyAIController::StaticClass();
}

AMyChar::~AMyChar()
{

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
		//GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, str);
	}

	/*if (mMon1) //PlayAnimMontage(mMon1)只能执行一次
	{
		float time = PlayAnimMontage(mMon1);
		FString str = FString::Printf(TEXT("--- PlayAnimMontage - %f"), time);
		GEngine->AddOnScreenDebugMessage(0, 1.0f, FColor::Green, str);
	}*/
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

	//生成ai控制类
	SpawnDefaultController();

	//注册cd组件
	mCDComp = NewObject<UCoolDownComp>(this, TEXT("CDComponent"));
	mCDComp->RegisterComponent();
	mCDComp->SetOwner(this);

	//注册data组件
	mDataComp = NewObject<UMyCharDataComp>(this, TEXT("CharDataComponent"));
	mDataComp->RegisterComponent();
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

void AMyChar::TestFunction(int32 _num, FString _str)
{
	FString str = FString::Printf(TEXT("--- AMyChar::TestFunction - num:%d, str:%s"), _num, *_str);
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
} 

void AMyChar::SetWeapon1Class(TSubclassOf<USMyAttachment> InWeapon)
{
	Weapon1Class = InWeapon;
}

//--------------------- split

void AMyChar::OnCDFinish(UCoolDown* _cd)
{
	UE_LOG(AMyCharLogger, Warning, TEXT("--- AMyChar::OnCDFinish, skillId:%d"), _cd->GetSkillId());

}