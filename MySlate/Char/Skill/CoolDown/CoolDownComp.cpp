// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDownComp.h"

#include "CoolDown.h"
#include "Char/MyChar.h"
#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillFunction.h"

// Sets default values
UCoolDownComp::UCoolDownComp()
	: Super()
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = false;
	bAllowAnyoneToDestroyMe = true;
	mOwner = nullptr;
}

UCoolDownComp::~UCoolDownComp()
{
	UE_LOG(CompLogger, Warning, TEXT("--- UCoolDownComp::~UCoolDownComp"));
}

void UCoolDownComp::BeginPlay()
{
	Super::BeginPlay();
}

void UCoolDownComp::BeginDestroy()
{
	Super::BeginDestroy();
}

void UCoolDownComp::DestroyComponent(bool bPromoteChildren /*= false*/)
{
	for (UCoolDown* cd : mCDArr)
	{
		cd->RemoveFromRoot();
		cd->ConditionalBeginDestroy();
	}
	mCDArr.Empty();

	UE_LOG(CompLogger, Warning, TEXT("--- UCoolDownComp::DestroyComponent"));
	Super::DestroyComponent(bPromoteChildren);
}

void UCoolDownComp::MyTick(float DeltaTime)
{
	for (UCoolDown* cd : mCDArr)
	{
		if (!cd->IsNull())
		{
			if (!cd->IsOK())
			{
				cd->Tick(DeltaTime);
			}
		}
	}
}

void UCoolDownComp::CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class)
{
	//UCoolDown* cd = NewObject<UCoolDown>(_class);
	//cd->AddToRoot();
	//cd->SetSkillId(_skillId);
	//mCDArr.Add(cd);
}

USkillFunction* UCoolDownComp::CanUseSkill(int32 _skillId)
{
	for (UCoolDown* cd : mCDArr)
	{
		if (cd->GetSkillId() == _skillId)
		{
			if (!cd->IsNull())
			{
				if (cd->IsOK())
				{
					return cd->GetSkillFunc();
				}
			}
		}
	}

	UE_LOG(CompLogger, Warning, TEXT("--- UCoolDownComp::CanUseSkill, nullptr"));
	return nullptr;
}

void UCoolDownComp::RestartCD(int32 _skillId)
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

void UCoolDownComp::RemoveCDById(int32 _skillId)
{
	for (int32 i = 0; i < mCDArr.Num(); ++i)
	{
		if (mCDArr[i]->mSkillId == _skillId)
		{
			mCDArr[i]->RemoveFromRoot();
			mCDArr[i]->ConditionalBeginDestroy(); //cd对象丢给gc系统
			mCDArr.RemoveAt(i);
			UE_LOG(CompLogger, Error, TEXT("--- UCoolDownComp::RemoveCDById, skillId:%d"), _skillId);
			return;
		}
	}
}

void UCoolDownComp::AddCD(int32 _skillId, bool _isRestartCD)
{
	USkillTemplate* skillTemp = USkillDataMgr::GetInstance()->GetSkillTemplate(_skillId);
	if (skillTemp)
	{
		////清楚旧的
		RemoveCDById(_skillId);

		UCoolDown* cd = NewObject<UCoolDown>(UCoolDown::StaticClass());
		cd->AddToRoot();
		mCDArr.Add(cd);
		cd->SetSkillTemplate(skillTemp); 
		cd->SetChar(mOwner);
		if (_isRestartCD) {
			cd->Restart();
		}
		mCDArr.Add(cd);
	}
	else
	{
		UE_LOG(CompLogger, Error, TEXT("--- Error: No USkillTemplate, mSkillId:%d"), _skillId);
	}
}
