
#include "MySlate.h"
#include "MyScene.h"

#include "../Player/MySpectator.h"

AMyScene::AMyScene()
{
	PrimaryActorTick.bCanEverTick = true;
	mSpectator = nullptr;
}

AMyScene::~AMyScene()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyScene::~AMyScene"));
}

void AMyScene::BeginPlay()
{
	Super::BeginPlay();
	AMyScene::SetInstance(this);

	//将场景摄像机绑定到这个actor
	BindSpectator();
}

void AMyScene::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	IBehavInterface::BehavTick(DeltaSeconds);
}

void AMyScene::Destroyed()
{
	
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyScene::Destroyed"));
	Super::Destroyed();
}

void AMyScene::BindSpectator()
{
	APlayerController* ctrler = GetWorld()->GetFirstPlayerController();
	if (ctrler != nullptr)
	{
		mSpectator = Cast<AMySpectator>(ctrler->GetSpectatorPawn());
	}
}
