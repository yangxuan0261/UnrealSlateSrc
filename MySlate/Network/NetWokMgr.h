
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
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UNetWokMgr")
		float GetSpeed();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UNetWokMgr")
		int32  GetCadence();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UNetWokMgr")
		int32  GetBodyHeartRate();
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "UNetWokMgr")
		int32  GetDirection();
	UFUNCTION(BlueprintCallable, Category = "UNetWokMgr")
		bool connectSensor(const FString &IP, const int32 &port);

private:
	FSocket *ConnectionSocket;
	FIPv4Endpoint RemoteAddressForConnection;
	FTimerHandle TimerHandle;

	float fSpeed;
	int32 iRotaion;
	int32 iBodyRate;
	int32 iDirection;

	bool FormatReceiveDataToNumber(const FString& recvData, int32 &heart, int32 &rotation, float &speed, int32 &direction);
	FSocket* CreateTCPConnection(const FString& TheIP, const int32 ThePort, const int32 ReceiveBufferSize);

	FString StringFromBinaryArray(const TArray<uint8>& BinaryArray);
	void TCPSocketListener();
};

#define gGetNetMgr()			UNetWokMgr::GetInstance()