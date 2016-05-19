#pragma once

/*******************************************
***** 特效控制扩展
*******************************************/

#include "BehavInter.generated.h"

class UBehavElem;

UINTERFACE()
class UBehavInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IBehavInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IBehavInterface();
	virtual void BehavTick(float DeltaSeconds);

	//特效
	void AddBehavElem(int32 _groupId, TArray<UBehavElem*> _elemVec);
	void RemoveBehavElem(UBehavElem* _elem);
	void RemoveBehavElemAll(int32 _groupId = 0);

	void SetActor(AActor* _actor) { mOwnerActor = _actor; }
	AActor*	GetActor() const { return mOwnerActor; }

private:
	TMap<int32, TArray<UBehavElem*>>	mBehavMap;
	AActor*		mOwnerActor;
};