
#pragma once

#include "../../../Common/ISingleton.h"

#include "SkillDataMgr.generated.h"

class USkillTemplate;
class UBufflTemplate;

UCLASS()
class USkillDataMgr : public UObject, public USingleton<USkillDataMgr>
{
	GENERATED_BODY()

public:
	USkillDataMgr();
	virtual ~USkillDataMgr();
	virtual void BeginDestroy() override;

public:

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		USkillTemplate*		CreateSkillTemp(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		UBufflTemplate*		CreateBuffTemp(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		USkillTemplate*		GetSkillTemplate(int32 _skillId);
	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		UBufflTemplate*		GetBuffTemplate(int32 _buffId);

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void				LoadSkillData();

	UFUNCTION(BlueprintCallable, Category = "USkillDataMgr")
		void				LoadBuffData();

private:
	void				InitFakeDate();//不在这里模拟数据，在蓝图中生产

private:
	TMap<int32, USkillTemplate*>	mSkillTempMap;
	TMap<int32, UBufflTemplate*>	mBuffTempMap;
};
