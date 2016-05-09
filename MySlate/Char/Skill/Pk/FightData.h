#pragma once

#include "../Utils/CommonDef.h"
#include "../../Object/ObjInter.h"

#include "FightData.generated.h"

UCLASS()
class UFightData : public UObject, public IObjInterface
{
	GENERATED_BODY()

public:
	UFightData();
	virtual ~UFightData();
	virtual void BeginDestroy() override;

	//obj interface
	virtual void Reset() override;

	UFightData* Clone();
	void Copy(UFightData* _fightData);
	

	float GetAttackPhy() const { return mAttackPhy; }
	float GetLv() const { return mLv; }

public:
	//原始属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mAttackPhy;		//物理攻击

public:
	//成长相关
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		int			mLv;			//等级

public:
};
