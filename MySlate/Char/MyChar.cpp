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
#include "Skill/SkillFunction.h"
#include "MyCharDataComp.h"

DECLARE_LOG_CATEGORY_EXTERN(AMyCharLogger, Log, All);
DEFINE_LOG_CATEGORY(AMyCharLogger)

// Sets default values
AMyChar::AMyChar() : Super()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//--------- 
	mCDComp = nullptr;
	mDataComp = nullptr;
	mUsingSkill = nullptr;
	mCharState = CharState::IdleRun;
	mUuid = 0;

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

	if (mUsingSkill != nullptr)
	{
		mUsingSkill->Tick(DeltaTime);
	}
}

// Called when the game starts or when spawned
void AMyChar::BeginPlay()
{
	Super::BeginPlay();

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

void AMyChar::OnCDFinish(UCoolDown* _cd)
{
	UE_LOG(AMyCharLogger, Warning, TEXT("--- AMyChar::OnCDFinish, skillId:%d"), _cd->GetSkillId());
	mCanUseSkillArr.AddUnique(_cd);
}

bool AMyChar::IsAlive()
{
	return mDataComp->mHealth > 0.f ? true : false;
}

void AMyChar::Death()
{


	OnDeath(); //通知一下蓝图
}

void AMyChar::Reset()
{

}
