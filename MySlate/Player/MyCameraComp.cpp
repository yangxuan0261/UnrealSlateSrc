#include "MySlate.h"
#include "MyCameraComp.h"

UMyCameraComp::UMyCameraComp() : Super()
{
	mZoom = 1.0f;
	mMinZoom = 0.4f;
	mMaxZoom = 1.0f;

	MinCameraOffset = 500.f;
	MaxCameraOffset = 4000.f;
	FixedCameraAngle = FRotator(-45.f, 0.f, 0.f);
	mStartSwipeCoords.Set(0.0f, 0.0f, 0.0f);
}

UMyCameraComp::~UMyCameraComp()
{

}

void UMyCameraComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{
	
	Super::DestroyComponent(bPromoteChildren);
}

void UMyCameraComp::GetCameraView(float DeltaTime, FMinimalViewInfo& OutResult)
{
	APlayerController* Controller = GetPlayerController();
	if (Controller != nullptr)
	{
		OutResult.FOV = 30.f;
		const float CurrentOffset = MinCameraOffset + mZoom * (MaxCameraOffset - MinCameraOffset);
		FVector Pos2 = Controller->GetFocalLocation();
		OutResult.Location = Controller->GetFocalLocation() - FixedCameraAngle.Vector() * CurrentOffset;
		OutResult.Rotation = FixedCameraAngle;
	}
}

void UMyCameraComp::SetZoom(float _val)
{
	mZoom = FMath::Clamp(_val, mMinZoom, mMaxZoom);
}

void UMyCameraComp::OnZoomIn()
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMySpectator::OnMouseScrollUp"));
	SetZoom(mZoom - 0.1f);
}

void UMyCameraComp::OnZoomOut()
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMySpectator::OnMouseScrollDown"));
	SetZoom(mZoom + 0.1f);
}

void UMyCameraComp::MoveForward(float _val)
{
	APawn* OwnerPawn = Cast<APawn>(GetOuter());
	if (OwnerPawn != nullptr)
	{
		APlayerController* Controller = GetPlayerController();
		if ((_val != 0.f) && (Controller != nullptr))
		{
			UE_LOG(GameLogger, Warning, TEXT("--- UMyCameraComp::MoveForward, val:%f"), _val);
			const FRotationMatrix R(Controller->PlayerCameraManager->GetCameraRotation());
			const FVector WorldSpaceAccel = R.GetScaledAxis(EAxis::X) * 100.0f;

			// transform to world space and add it
			OwnerPawn->AddMovementInput(WorldSpaceAccel, _val);
		}
	}
}

void UMyCameraComp::MoveRight(float _val)
{
	APawn* OwnerPawn = Cast<APawn>(GetOuter());
	if (OwnerPawn != nullptr)
	{
		APlayerController* Controller = GetPlayerController();
		if ((_val != 0.f) && (Controller != nullptr))
		{
			UE_LOG(GameLogger, Warning, TEXT("--- UMyCameraComp::MoveRight, val:%f"), _val);
			const FRotationMatrix R(Controller->PlayerCameraManager->GetCameraRotation());
			const FVector WorldSpaceAccel = R.GetScaledAxis(EAxis::Y) * 100.0f;

			// transform to world space and add it
			OwnerPawn->AddMovementInput(WorldSpaceAccel, _val);
		}
	}
}

bool UMyCameraComp::OnSwipeStarted(const FVector2D& SwipePosition)
{
	bool bResult = false;
	APlayerController* Controller = GetPlayerController();
	if (Controller != nullptr)
	{
		// Get intersection point with the plan used to move around
		FHitResult Hit;
		if (Controller->GetHitResultAtScreenPosition(SwipePosition, Collision_Pawn, true, Hit))
		{
			mStartSwipeCoords = Hit.ImpactPoint;
			bResult = true;
		}
	}
	else
	{
		EndSwipeNow();
	}
	return bResult;
}

bool UMyCameraComp::OnSwipeUpdate(const FVector2D& SwipePosition)
{
	bool bResult = false;
	APlayerController* Controller = GetPlayerController();
	if ((Controller != NULL) && (mStartSwipeCoords.IsNearlyZero() == false))
	{
		FHitResult Hit;
		if (Controller->GetHitResultAtScreenPosition(SwipePosition, Collision_Pawn, true, Hit))
		{
			FVector NewSwipeCoords = Hit.ImpactPoint;
			FVector Delta = mStartSwipeCoords - NewSwipeCoords;
			// Flatten Z axis - we are not interested in that.
			Delta.Z = 0.0f;
			if (Delta.IsNearlyZero() == false)
			{
				ASpectatorPawn* SpectatorPawn = GetPlayerController()->GetSpectatorPawn();
				if (SpectatorPawn != NULL)
				{
					FVector CurrentCamera = SpectatorPawn->GetActorLocation();
					CurrentCamera += Delta;
					SetCameraTarget(CurrentCamera);
					bResult = true;
				}
			}
		}
	}
	return bResult;
}

bool UMyCameraComp::OnSwipeReleased(const FVector2D& SwipePosition)
{
	bool bResult = false;
	if (mStartSwipeCoords.IsNearlyZero() == false)
	{
		APlayerController* Controller = GetPlayerController();
		if (Controller)
		{
			FHitResult Hit;
			if (Controller->GetHitResultAtScreenPosition(SwipePosition, Collision_Pawn, true, Hit))
			{
				FVector EndSwipeCoords = Hit.ImpactPoint;
				bResult = true;
			}
		}
		EndSwipeNow();
	}

	return false;
}

void UMyCameraComp::EndSwipeNow()
{
	mStartSwipeCoords.Set(0.0f, 0.0f, 0.0f);
}

APlayerController* UMyCameraComp::GetPlayerController()
{
	APawn* Owner = Cast<APawn>(GetOuter()); //new这个对象时是以Spectator为outer
	APlayerController* Controller = Owner !=nullptr?Cast<APlayerController>(Owner->GetController()) : nullptr;
	return Controller;
}

void UMyCameraComp::SetCameraTarget(const FVector& CameraTarget)
{
	ASpectatorPawn* SpectatorPawn = GetPlayerController()->GetSpectatorPawn();
	if (SpectatorPawn != NULL)
	{
		SpectatorPawn->SetActorLocation(CameraTarget, false);
	}
}
