
#include "MySlate.h"
#include "ResDataBase.h"

UResDataBase::UResDataBase() : Super()
{

}

UResDataBase::~UResDataBase()
{
	UE_LOG(ResLogger, Warning, TEXT("--- UResDataBase::~UResDataBase"));
}

void UResDataBase::BeginDestroy()
{

	UE_LOG(ResLogger, Warning, TEXT("--- UResDataBase::BeginDestroy"));
	Super::BeginDestroy();
}

