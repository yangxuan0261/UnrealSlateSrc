
#include "MySlate.h"
#include "CommonBuff.h"

UCommonBuff::UCommonBuff() : Super()
{
	IObjInterface::SetObj(this);
}

UCommonBuff::~UCommonBuff()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UCommonBuff::~UCommonBuff"));
}

void UCommonBuff::BeginDestroy()
{


	UE_LOG(BuffLogger, Warning, TEXT("--- UCommonBuff::BeginDestroy"));
	Super::BeginDestroy();
}

void UCommonBuff::Reset()
{

}
