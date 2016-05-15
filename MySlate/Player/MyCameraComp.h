
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

	APlayerController* GetPlayerController();

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
};
