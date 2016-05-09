
#pragma once

#include "ObjInter.generated.h"

class UObjMgr;

UINTERFACE()
class UObjInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class IObjInterface
{
	GENERATED_IINTERFACE_BODY()
public:
	IObjInterface();

	virtual void Reset() = 0;
	virtual void SetObj(UObject* _obj) { mOwnObj = _obj; }
	virtual void Recycle();

private:
	UObjMgr*	mObjMgr;
	UObject*	mOwnObj;
};