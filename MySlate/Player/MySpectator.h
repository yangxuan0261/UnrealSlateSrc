
#pragma once

#include "MySpectator.generated.h"

class UMyCameraComp;

UCLASS()
class AMySpectator : public ASpectatorPawn
{
	GENERATED_BODY()

public:
	AMySpectator();
	virtual ~AMySpectator();

	// Begin ADefaultPawn interface
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	virtual void MoveForward(float Val) override;
	virtual void MoveRight(float Val) override;
	// End ADefaultPawn interface

public:
	void OnMouseScrollUp();
	void OnMouseScrollDown();
	UMyCameraComp*		GetMyCameraComp() const { return mCameraComp; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AMySpectator")
		UMyCameraComp* mCameraComp;

private:
	
};
