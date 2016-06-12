#include "MySlate.h"
#include "MyPlayerCtrler.h"

#include "./MyInput.h"
#include "./MyCameraComp.h"
#include "./MySpectator.h"
#include "../Char/MyChar.h"
#include "../Char/ExtInter/MyInputInter.h"

AMyPlayerCtrler::AMyPlayerCtrler() : Super()
{
	PrimaryActorTick.bCanEverTick = true;
	bHidden = false;
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
	InputHandler = nullptr;
	mMyCameraComp = nullptr;
	mMySpectator = nullptr;
	mIsReadyAtk = false;
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

	InputComponent->BindAction("LeftMouse", IE_Pressed, this, &AMyPlayerCtrler::OnLeftMousePressed);
	InputComponent->BindAction("RightMouse", IE_Pressed, this, &AMyPlayerCtrler::OnRightMousePressed);

	//按A键，准备攻击
	InputComponent->BindAction("ReadyAtk", IE_Pressed, this, &AMyPlayerCtrler::OnReadAtk);

	// support touch devices 
	InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AMyPlayerCtrler::MoveToTouchLocation);
	InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AMyPlayerCtrler::MoveToTouchLocation);
}

void AMyPlayerCtrler::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (!bGamePaused && PlayerInput && InputHandler)
	{
		//InputHandler->UpdateDetection(DeltaTime);
	}
}

void AMyPlayerCtrler::OnTapPressed(const FVector2D& ScreenPosition, float DownTime)
{
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetClickTarget(ScreenPosition, WorldPosition);

	AMyChar* tarChar = Cast<AMyChar>(HitActor);
	//AMySpectator* spectator = Cast<AMySpectator>(GetSpectatorPawn());
	TArray<AMyChar*> dstCharVec;
	if (tarChar != nullptr)
	{
		dstCharVec.Add(tarChar);
		UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnTapPressed, target id:%d"), tarChar->GetUuid());
	}
	SetSelected(dstCharVec);
	//if (HitActor && HitActor->GetClass()->ImplementsInterface(UStrategyInputInterface::StaticClass())) //检查是否有实现结构
	//{
	//	IStrategyInputInterface::Execute_OnInputTap(HitActor);
	//}

}
	
void AMyPlayerCtrler::OnHoldPressed(const FVector2D& ScreenPosition, float DownTime)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnHoldPressed, pos:%s"), *ScreenPosition.ToString());
}

void AMyPlayerCtrler::OnHoldReleased(const FVector2D& ScreenPosition, float DownTime)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnHoldReleased, pos:%s"), *ScreenPosition.ToString());
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

void AMyPlayerCtrler::OnLeftMousePressed()
{
	FVector2D pressPos;
	this->GetMousePosition(pressPos.X, pressPos.Y);
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnLeftMousePressed, pos:%s"), *pressPos.ToString());

	bool isAtk = false;
	FVector WorldPosition(0.f);
	AActor* const HitActor = GetClickTarget(pressPos, WorldPosition);
	AMyChar* tarChar = Cast<AMyChar>(HitActor);
	if (mSelectedVec.Num() > 0)
	{
		if (mIsReadyAtk)
		{
			//如果有人就锁定目标， 没人就移动

			if (tarChar != nullptr)
			{
				AtkTarget(tarChar);
			}
			else
			{
				MoveDestination(WorldPosition);
			}

			isAtk = true;
			mIsReadyAtk = false;
		}
	}

	if (!isAtk)
	{
		TArray<AMyChar*> dstCharVec;
		if (tarChar != nullptr)
		{
			dstCharVec.Add(tarChar);
		}
		SetSelected(dstCharVec);
	}


}

void AMyPlayerCtrler::OnRightMousePressed()
{
	FVector2D pressPos;
	this->GetMousePosition(pressPos.X, pressPos.Y);
	UE_LOG(GameLogger, Warning, TEXT("--- AMyPlayerCtrler::OnLeftMousePressed, pos:%s"), *pressPos.ToString());

	FHitResult HitResult;
	this->GetHitResultAtScreenPosition(pressPos, CurrentClickTraceChannel, true, HitResult);
	if (HitResult.bBlockingHit)
	{
		MoveDestination(HitResult.ImpactPoint);
	}
}

void AMyPlayerCtrler::OnReadAtk()
{
	mIsReadyAtk = true;
}

void AMyPlayerCtrler::MoveDestination(const FVector& DestLocation)
{
	for (AMyChar* selChar : mSelectedVec)
	{
		IMyInputInterface::Execute_MoveToDst(selChar, DestLocation);
	}
}

void AMyPlayerCtrler::AtkTarget(AMyChar* _target)
{
	for (AMyChar* selChar : mSelectedVec)
	{
		if (selChar != _target) //不能攻击自己，其余交给接口判断
		{
			IMyInputInterface::Execute_AttackTarget(selChar, _target, 0);
		}
	}
}

AActor* AMyPlayerCtrler::GetClickTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const
{
	//根据屏幕2d点ScreenPoint，和检查标记Collision_Pawn，检测是否点击中world中的某个符合条件的actor
	FHitResult Hit;
	if (this->GetHitResultAtScreenPosition(ScreenPoint, Collision_Pawn, true, Hit))
	{
		WorldPoint = Hit.ImpactPoint;
		return Hit.GetActor();
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

void AMyPlayerCtrler::SetSelected(TArray<AMyChar*>& _selectedVec)
{
	for (AMyChar* preChar : mSelectedVec)
	{
		IMyInputInterface::Execute_SetParticleVisible(preChar, false);
	}
	mSelectedVec.Empty();

	for (AMyChar* selChar : _selectedVec)
	{
		IMyInputInterface::Execute_SetParticleVisible(selChar, true);
		mSelectedVec.Add(selChar);
	}
}

