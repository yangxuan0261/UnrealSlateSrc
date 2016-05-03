
#include "MySlate.h"
#include "BehavInfo.h"

FEffElemInfo::FEffElemInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FEffElemInfo::FEffElemInfo construct"));
}

FEffElemInfo::~FEffElemInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FEffElemInfo::~FEffElemInfo"));
}

FBehavInfo::FBehavInfo() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::FBehavInfo construct"));
}

FBehavInfo::~FBehavInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBehavInfo::~FBehavInfo"));
}


