#include "MySlate.h"
#include "ObjInter.h"

#include "./ObjMgr.h"

UObjInterface::UObjInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	UE_LOG(ObjLogger, Warning, TEXT("--- UObjInterface::UObjInterface 111111"));
}


IObjInterface::IObjInterface() 
 : mOwnObj(nullptr)
{
	UE_LOG(ObjLogger, Warning, TEXT("--- IObjInterface::IObjInterface 222222"));
	mObjMgr = UObjMgr::GetInstance();
}

void IObjInterface::Recycle()
{
	Reset();
	mObjMgr->Recycle(mOwnObj);
}
