
#include "MySlate.h"
#include "BehavInfo.h"

FBehavInfo::FBehavInfo() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::FBehavInfo construct"));
}

FBehavInfo::~FBehavInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::~FBehavInfo"));
}

