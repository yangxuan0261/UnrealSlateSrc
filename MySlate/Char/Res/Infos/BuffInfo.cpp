
#include "MySlate.h"
#include "BuffInfo.h"

FBuffInfo::FBuffInfo() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBuffInfo::FBuffInfo construct"));
}

FBuffInfo::~FBuffInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBuffInfo::~FBuffInfo"));
}

