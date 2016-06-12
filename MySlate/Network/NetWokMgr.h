
#pragma once

#include "../Common/ISingleton.h"
#include "Tickable.h"
#include "NetWokMgr.generated.h"


UCLASS()
class UNetWokMgr : public UObject, public FTickableGameObject, public USingleton<UNetWokMgr>
{
	GENERATED_BODY()

public:
	UNetWokMgr();
	virtual ~UNetWokMgr();
	virtual void BeginDestroy() override;

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:

	FSocket* ListenerSocket;
	FSocket* ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;
	void Launch();

	bool StartTCPReceiver(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort
	);

	FSocket* CreateTCPConnectionListener(
		const FString& YourChosenSocketName,
		const FString& TheIP,
		const int32 ThePort,
		const int32 ReceiveBufferSize = 2 * 1024 * 1024
	);

	//Timer functions, could be threads
	void TCPConnectionListener(); 	//can thread this eventually
	void TCPSocketListener();		//can thread this eventually

	//Rama's StringFromBinaryArray
	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);

public:
	FTimerHandle       mListener;
};

#define gNetMgr()			UNetWokMgr::GetInstance()