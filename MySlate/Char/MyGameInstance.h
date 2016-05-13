
#pragma once
#include "./Common/ISingleton.h"
#include "MyGameInstance.generated.h"

class USkillMgr;
class UCharMgr;
class UFuncFactory;
class UBuffMgr;
class UResMgr;
class UEffectMgr;
class UObjMgr;

UCLASS()
class MYSLATE_API UMyGameInstance : public UGameInstance, public USingleton<UMyGameInstance>
{
	GENERATED_BODY()
public:
	UMyGameInstance(const FObjectInitializer& ObjectInitializer);

	/** virtual function to allow custom GameInstances an opportunity to set up what it needs */
	virtual void Init() override;
	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

public:


private:
	static USkillMgr*		gSkillMgr;
	static UCharMgr*		gCharMgr;
	static UFuncFactory*	gFunctionMgr;
	static UBuffMgr*		gBuffMgr;
	static UResMgr*			gResMgr;
	static UEffectMgr*		gEffectMgr;
	static UObjMgr*			gObjMgr;
};

#define GetGame()			UMyGameInstance::GetInstance()