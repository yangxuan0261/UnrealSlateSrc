
#pragma once

#include "./Char/Skill/SkillMgr.h"
#include "./Char/CharMgr.h"
#include "./Char/Skill/Function/FuncFactory.h"
#include "./Char/Skill/Buff/BuffMgr.h"
#include "./Char/Res/ResMgr.h"
#include "./Char/Effect/EffectMgr.h"
#include "./Char/Object/ObjMgr.h"

#include "GolbalFunc.generated.h"

UCLASS()
class UGolbalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UGolbalFunc();
	virtual ~UGolbalFunc();
	virtual void BeginDestroy() override;

	template<typename	TRetType>
	static TRetType*				GetMgr() { return TRetType::GetInstance();}

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					InitMgrs();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					DestroyMgrs();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillMgr*			GetSkillMgr() { return GetMgr<USkillMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UBuffMgr*			GetBuffMgr() { return GetMgr<UBuffMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UCharMgr*			GetCharMgr() { return GetMgr<UCharMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UResMgr*				GetResMgr() { return GetMgr<UResMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UEffectMgr*			GetEffectMgr() { return GetMgr<UEffectMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UObjMgr*				GetObjtMgr() { return GetMgr<UObjMgr>(); }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TurnForward(AActor* _actor, const FVector& _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					DrawSegment(const FVector& _start, const FVector& _end, float _time = 5.f);

	//--------------- test function
	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestForceGC();

};
