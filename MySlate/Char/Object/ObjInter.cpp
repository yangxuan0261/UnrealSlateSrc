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
	UE_LOG(ObjLogger, Warning, TEXT("--- IObjInterface::IObjInterface"));
}

void IObjInterface::SetObj(UObject* _obj)
{
	UE_LOG(ObjLogger, Warning, TEXT("--- IObjInterface::SetObj, construct - %s"), *_obj->GetClass()->GetName());
	mObjMgr = UObjMgr::GetInstance();
	mOwnObj = _obj;
	Reset();
}
void IObjInterface::Recycle()
{
	UE_LOG(ObjLogger, Warning, TEXT("--- IObjInterface::Recycle - %s"), *mOwnObj->GetClass()->GetName());
	Reset();
	mObjMgr->Recycle(mOwnObj);
}
