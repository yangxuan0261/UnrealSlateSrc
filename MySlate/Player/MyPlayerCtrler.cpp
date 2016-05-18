#include "MySlate.h"
#include "MyPlayerCtrler.h"

#include "./MyInput.h"
#include "./MyCameraComp.h"
#include "./MySpectator.h"
#include "../Char/MyChar.h"

AMyPlayerCtrler::AMyPlayerCtrler() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	InputHandler = nullptr;
	mMyCameraComp = nullptr;
	mMySpectator = nullptr;
}

AMyPlayerCtrler::~AMyPlayerCtrler()
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::~AMyPlayerCtrler"));
}

void AMyPlayerCtrler::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	if (bMoveToMouseCursor)
	{
		MoveToMouseCursor();
	}
}

void AMyPlayerCtrler::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputHandler = NewObject<UMyInput>(this, UMyInput::StaticClass()); //跟随this释放

	BIND_1P_ACTION(InputHandler, EGameKey::Tap, IE_Pressed, &AMyPlayerCtrler::OnTapPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Pressed, &AMyPlayerCtrler::OnHoldPressed);
	BIND_1P_ACTION(InputHandler, EGameKey::Hold, IE_Released, &AMyPlayerCtrler::OnHoldReleased);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Pressed, &AMyPlayerCtrler::OnSwipeStarted);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Repeat, &AMyPlayerCtrler::OnSwipeUpdate);
	BIND_1P_ACTION(InputHandler, EGameKey::Swipe, IE_Released, &AMyPlayerCtrler::OnSwipeReleased);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Pressed, &AMyPlayerCtrler::OnSwipeTwoPointsStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::SwipeTwoPoints, IE_Repeat, &AMyPlayerCtrler::OnSwipeTwoPointsUpdate);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Pressed, &AMyPlayerCtrler::OnPinchStarted);
	BIND_2P_ACTION(InputHandler, EGameKey::Pinch, IE_Repeat, &AMyPlayerCtrler::OnPinchUpdate);


	InputComponent->BindAction("MouseClick", IE_Pressed, this, &AMyPlayerCtrler::OnSetDestinationPressed);
	InputComponent->BindAction("MouseClick", IE_Released, this, &AMyPlayerCtrler::OnSetDestinationReleased);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerCtrler::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyPlayerCtrler::MoveToTouchLocation);
}

void AMyPlayerCtrler::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	if (!bGamePaused && PlayerInput && InputHandler)
	{
		InputHandler->UpdateDetection(DeltaTime);
	}

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);
}

void AMyPlayerCtrler::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetClickTarget(ScreenPosition, WorldPosition);

	AMyChar* tarChar = Cast<AMyChar>(HitActor);
	AMySpectator* spectator = Cast<AMySpectator>(GetSpectatorPawn());
	if (spectator != nullptr)
	{
		UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnTapPressed, target id:%d"), tarChar->GetUuid());
	}

	//if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass())) //检查是否有实现结构
	//{
	//	IStrategyInputInterface::Execute_OnInputTap(HitActor);
	//}

}
	
void AMyPlayerCtrler::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{

}

void AMyPlayerCtrler::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{

}

void AMyPlayerCtrler::OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnSwipeStarted, DownTime:%f"), DownTime);
	if (GetMyCameraComp() != nullptr)
	{
		GetMyCameraComp()->OnSwipeStarted(AnchorPosition);
	}
}

void AMyPlayerCtrler::OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnSwipeUpdate, DownTime:%f"), DownTime);
	if (GetMyCameraComp() != nullptr)
	{
		GetMyCameraComp()->OnSwipeUpdate(ScreenPosition);
	}
}

void AMyPlayerCtrler::OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnSwipeReleased, DownTime:%f"), DownTime);
	if (GetMyCameraComp() != nullptr)
	{
		GetMyCameraComp()->OnSwipeReleased(ScreenPosition);
	}
}

void AMyPlayerCtrler::OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{

}

void AMyPlayerCtrler::OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{

}

void AMyPlayerCtrler::OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime)
{

}

void AMyPlayerCtrler::OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime)
{

}

void AMyPlayerCtrler::MoveToMouseCursor()
{
	// Trace to see what is under the mouse cursor
	FHitResult Hit;
	GetHitResultUnderCursor(ECC_Visibility, false, Hit);

	if (Hit.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(Hit.ImpactPoint);
	}
}

void AMyPlayerCtrler::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
{
	FVector2D ScreenSpaceLocation(Location);

	// Trace to see what is under the touch location
	FHitResult HitResult;
	GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		// We hit something, move there
		SetNewMoveDestination(HitResult.ImpactPoint);
	}
}

void AMyPlayerCtrler::SetNewMoveDestination(const FVector DestLocation)
{
	APawn* const Pawn = GetPawn();
	if (Pawn)
	{
		UNavigationSystem* const NavSys = GetWorld()->GetNavigationSystem();
		float const Distance = FVector::Dist(DestLocation, Pawn->GetActorLocation());

		// We need to issue move command only if far enough in order for walk animation to play correctly
		if (NavSys && (Distance > 120.0f))
		{
			NavSys->SimpleMoveToLocation(this, DestLocation);
		}
	}
}

void AMyPlayerCtrler::OnSetDestinationPressed()
{
	// set flag to keep updating destination until released
	bMoveToMouseCursor = true;
}

void AMyPlayerCtrler::OnSetDestinationReleased()
{
	// clear flag to indicate we should stop updating the destination
	bMoveToMouseCursor = false;
}

AActor* AMyPlayerCtrler::GetClickTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
	//根据屏幕2d点ScreenPoint，和检查标记Collision_Pawn，检测是否点击中world中的某个符合条件的actor
	FHitResult Hit;
	if (GetHitResultAtScreenPosition(ScreenPoint, Collision_Pawn, true, Hit)) 
	{
		//if (!AStrategyGameMode::OnEnemyTeam(Hit.GetActor(), this))
		//{
			WorldPoint = Hit.ImpactPoint;
			return Hit.GetActor();
		//}
	}
	return nullptr;
}

AMySpectator* AMyPlayerCtrler::GetMySpectator()
{
	if (mMySpectator == nullptr)
	{
		mMySpectator = Cast<AMySpectator>(GetSpectatorPawn());
	}
	return mMySpectator;
}

UMyCameraComp* AMyPlayerCtrler::GetMyCameraComp()
{
	if (mMyCameraComp == nullptr)
	{
		if (GetMySpectator() != nullptr)
		{
			mMyCameraComp = GetMySpectator()->GetMyCameraComp();
		}
	}
	return mMyCameraComp;
}
