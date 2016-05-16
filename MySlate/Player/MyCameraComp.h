
#pragma once

#include "MyCameraComp.generated.h"

UCLASS()
class UMyCameraComp : public UCameraComponent
{
	GENERATED_BODY()

public:
	UMyCameraComp();
	virtual ~UMyCameraComp();
	virtual void DestroyComponent(bool bPromoteChildren = false) override;

	// Begin UCameraComponent interface
	virtual void GetCameraView(float DeltaTime, FMinimalViewInfo& OutResult) override;

public:
	void SetZoom(float _val);
	void OnZoomIn();
	void OnZoomOut();
	void MoveForward(float _val);
	void MoveRight(float _val);

	bool OnSwipeStarted(const FVector2D& SwipePosition);
	bool OnSwipeUpdate(const FVector2D& SwipePosition);
	bool OnSwipeReleased(const FVector2D& SwipePosition);
	void EndSwipeNow();

	APlayerController* GetPlayerController();
	void SetCameraTarget(const FVector& CameraTarget);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCameraComp")
		FRotator FixedCameraAngle;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCameraComp")
		float MinCameraOffset;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCameraComp")
		float MaxCameraOffset;

	float		mZoom;
	float		mMinZoom;
	float		mMaxZoom;
	FVector		mStartSwipeCoords;
};
