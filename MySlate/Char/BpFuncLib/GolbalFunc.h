
#pragma once

#include "GolbalFunc.generated.h"

class USkillMgr;
class UCharMgr;
class UFuncFactory;
class UBuffMgr;
class UResMgr;
class UEffectMgr;
class AMyChar;

UCLASS()
class UGolbalFunc : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UGolbalFunc();
	virtual ~UGolbalFunc();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					InitMgrs();
	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					DestroyMgrs();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static USkillMgr*			GetSkillMgr() { return gSkillMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UBuffMgr*			GetBuffMgr() { return gBuffMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UCharMgr*			GetCharMgr() { return gCharMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UResMgr*				GetResMgr() { return gResMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static UEffectMgr*			GetEffectMgr() { return gEffectMgr; }

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TurnForward(AActor* _actor, const FVector& _targetLoc);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					DrawSegment(const FVector& _start, const FVector& _end, float _time = 5.f);

	//--------------- test function
	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestStrSplit();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestMapRmove();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestForceGC();

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestStrContains(FString _str);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestFilter(AMyChar* _actor, float _radius);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestSpwanBullet(AMyChar* _actor);

	UFUNCTION(BlueprintCallable, Category = "GolbalFunc")
		static void					TestArrLambda(FString _str);

private:
	static USkillMgr*				gSkillMgr;
	static UCharMgr*				gCharMgr;
	static UFuncFactory*			gFunctionMgr;
	static UBuffMgr*				gBuffMgr;
	static UResMgr*					gResMgr;
	static UEffectMgr*				gEffectMgr;
};
