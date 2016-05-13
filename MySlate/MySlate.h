// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#ifndef __MYSLATE_H__
#define __MYSLATE_H__

#include "EngineMinimal.h"
//#include "Engine.h"
#include "EngineGlobals.h"
#include "Engine/Engine.h"
#include "Engine/StreamableManager.h"

#include "CanvasItem.h"
#include "Engine/Canvas.h"

//----- behavior tree and ai Begin -----
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Bool.h"
#include "BehaviorTree/Decorators/BTDecorator_BlueprintBase.h"
#include "BehaviorTree/Services/BTService_BlueprintBase.h"
#include "BehaviorTree/BTNode.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BehaviorTree/Tasks/BTTask_BlueprintBase.h"
#include "AIController.h"
#include "AI/Navigation/NavigationSystem.h"

//----- Animation Begin -----
#include "Animation/AnimInstance.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"

//----- Component Begin -----
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

//----- engine util Begin -----
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
//----- Animation Begin -----


DECLARE_LOG_CATEGORY_EXTERN(LogMySlate, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FilterLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(FuncLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(SkillLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(AnimLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(BuffLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(BulletLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(CompLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(PkLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(AILogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(GolbalFuncLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ResLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(EffectLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(ObjLogger, Log, All);
DECLARE_LOG_CATEGORY_EXTERN(GameLogger, Log, All);

//use logger
//UE_LOG(SkillLogger, Warning, TEXT("--- USkillFunction::~USkillFunction:%d"), mSkillId);

#endif
