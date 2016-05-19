#pragma once

#include "MyPlayerCtrler.generated.h"

class UMyInput;
class UMyCameraComp;
class AMySpectator;
class AMyChar;

UCLASS()
class AMyPlayerCtrler : public APlayerController
{
	GENERATED_BODY()

public:
	AMyPlayerCtrler();
	virtual ~AMyPlayerCtrler();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;
	// End PlayerController interface

	/** Input handlers. */
	void OnTapPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldPressed(const FVector2D& ScreenPosition, float DownTime);
	void OnHoldReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeStarted(const FVector2D& AnchorPosition, float DownTime);
	void OnSwipeUpdate(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeReleased(const FVector2D& ScreenPosition, float DownTime);
	void OnSwipeTwoPointsStarted(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnSwipeTwoPointsUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);
	void OnPinchStarted(const FVector2D& AnchorPosition1, const FVector2D& AnchorPosition2, float DownTime);
	void OnPinchUpdate(const FVector2D& ScreenPosition1, const FVector2D& ScreenPosition2, float DownTime);

	void MoveToMouseCursor();
	void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	void SetNewMoveDestination(const FVector DestLocation);

	void OnLeftMousePressed();
	void OnRightMousePressed();

	void OnReadAtk();
	void MoveDestination(const FVector& DestLocation);
	void AtkTarget(AMyChar* _target);

	AActor*				GetClickTarget(const FVector2D& ScreenPoint, FVector& WorldPoint) const;
	AMySpectator*		GetMySpectator();
	UMyCameraComp*		GetMyCameraComp();
	void				SetSelected(TArray<AMyChar*>& _selectedVec);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyPlayerCtrler")
		UMyInput* InputHandler;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyPlayerCtrler")
		UMyCameraComp*	mMyCameraComp;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMyPlayerCtrler")
		AMySpectator*	mMySpectator;

private:
	TArray<AMyChar*>	mSelectedVec;
	bool				mIsReadyAtk;
};


