
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
void UNetWokMgr::Launch()
{
	//IP = 127.0.0.1, Port = 8890 for my Python test case
	if (!StartTCPReceiver("RamaSocketListener", "127.0.0.1", 8890))
	{
		//UE_LOG  "TCP Socket Listener Created!"
		return;
	}

	//UE_LOG  "TCP Socket Listener Created! Yay!"
}

//Rama's Start TCP Receiver
bool UNetWokMgr::StartTCPReceiver(
	const FString& YourChosenSocketName,
	const FString& TheIP,
	const int32 ThePort
) {
	//Rama's CreateTCPConnectionListener
	ListenerSocket = CreateTCPConnectionListener(YourChosenSocketName, TheIP, ThePort);

	//Not created?
	if (!ListenerSocket)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartTCPReceiver>> Listen socket could not be created! ~> %s %d"), *TheIP, ThePort));
		return false;
	}

	//Start the Listener! //thread this eventually
	GetWorld()->GetTimerManager().SetTimer(mListener, FTimerDelegate::CreateUObject(this, &UNetWokMgr::TCPConnectionListener), 0.01, true); //设置定时器

	return true;
}

//Rama's Create TCP Connection Listener
FSocket* UNetWokMgr::CreateTCPConnectionListener(const FString& YourChosenSocketName, const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize)
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//Create Socket
	FIPv4Address tmpIpv4;
	FIPv4Address::Parse(TheIP, tmpIpv4);
	FIPv4Endpoint Endpoint(tmpIpv4, ThePort);
	FSocket* ListenSocket = FTcpSocketBuilder(*YourChosenSocketName)
		.AsReusable()
		.BoundToEndpoint(Endpoint)
		.Listening(8);

	//Set Buffer Size
	int32 NewSize = 0;
	ListenSocket->SetReceiveBufferSize(ReceiveBufferSize, NewSize);

	//Done!
	return ListenSocket;
}

//Rama's TCP Connection Listener
void UNetWokMgr::TCPConnectionListener()
{
	//~~~~~~~~~~~~~
	if (!ListenerSocket) return;
	//~~~~~~~~~~~~~

	//Remote address
	TSharedRef<FInternetAddr> RemoteAddress = ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->CreateInternetAddr();
	bool Pending;

	// handle incoming connections
	if (ListenerSocket->HasPendingConnection(Pending) && Pending)
	{
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
		//Already have a Connection? destroy previous
		if (ConnectionSocket)
		{
			ConnectionSocket->Close();
			ISocketSubsystem::Get(PLATFORM_SOCKETSUBSYSTEM)->DestroySocket(ConnectionSocket);
		}
		//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

		//New Connection receive!
		ConnectionSocket = ListenerSocket->Accept(*RemoteAddress, TEXT("RamaTCP Received Socket Connection"));

		if (ConnectionSocket != NULL)
		{
			//Global cache of current Remote Address
			RemoteAddressForConnection = FIPv4Endpoint(RemoteAddress);

			//UE_LOG "Accepted Connection! WOOOHOOOO!!!";

			//can thread this too
			GetWorld()->GetTimerManager().SetTimer(mListener, FTimerDelegate::CreateUObject(this, &UNetWokMgr::TCPSocketListener), 0.01, true); //设置定时器
		}
	}
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


	//Binary Array!
	TArray<uint8> ReceivedData;

	uint32 Size;
	while (ConnectionSocket->HasPendingData(Size))
	{
		ReceivedData.Init(FMath::Min(Size, 65507u));

		int32 Read = 0;
		ConnectionSocket->Recv(ReceivedData.GetData(), ReceivedData.Num(), Read);

		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Read! %d"), ReceivedData.Num()));
	}
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (ReceivedData.Num() <= 0)
	{
		//No Data Received
		return;
	}

	UE_LOG(NetLogger, Error, TEXT("--- UNetWokMgr， Total Data read : %d"), ReceivedData.Num());
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Data Bytes Read ~> %d"), ReceivedData.Num()));


	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	//						Rama's String From Binary Array
	const FString ReceivedUE4String = StringFromBinaryArray(ReceivedData);
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	UE_LOG(NetLogger, Error, TEXT("--- UNetWokMgr， As String!!!!! ~> : %s"), *ReceivedUE4String);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("As String Data ~> %s"), *ReceivedUE4String));
}