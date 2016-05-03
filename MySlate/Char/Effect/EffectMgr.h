
#pragma once

#include "../../Common/ISingleton.h"
#include "Tickable.h"
#include "EffectMgr.generated.h"

class UEffDataElem;
class UBehavData;

USTRUCT()
struct FEffectBind
{
	GENERATED_USTRUCT_BODY()
public:
	FEffectBind();
	bool operator ==(const FEffectBind& _cp) //重载==操作符，TArray remove中需要用到
	{
		return mUuId == _cp.mUuId;
	}
	FEffectBind(UEffDataElem* _effData, int32 _lefTtime, int32 _uuId, UParticleSystemComponent* _psComp);
	int32	mUuId;		//唯一识别，区分相同buff移除
	float	mDelayTimer; //延迟时间 计步器
	bool	mHasDelay; //延迟时间 计步器
	float	mLeftTimer;	//剩余时间 计步器
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

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UBehavData*		GetBehav(int32 _key);

	//advanced attach
	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		TArray<int32>	AttachBehavData(AMyChar* _target, int32 _behavDataId, float _time = -1.f);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		bool			AttachBehavDataOnce(AMyChar* _target, UBehavData* _behavData);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			CreateEffBind(AMyChar* _target, UEffDataElem* _ele, float _time, TArray<FEffectBind>& _bindArr, TArray<int32>& _dstUuids, bool _isDurable = true);

	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			DetachEffect(int32 _targetId, const TArray<int32>& _effuuids);

	//normal attach
	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		TArray<int32>	AttachBehavData2(AMyChar* _target, int32 _behavDataId, float _time = -1.f);


public:
	TMap<int32, TArray<FEffectBind>>	mEffectBindMap; //特效数组
	TMap<int32, UBehavData*>	mBehavMap;
};
