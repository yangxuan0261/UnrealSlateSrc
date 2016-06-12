
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

void UGolbalFunc::TestString(FString _str)
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- UGolbalFunc::BeginDestroy, %s"), *_str);
}

void UGolbalFunc::testSocket(FString _ip, int32 _port)
{
	//FSocket* Socket = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateSocket(NAME_Stream, TEXT("default"), false);

	//FString address = _ip;
	//FIPv4Address ip;
	//FIPv4Address::Parse(address, ip);

	//TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	//addr->SetIp(*ip.ToString());
	//addr->SetPort(_port);

	//bool connected = Socket->Connect(*addr);
	//if (connected)
	//{
	//	FString serialized = TEXT("loadPlayer|1");
	//	TCHAR *serializedChar = serialized.GetCharArray().GetData();
	//	int32 size = FCString::Strlen(serializedChar);
	//	int32 sent = 0;

	//	bool successful = Socket->Send((uint8*)TCHAR_TO_UTF8(serializedChar), size, sent);
	//}
}
