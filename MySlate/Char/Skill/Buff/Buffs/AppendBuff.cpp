
#include "MySlate.h"
#include "AppendBuff.h"

#include "AbsBuff.h"

UAppendBuff::UAppendBuff() : Super()
{
	IObjInterface::SetObj(this);
}

UAppendBuff::~UAppendBuff()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UAppendBuff::~UAppendBuff"));
}

void UAppendBuff::BeginDestroy()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UAppendBuff::BeginDestroy"));
	Super::BeginDestroy();
}

void UAppendBuff::Reset()
{

}

void UAppendBuff::AppendBuff(UAbsBuff* _beAdd)
{

}
