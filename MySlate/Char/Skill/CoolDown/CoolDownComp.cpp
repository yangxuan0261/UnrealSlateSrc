// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDownComp.h"

#include "CoolDown.h"
#include "Char/MyChar.h"
#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillFunction.h"

DECLARE_LOG_CATEGORY_EXTERN(UCoolDownLogger, Log, All);
DEFINE_LOG_CATEGORY(UCoolDownLogger)

// Sets default values
UCoolDownComp::UCoolDownComp(const FObjectInitializer& ObjectInitializer): Super(ObjectInitializer)
{
	bWantsBeginPlay = true;
	PrimaryComponentTick.bCanEverTick = true;
	bAllowAnyoneToDestroyMe = true;
	mOwner = nullptr;
}

UCoolDownComp::~UCoolDownComp()
{
	UE_LOG(UCoolDownLogger, Warning, TEXT("--- deconstruct ~UCoolDownComp"));
	for (UCoolDown* cd : mCDArr)
		cd->RemoveFromRoot();
	mCDArr.Empty();
}

void UCoolDownComp::BeginPlay()
{
	Super::BeginPlay();
}

void UCoolDownComp::BeginDestroy()
{
	Super::BeginDestroy();
}

void UCoolDownComp::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	//UE_LOG(UCoolDownLogger, Warning, TEXT("--- UCoolDownComp::TickComponent:%f"), DeltaTime);
	for (UCoolDown* cd : mCDArr)
	{
		if (!cd->IsNull())
			cd->Tick(DeltaTime);
	}
}

void UCoolDownComp::CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class)
{
	//UCoolDown* cd = NewObject<UCoolDown>(_class);
	//cd->AddToRoot();
	//cd->SetSkillId(_skillId);
	//mCDArr.Add(cd);
}

void UCoolDownComp::UseSkill(UCoolDown* _skill, int32 _targetId)
{
	//bool noCD = true;
	for (UCoolDown* cd : mCDArr)
	{
		if (cd == _skill)
		{
			if (!cd->IsNull())
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

void UCoolDownComp::RemoveCDByType(ESkillType _skillType)
{
	for (int32 i = 0; i < mCDArr.Num(); ++i)
	{
		if (mCDArr[i]->mSkillFunc->mType == _skillType)
		{
			mCDArr[i]->RemoveFromRoot(); //销毁这个cd对象
			mCDArr.RemoveAt(i);
			return;
		}
	}
}

void UCoolDownComp::AddCD(ESkillType _skillType, int32 _skillId, bool _isRestartCD)
{
	USkillTemplate* skillTemp = USkillDataMgr::GetInstance()->GetSkillTemplate(_skillId);
	if (skillTemp)
	{
		UCoolDown* cd = NewObject<UCoolDown>(UCoolDown::StaticClass());
		cd->AddToRoot();
		cd->SetSkillTemplate(skillTemp);
		cd->SetChar(mOwner);
		if (_isRestartCD)
			cd->Restart();

		USkillFunction* skillFunc = NewObject<USkillFunction>(cd, UCoolDown::StaticClass()); //设置USkillFunction跟随UCoolDown销毁
		if (skillFunc)
		{
			cd->mSkillFunc = skillFunc;
			cd->mSkillFunc->mSkillTemplate = skillTemp;
			cd->mSkillFunc->mType = _skillType;
			cd->mSkillFunc->mSkillId = _skillId;
		}

		//清楚旧的，加入新的
		RemoveCDByType(_skillType);
		mCDArr.Add(cd);
	}
	else
	{
		UE_LOG(UCoolDownLogger222, Warning, TEXT("--- Error: No USkillTemplate, mSkillId:%d"), _skillId);
	}
}
