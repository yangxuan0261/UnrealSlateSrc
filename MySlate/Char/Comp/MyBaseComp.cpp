
#include "MySlate.h"
#include "MyBaseComp.h"


UMyBaseComp::UMyBaseComp()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
}

UMyBaseComp::~UMyBaseComp()
{

}

void UMyBaseComp::BeginPlay()
{
	Super::BeginPlay();
}

void UMyBaseComp::TickComponent( float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction )
{
	Super::TickComponent( DeltaTime, TickType, ThisTickFunction );
}

void UMyBaseComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{

	Super::DestroyComponent(bPromoteChildren);
}

void UMyBaseComp::Reset()
{

}

