// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDown.h"

#include "Char/MyChar.h"
#include "Char/Skill/Template/SkillTemplate.h"

DECLARE_LOG_CATEGORY_EXTERN(UCoolDownLogger222, Log, All);
DEFINE_LOG_CATEGORY(UCoolDownLogger222)

UCoolDown::UCoolDown() : Super()
{
	mSkillId = -1;
	mSkillTemplate = nullptr;
	mIsOK = true;
	mCDTime = 1.f;
	mTimer = 0.f;
	mType = ESkillType::Normal;
}

UCoolDown::~UCoolDown()
{
	UE_LOG(UCoolDownLogger222, Warning, TEXT("--- UCoolDown::~UCoolDown, skillId:%d"), mSkillId);
}

void UCoolDown::SetSkillTemplate(USkillTemplate * _skillTemplate)
{
	mSkillTemplate = _skillTemplate;
	mSkillId = mSkillTemplate->mId;
	mCDTime = mSkillTemplate->mCoolDown;
	mTimer = mCDTime;
	mIsOK = true;
}

void UCoolDown::UseSkill(AMyChar * _attActor, int32 _targetId)
{
	if (!_attActor || IsNull())
		return;

	//技能任务

}

void UCoolDown::Restart()
{
	mTimer = 0.f;
	mIsOK = false;
}

void UCoolDown::Tick(float DeltaTime)
{
	if (!mIsOK)
	{
		mTimer += DeltaTime;
		if (mTimer >= mCDTime)
		{
			mTimer = mCDTime;
			mIsOK = true;
			UE_LOG(UCoolDownLogger222, Warning, TEXT("--- CD isOK, skillId:%d"), mSkillId);
		}
	}
	else
		mTimer = mCDTime;
}
