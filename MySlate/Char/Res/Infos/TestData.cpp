
#include "MySlate.h"
#include "TestData.h"

FTestData::FTestData() 
{
	UE_LOG(ResLogger, Warning, TEXT("--- FTestData::FTestData construct"));
}

FTestData::~FTestData()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FTestData::~FTestData"));
}

