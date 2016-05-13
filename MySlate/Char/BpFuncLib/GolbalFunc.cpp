
#include "MySlate.h"
#include "GolbalFunc.h"

#include "../MyChar.h"

UGolbalFunc::UGolbalFunc() : Super()
{
	
}

UGolbalFunc::~UGolbalFunc()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UGolbalFunc::~UGolbalFunc"));
}

void UGolbalFunc::BeginDestroy()
{

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UGolbalFunc::BeginDestroy"));
	Super::BeginDestroy();
}

void UGolbalFunc::InitMgrs()
{

}

void UGolbalFunc::DestroyMgrs()
{

}

void UGolbalFunc::TurnForward(AActor* _actor, const FVector& _targetLoc)
{
	FRotator rota = UKismetMathLibrary::FindLookAtRotation(_actor->GetActorLocation(), _targetLoc);
	_actor->SetActorRotation(rota);
}

void UGolbalFunc::DrawSegment(const FVector& _start, const FVector& _end, float _time /* = 5.f */)
{
	::DrawDebugLine(GWorld, _start, _end, FColor::Red, true, _time);
	::DrawDebugSolidBox(GWorld, _start, FVector(5.f, 5.f, 5.f), FColor::Green, true, _time);
	::DrawDebugSolidBox(GWorld, _end, FVector(5.f, 5.f, 5.f), FColor::Green, true, _time);

	//dist
	int32 dist = (int32)(_end - _start).Size();
	::DrawDebugString(GWorld, (_start + _end) / 2.f, FString::Printf(TEXT("%d"), dist), nullptr, FColor::Green, 5.f, true);
}

void UGolbalFunc::TestForceGC()
{
	GWorld->GetWorld()->ForceGarbageCollection(true);
}
