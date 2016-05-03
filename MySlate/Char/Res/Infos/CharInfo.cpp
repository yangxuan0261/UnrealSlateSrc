
#include "MySlate.h"
#include "CharInfo.h"

FFightDataInfo::FFightDataInfo()
{

}

FFightDataInfo::~FFightDataInfo()
{

}

FCharInfo::FCharInfo() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FCharInfo::FCharInfo construct"));
}

FCharInfo::~FCharInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FCharInfo::~FCharInfo"));
}


