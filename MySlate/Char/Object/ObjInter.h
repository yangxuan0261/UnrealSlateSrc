
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

	virtual void Reset() = 0;	//抽象接口，要求子类必须重写
	virtual void SetObj(UObject* _obj); 
	virtual void Recycle();

private:
	UObjMgr*	mObjMgr;	//回收中心
	UObject*	mOwnObj;	//宿主对象
};