
#pragma once

#include "../../Common/ISingleton.h"
#include "Tickable.h"
#include "../Skill/SkillTypes.h"
#include "EffectMgr.generated.h"

class UEffDataElem;
class UShakeElem;
struct FEffElemInfo;
struct FShakeInfo;
class UBehavData;
class AMyChar;
class AMyBullet;

USTRUCT()
struct FEffectBind
{
	GENERATED_USTRUCT_BODY()
public:
	FEffectBind() {}
	bool operator ==(const FEffectBind& _cp) //重载==操作符，TArray remove中需要用到
	{
		return mUuId == _cp.mUuId;
	}
	FEffectBind(UEffDataElem* _effData, int32 _uuId, UParticleSystemComponent* _psComp);
	int32	mUuId;		//唯一识别，区分相同buff移除
	float	mDelayTimer; //延迟时间 计步器
	bool	mHasDelay; //延迟时间 计步器
	float	mTotalTimer; //总时间 计步器
	bool	mHasTotal; //总时间 计步器
	UEffDataElem*	mEffData;
	UParticleSystemComponent* mPsComp; //生成的粒子组件
};

UCLASS()
class UEffectMgr : public UObject, public FTickableGameObject, public USingleton<UEffectMgr>
{
	GENERATED_BODY()

public:
	UEffectMgr();
	virtual ~UEffectMgr();
	virtual void BeginDestroy() override;

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			loadBehavInfo();	//TODO: 待优化，不一次性加载，用到时才加载
	void		CopyEffInfoToData(TArray<FEffElemInfo>& _info, TArray<UEffDataElem*>& _dstVec);
	void		CopyShkInfoToData(TArray<FShakeInfo>& _info, TArray<UShakeElem*>& _dstVec);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UBehavData*		GetBehav(int32 _key);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			AttachBehav(AMyChar* _tarChar, EOwnType _ownType, AMyBullet* _tarBullet, int32 _behavDataId);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		void			DetachEffect(int32 _targetId, const TArray<int32>& _effuuids);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UShakeElem*	TestShake(AMyChar* _actor, int32 _id);

public:
	TMap<int32, TArray<FEffectBind>>	mEffectBindMap; //特效数组
	TMap<int32, UBehavData*>	mBehavMap;
};
