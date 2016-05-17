
#pragma once

#include "../CharTypes.h"
#include "./MyBaseComp.h"
#include "MyCharDataComp.generated.h"

class UCoolDown;
class AMyChar;
class UFightData;
class UCharData;

UCLASS()
class UMyCharDataComp : public UMyBaseComp
{
	GENERATED_BODY()

public:
	UMyCharDataComp();
	virtual ~UMyCharDataComp();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override; //组件被new的时候立即调用
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	virtual void DestroyComponent(bool bPromoteChildren = false) override;
	// End UActorComponent Interface.

	void		SetFightData(UFightData* _data) { mFightData = _data; }
	UFightData*	GetFigthData() const { return mFightData; }

	void		SetCharData(int32 _id);
	UCharData*	GetCharhData() const { return mCharData; }

	const ETeam& GetTeamType() const { return mTeam; }

	void		SetHealth(float _value) { mHealth = _value; }
	float		GetHealth() const { return mHealth; }
	void		SetHealthMax(float _value) { mHealthMax = _value; }
	float		GetHealthMax() const { return mHealthMax; }

	//TODO 测试伤害，减血
	void		Hurt(float _value) { mHealth -= _value; }
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		UFightData*		mFightData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		UCharData*		mCharData;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		EGroup			mGroup;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		ETeam			mTeam;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealth;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyCharDataComp")
		float			mHealthMax;
};