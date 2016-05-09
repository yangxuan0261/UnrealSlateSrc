
#pragma once

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
		virtual void BehavTick(float DeltaSeconds);

		//ÌØÐ§
		void AddBehavElem(int32 _groupId, TArray<UBehavElem*> _elemVec);
		void RemoveBehavElem(UBehavElem* _elem);
		void RemoveBehavElemAll(int32 _groupId = 0);
public:
	TMap<int32, TArray<UBehavElem*>>	mBehavMap;
};