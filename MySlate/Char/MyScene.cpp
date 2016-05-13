
#include "MySlate.h"
#include "MyScene.h"

AMyScene::AMyScene()
{
	PrimaryActorTick.bCanEverTick = true;
	mCameraActor = nullptr;
}

AMyScene::~AMyScene()
{
	UE_LOG(BulletLogger, Warning, TEXT("--- AMyScene::~AMyScene"));
}

void AMyScene::BeginPlay()
{
	Super::BeginPlay();
	
	//mCamera->setlocation
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
