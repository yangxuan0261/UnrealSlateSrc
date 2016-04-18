// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Tickable.h"

#include "BuffMgr.generated.h"

class UPkMsg;

UCLASS()
class UBuffMgr : public UObject, public FTickableGameObject, public USingleton<UBuffMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UBuffMgr();
	virtual ~UBuffMgr();

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

	//=== buffer运行 begin ===
	void RunBeforePkBuffs(int32 _charId, UPkMsg* msg);//buffer前置
	void RunEndPkBuffs(int32 _charId, UPkMsg* msg);//buffer后置
	//=== buffer运行 end   ===
public:
	

private:
};
