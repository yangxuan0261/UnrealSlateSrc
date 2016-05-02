
#include "MySlate.h"
#include "EffectMgr.h"

UEffectMgr::UEffectMgr() : Super()
{

}

UEffectMgr::~UEffectMgr()
{
	UE_LOG(ResLogger, Warning, TEXT("--- UEffectMgr::~UEffectMgr"));
}

void UEffectMgr::BeginDestroy()
{

	UE_LOG(ResLogger, Warning, TEXT("--- UEffectMgr::BeginDestroy"));
	Super::BeginDestroy();
}