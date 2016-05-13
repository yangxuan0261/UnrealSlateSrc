#include "MySlate.h"
#include "MyGameInstance.h"

#include "./Char/Skill/SkillMgr.h"
#include "./Char/CharMgr.h"
#include "./Char/Skill/Function/FuncFactory.h"
#include "./Char/Skill/Buff/BuffMgr.h"
#include "./Char/Res/ResMgr.h"
#include "./Char/Effect/EffectMgr.h"
#include "./Char/Object/ObjMgr.h"

USkillMgr*		UMyGameInstance::gSkillMgr = nullptr;
UCharMgr*		UMyGameInstance::gCharMgr = nullptr;
UFuncFactory*	UMyGameInstance::gFunctionMgr = nullptr;
UBuffMgr*		UMyGameInstance::gBuffMgr = nullptr;
UResMgr*		UMyGameInstance::gResMgr = nullptr;
UEffectMgr*		UMyGameInstance::gEffectMgr = nullptr;
UObjMgr*		UMyGameInstance::gObjMgr = nullptr;

UMyGameInstance::UMyGameInstance(const FObjectInitializer& ObjectInitializer)
: Super(ObjectInitializer)
{

}

void UMyGameInstance::Init()
{
	Super::Init();
	UE_LOG(GameLogger, Warning, TEXT("--- UMyGameInstance::Init"));

	UMyGameInstance::SetInstance(this); //将这个对象设置为单例对象

	gSkillMgr = gGetSkill();
	gCharMgr = gGetChar();
	gFunctionMgr = gGetFactory();
	gFunctionMgr->InitFuncAndFilters();
	gBuffMgr = gGetBuff();
	gResMgr = UResMgr::GetInstance();
	gEffectMgr = gGetEffect();
	gObjMgr = UObjMgr::GetInstance();
}

void UMyGameInstance::Shutdown()
{
	UMyGameInstance::SetInstance(nullptr);

	USkillMgr::ReleaseInstance();
	UCharMgr::ReleaseInstance();
	UFuncFactory::ReleaseInstance();
	UBuffMgr::ReleaseInstance();
	UResMgr::ReleaseInstance();
	UEffectMgr::ReleaseInstance();
	UObjMgr::ReleaseInstance(); //暂时不释放对象，避免stop时崩溃
	gSkillMgr = nullptr;
	gCharMgr = nullptr;
	gFunctionMgr = nullptr;
	gBuffMgr = nullptr;
	gResMgr = nullptr;
	gEffectMgr = nullptr;
	gObjMgr = nullptr;

	UE_LOG(GameLogger, Warning, TEXT("--- UMyGameInstance::Shutdown"));
	Super::Shutdown();
}

//void UMyGameInstance::Init()
//{
//	FCoreUObjectDelegates::PreLoadMap.AddUObject(this, &UMyGameInstance::MyBeginLoadingScreen);
//	FCoreUObjectDelegates::PostLoadMap.AddUObject(this, &UMyGameInstance::MyEndLoadingScreen);
//}
//
//void UMyGameInstance::MyBeginLoadingScreen()
//{
//	FLoadingScreenAttributes LoadingScreen;
//	LoadingScreen.bAutoCompleteWhenLoadingCompletes = false;
//	LoadingScreen.WidgetLoadingScreen = FLoadingScreenAttributes::NewTestLoadingScreenWidget();
//
//	GetMoviePlayer()->SetupLoadingScreen(LoadingScreen);
//}
//
//void UMyGameInstance::MyEndLoadingScreen()
//{
//}
