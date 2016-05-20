
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
class IBehavInterface;
class USkillTemplate;

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
		int32			AttachBehav(AMyChar* _tarChar, EOwnType _ownType, AMyBullet* _tarBullet, int32 _behavDataId);

		void			DetachBehav(IBehavInterface* _actor, int32 _groupId);
		void			AttachMesh(AMyBullet* _bullet, USkillTemplate* _skillTemp);

	UFUNCTION(BlueprintCallable, Category = "UEffectMgr")
		UShakeElem*	TestShake(AMyChar* _actor, int32 _id);

public:
	TMap<int32, UBehavData*>	mBehavMap;
};

#define gGetEffectMgr()			UEffectMgr::GetInstance()