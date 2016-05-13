// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "MySlate.h"
#include "Slate/MenuStyles.h"

//Custom implementation of the Default Game Module. 
class FSlateTutorialsGameModule : public FDefaultGameModuleImpl
{
	// Called whenever the module is starting up. In here, we unregister any style sets 
	// (which may have been added by other modules) sharing our 
	// style set's name, then initialize our style set. 
	virtual void StartupModule() override
	{
		//Hot reload hack
		FSlateStyleRegistry::UnRegisterSlateStyle(FMenuStyles::GetStyleSetName());
		FMenuStyles::Initialize();
	}

	// Called whenever the module is shutting down. Here, we simply tell our MenuStyles to shut down.
	virtual void ShutdownModule() override
	{
		FMenuStyles::Shutdown();
	}

};

//IMPLEMENT_PRIMARY_GAME_MODULE( FDefaultGameModuleImpl, MySlate, "MySlate" );
IMPLEMENT_PRIMARY_GAME_MODULE(FSlateTutorialsGameModule, MySlate, "MySlate");

DEFINE_LOG_CATEGORY(LogMySlate)
DEFINE_LOG_CATEGORY(FilterLogger)
DEFINE_LOG_CATEGORY(FuncLogger)
DEFINE_LOG_CATEGORY(SkillLogger)
DEFINE_LOG_CATEGORY(AnimLogger)
DEFINE_LOG_CATEGORY(BuffLogger)
DEFINE_LOG_CATEGORY(BulletLogger)
DEFINE_LOG_CATEGORY(CompLogger)
DEFINE_LOG_CATEGORY(PkLogger)
DEFINE_LOG_CATEGORY(AILogger)
DEFINE_LOG_CATEGORY(GolbalFuncLogger)
DEFINE_LOG_CATEGORY(ResLogger)
DEFINE_LOG_CATEGORY(EffectLogger)
DEFINE_LOG_CATEGORY(ObjLogger)
DEFINE_LOG_CATEGORY(GameLogger)
