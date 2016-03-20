// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDownComponent.h"

#include "CoolDown.h"
#include "Char/MyChar.h"
#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"

DECLARE_LOG_CATEGORY_EXTERN(UCoolDownLogger, Log, All);
DEFINE_LOG_CATEGORY(UCoolDownLogger)

// Sets default values
UCoolDownComponent::UCoolDownComponent(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	bAllowAnyoneToDestroyMe = true;
	mOwner = nullptr;
}

UCoolDownComponent::~UCoolDownComponent()
{
	UE_LOG(UCoolDownLogger, Warning, TEXT("--- deconstruct ~UCoolDownComponent"));
	mCDArr.Empty();
}

void UCoolDownComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UCoolDownComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(UCoolDownLogger, Warning, TEXT("--- UCoolDownComponent::TickComponent:%f"), DeltaTime);
	for (UCoolDown* cd : mCDArr)
	{
		if (!cd->IsNull())
			cd->Tick(DeltaTime);
	}
}

void UCoolDownComponent::CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class)
{
	UCoolDown* cd = NewObject<UCoolDown>(_class);
	cd->AddToRoot();
	cd->SetSkillId(_skillId);
	mCDArr.Add(cd);
}

void UCoolDownComponent::UseSkill(int32 _skillId, int32 _targetId)
{
	//bool noCD = true;
	for (UCoolDown* cd : mCDArr)
	{
		if (!cd->IsNull())
		{
			if (cd->GetSkillId() == _skillId)
			{
				if (cd->IsOK())
				{
					cd->UseSkill(mOwner, _targetId);
					return;
				}
			}
		}
	}
}

void UCoolDownComponent::RestartCD(int32 _skillId)
{
	for (UCoolDown* cd : mCDArr)
	{
		if (cd->GetSkillId() == _skillId)
		{
			cd->Restart();
			return;
		}
	}
}

void UCoolDownComponent::RemoveCDByType(ESkillType::Type _skillType)
{
	for (int32 i = 0; i < mCDArr.Num(); ++i)
	{
		if (mCDArr[i]->GetType() == _skillType)
		{
			mCDArr[i]->RemoveFromRoot();
			mCDArr.RemoveAtSwap(i);
			return;
		}
	}
}

void UCoolDownComponent::AddCD(ESkillType::Type _skillType, int32 _skillId, bool _isRestartCD)
{
	USkillTemplate* skillTemp = USkillDataMgr::GetInstance()->GetSkillTemplate(_skillId);
	if (skillTemp)
	{
		UCoolDown* cd = NewObject<UCoolDown>(UCoolDown::StaticClass());
		cd->AddToRoot();
		cd->SetSkillTemplate(skillTemp);
		cd->SetType(_skillType);
		if (_isRestartCD)
			cd->Restart();

		//清楚旧的，加入新的
		RemoveCDByType(_skillType);
		mCDArr.Add(cd);
	}
}
