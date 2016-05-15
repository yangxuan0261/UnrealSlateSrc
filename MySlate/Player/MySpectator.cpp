#include "MySlate.h"
#include "MySpectator.h"

#include "./MyCameraComp.h"

AMySpectator::AMySpectator() : Super()
{
	GetCollisionComponent()->SetCollisionProfileName(UCollisionProfile::NoCollision_ProfileName);
	bAddDefaultMovementBindings = false;

	////用摄像机蓝图类
	//static ConstructorHelpers::FClassFinder<UMyCameraComp> CameraCompCls(TEXT("/Game/TopDownCPP/Blueprints/Player/MyCameraCompBp"));
	//mCameraComp = NewObject<UMyCameraComp>(this, CameraCompCls.Class, TEXT("MyCameraComp"));

	mCameraComp = CreateDefaultSubobject<UMyCameraComp>(TEXT("MyCameraComp")); //构造观察者的摄像机
}

AMySpectator::~AMySpectator()
{

}

void AMySpectator::BeginPlay()
{
}

void AMySpectator::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);
	check(InputComponent);

	InputComponent->BindAction("ZoomOut", IE_Pressed, this, &AMySpectator::OnMouseScrollUp);
	InputComponent->BindAction("ZoomIn", IE_Pressed, this, &AMySpectator::OnMouseScrollDown);

	InputComponent->BindAxis("MoveForward", this, &AMySpectator::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMySpectator::MoveRight);
}

void AMySpectator::MoveForward(float Val)
{
	mCameraComp->MoveForward(Val);
}

void AMySpectator::MoveRight(float Val)
{
	mCameraComp->MoveRight(Val);
}

void AMySpectator::OnMouseScrollUp()
{
	mCameraComp->OnZoomIn();
}

void AMySpectator::OnMouseScrollDown()
{
	mCameraComp->OnZoomOut();
}
