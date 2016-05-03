
#pragma once

#include "Tickable.h"
#include "../../Common/ISingleton.h"
#include "../Effect/Effects/UBehavData.h"

#include "SkillMgr.generated.h"

class AMyChar;
class USkillTemplate;
class UBufflTemplate;

UCLASS()
class USkillMgr : public UObject, public FTickableGameObject, public USingleton<USkillMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	USkillMgr();
	virtual ~USkillMgr();
	virtual void BeginDestroy() override;

	// Begin FTickableGameObject Interface.
	virtual void Tick(float DeltaTime) override;
	virtual bool IsTickable() const override;
	virtual TStatId GetStatId() const override;
	// End FTickableGameObject Interface.

public:
	UFUNCTION(BlueprintCallable, Category = "USkillMgr")
		void			CharDeathNotify(AMyChar* _char);

	//-------------- datas
	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		USkillTemplate*		GetSkillTemplate(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		UBufflTemplate*		GetBuffTemplate(int32 _buffId);

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void				LoadSkillData();

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void				LoadBuffData();

private:
	TMap<int32, USkillTemplate*>	mSkillTempMap;
	TMap<int32, UBufflTemplate*>	mBuffTempMap;
};
