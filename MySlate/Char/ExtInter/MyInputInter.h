#pragma once

/*******************************************
***** 输入控制器扩展
*******************************************/
#include <vector>
#include "MyInputInter.generated.h"

class AMyChar;

enum class FOpType : uint8
{
	None = 0,
	Move,
	Attack,
};

struct FOperator
{
	FOperator() {}
	FOperator(FOpType _type, AMyChar* _target, FVector& _loc) 
	{
		mType = _type;
		mTarget = _target;
		mLoc = _loc;
	}
	FOpType		mType;
	AMyChar*	mTarget;
	FVector		mLoc;
};

UINTERFACE()
class UMyInputInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IMyInputInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IMyInputInterface();
	void		SetChar(AMyChar* _target);
	void		SetParticleVisible(bool _b);
	void		MoveToDst(AMyChar* _target, const FVector& _loc, bool _isShift = false);
	void		AttackTarget(AMyChar* _target, int32 _skillId = 0, bool _isShift = false);
	void		OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult);

protected:
	AMyChar*	mOwnChar;	//宿主对象
	AAIController* mAICtrl; 
	TArray<FOperator>	mOperatorVec; 
};