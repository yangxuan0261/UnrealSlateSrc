// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDown.h"

#include "Char/MyChar.h"
#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillFunction.h"

UCoolDown::UCoolDown() : Super()
{
	mSkillId = -1;
	mSkillTemplate = nullptr;
	mSkillFunc = nullptr;
	mIsOK = true;
	mCDTime = 1.f;
	mTimer = 0.f;
	mRatio = 1.f;
	mOwnerChar = nullptr;
}

UCoolDown::~UCoolDown()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UCoolDown::~UCoolDown, skillId:%d"), mSkillId);
	if (mSkillFunc)
		mSkillFunc->RemoveFromRoot();
}

void UCoolDown::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = mSkillTemplate->mId;
	mCDTime = mSkillTemplate->mCoolDown;
	mTimer = mCDTime;
	mIsOK = true;

	USkillFunction* skillFunc = NewObject<USkillFunction>(UCoolDown::StaticClass()); //设置USkillFunction跟随UCoolDown销毁
	skillFunc->AddToRoot();
	if (skillFunc)
	{
		mSkillFunc = skillFunc;
		mSkillFunc->SetSkillTemplate(_skillTemp);
	}
}

void UCoolDown::SetChar(AMyChar * _owner)
{
	mOwnerChar = _owner;
	mCDFinishDlg.Unbind();
	mCDFinishDlg.BindUObject(_owner, &AMyChar::OnCDFinish);
}

void UCoolDown::UseSkill(AMyChar * _attActor, int32 _targetId)
{
	if (!_attActor || IsNull())
		return;

	//技能任务
	//_attActor->mUsingSkill = this; //设置当前使用着技能

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
		mTimer += DeltaTime * mRatio;
		if (mTimer >= mCDTime)
		{
			mTimer = mCDTime;
			mIsOK = true;

			if (mOwnerChar != nullptr)
			{
				mCDFinishDlg.ExecuteIfBound(this); //cd完通知char，可以释放技能了
			}
		}
	}
	else
		mTimer = mCDTime;
}
