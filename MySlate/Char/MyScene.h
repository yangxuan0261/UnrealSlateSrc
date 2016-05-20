#pragma once

/*
场景actor，做场景特效，摄像机振动等, 把观察模式的SpectatorPawn引入
*/

#include "./ExtInter/BehavInter.h"
#include "../Common/ISingleton.h"

#include "MyScene.generated.h"

class AMySpectator;

UCLASS()
class AMyScene : public AActor, public IBehavInterface, public USingleton<AMyScene>
{
	GENERATED_BODY()

public:	
	AMyScene();
	virtual ~AMyScene();

	// Begin Actor interface
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void Destroyed() override;
	// End Actor interface

	void		BindSpectator();
	AMySpectator*	GetSpectator() const { return mSpectator; }
private:
	AMySpectator*	mSpectator;
};

#define gGetScene()			AMyScene::GetInstance()