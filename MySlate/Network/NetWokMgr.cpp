
#include "MySlate.h"
#include "NetWokMgr.h"
#include <string>

UNetWokMgr::UNetWokMgr()
{

}

UNetWokMgr::~UNetWokMgr()
{
	UE_LOG(NetLogger, Warning, TEXT("--- UNetWokMgr::~UNetWokMgr"));
}

void UNetWokMgr::BeginDestroy()
{
	
	UE_LOG(NetLogger, Warning, TEXT("--- UNetWokMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UNetWokMgr::Tick(float DeltaTime)
{

}

bool UNetWokMgr::IsTickable() const
{
	return true;
}

TStatId UNetWokMgr::GetStatId() const
{
	return TStatId();
}

//---------------------------------
bool UNetWokMgr::connectSensor(const FString &IP, const int32 &port) {
	ConnectionSocket = CreateTCPConnection(IP, port, 1024);
	if (!ConnectionSocket) {
		return false;
	}


	if (TimerHandle.IsValid() == false) {
		GetWorld()->GetTimerManager().SetTimer(TimerHandle, this,
			&UNetWokMgr::TCPSocketListener, 1.0f / 60.0f, true);
	}


	return true;
}

FSocket* UNetWokMgr::CreateTCPConnection(const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	FSocket* retSocket = NULL;

	ISocketSubsystem* SocketSubsystem = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM);

	if (SocketSubsystem != NULL)
	{
		retSocket = SocketSubsystem->CreateSocket(NAME_Stream, "SensorConnect", true);
	}

	FIPv4Address ip;
	FIPv4Address::Parse(TheIP, ip);
	//auto addr = SocketSubsystem->CreateInternetAddr();
	TSharedRef<FInternetAddr> addr = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool isValid = false;
	addr->SetIp(*ip.ToString(), isValid);//setIP
	addr->SetPort(ThePort);

	if (!retSocket->Connect(*addr)) {
		return NULL;
	}


	UE_LOG(NetLogger, Warning, TEXT("--- UNetWokMgr::CreateTCPConnection"));


	return retSocket;
}

//Rama's String From Binary Array
//This function requires
//		#include <string>
FString UNetWokMgr::StringFromBinaryArray(const TArray<uint8>& BinaryArray)
{
	//Create a string from a byte array!
	std::string cstr(reinterpret_cast<const char*>(BinaryArray.GetData()), BinaryArray.Num());
	return FString(cstr.c_str());
}

//Rama's TCP Socket Listener
void UNetWokMgr::TCPSocketListener()
{
	//~~~~~~~~~~~~~
	if (!ConnectionSocket) return;
	//~~~~~~~~~~~~~


	int32 sendType = 1;
	int sent;
	ConnectionSocket->Send((uint8 *)&sendType, sizeof(sendType), sent);

	//Binary Array!
	uint32 Size = 0;

	while (ConnectionSocket->HasPendingData(Size))
	{
		TArray<uint8> ReceivedData;
		ReceivedData.SetNumUninitialized(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);
		if (ReceivedData.Num() <= 0)
		{
		}
		else {
			const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
			FormatReceiveDataToNumber(ReceivedUE4String, iBodyRate, iRotaion, fSpeed, iDirection);
		}

	}

}

bool UNetWokMgr::FormatReceiveDataToNumber(const FString& recvData, int32 &heart, int32 &rotation, float &speed, int32 &direction) {
	//IP Formatting
	recvData.Replace(TEXT(" "), TEXT(""));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						   IP 4 Parts

	//String Parts
	TArray<FString> Parts;
	recvData.ParseIntoArray(Parts, TEXT(","), true);
	if (Parts.Num() != 4)
		return false;

	heart = FCString::Atoi(*Parts[0]);
	rotation = FCString::Atoi(*Parts[1]);
	speed = FCString::Atof(*Parts[2]);
	direction = FCString::Atoi(*Parts[3]);


	return true;
}

float UNetWokMgr::GetSpeed() {
	if (!ConnectionSocket)return 0.0f;
	return fSpeed;
}

int32  UNetWokMgr::GetCadence() {
	if (!ConnectionSocket) return 0;
	return iRotaion;
}

int32  UNetWokMgr::GetBodyHeartRate() {
	if (!ConnectionSocket) return 0;
	return iBodyRate;
}

int32  UNetWokMgr::GetDirection() {
	if (!ConnectionSocket) return 0;
	return iDirection;
}



