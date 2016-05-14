
#pragma once

#include "MyInput.generated.h"

DECLARE_DELEGATE_TwoParams(FOnePointActionSignature, const FVector2D&, float);
DECLARE_DELEGATE_ThreeParams(FTwoPointsActionSignature, const FVector2D&, const FVector2D&, float);

#define BIND_1P_ACTION(Handler, ActionKey, ActionEvent, Delegate)	\
{ \
	int32 Idx = Handler->ActionBindings1P.AddZeroed(); \
	Handler->ActionBindings1P[Idx].Key = ActionKey; \
	Handler->ActionBindings1P[Idx].KeyEvent = ActionEvent; \
	Handler->ActionBindings1P[Idx].ActionDelegate.BindUObject(this, Delegate); \
}

#define BIND_2P_ACTION(Handler, ActionKey, ActionEvent, Delegate)	\
{ \
	int32 Idx = Handler->ActionBindings2P.AddZeroed(); \
	Handler->ActionBindings2P[Idx].Key = ActionKey; \
	Handler->ActionBindings2P[Idx].KeyEvent = ActionEvent; \
	Handler->ActionBindings2P[Idx].ActionDelegate.BindUObject(this, Delegate); \
}

UENUM()
enum class EGameKey : uint8
{
	None = 0,
	Tap,
	Hold,
	Swipe,
	SwipeTwoPoints,
	Pinch,
};

struct FActionBinding1P
{
	/** key to bind it to */
	EGameKey Key;

	/** Key event to bind it to, e.g. pressed, released, dblclick */
	TEnumAsByte<EInputEvent> KeyEvent;

	/** action */
	FOnePointActionSignature ActionDelegate;
};

struct FActionBinding2P
{
	/** key to bind it to */
	EGameKey Key;

	/** Key event to bind it to, e.g. pressed, released, dblclick */
	TEnumAsByte<EInputEvent> KeyEvent;

	/** action */
	FTwoPointsActionSignature ActionDelegate;
};

struct FSimpleKeyState
{
	/** current events indexed with: IE_Pressed, IE_Released, IE_Repeat */
	uint8 Events[3];

	/** is it pressed? (unused in tap & hold) */
	uint8 bDown : 1;

	/** position associated with event */
	FVector2D Position;

	/** position associated with event */
	FVector2D Position2;

	/** accumulated down time */
	float DownTime;

	FSimpleKeyState()
	{
		FMemory::Memzero(this, sizeof(FSimpleKeyState));
	}
};

UCLASS()
class UMyInput : public UObject
{
	GENERATED_BODY()

public:
	UMyInput();
	virtual ~UMyInput();

	/** bindings for custom game events */
	TArray<FActionBinding1P> ActionBindings1P;
	TArray<FActionBinding2P> ActionBindings2P;

	/** update detection */
	void UpdateDetection(float DeltaTime);

	/** get touch anchor position */
	FVector2D GetTouchAnchor(int32 i) const;

protected:

	/** game key states */
	TMap<EGameKey, FSimpleKeyState> KeyStateMap;

	/** touch anchors */
	FVector2D TouchAnchors[2];

	/** how long was touch 0 pressed? */
	float Touch0DownTime;

	/** how long was two points pressed? */
	float TwoPointsDownTime;

	/** max distance delta for current pinch */
	float MaxPinchDistanceSq;

	/** prev touch states for recognition */
	uint32 PrevTouchState;

	/** is two points touch active? */
	bool bTwoPointsTouch;

	/** update game key recognition */
	void UpdateGameKeys(float DeltaTime);

	/** process input state and call handlers */
	void ProcessKeyStates(float DeltaTime);

	/** detect one point actions (touch and mouse) */
	void DetectOnePointActions(bool bCurrentState, bool bPrevState, float DeltaTime, const FVector2D& CurrentPosition, FVector2D& AnchorPosition, float& DownTime);

	/** detect two points actions (touch only) */
	void DetectTwoPointsActions(bool bCurrentState, bool bPrevState, float DeltaTime, const FVector2D& CurrentPosition1, const FVector2D& CurrentPosition2);
};
