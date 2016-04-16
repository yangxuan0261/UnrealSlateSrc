// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "CoolDown.h"

#include "Char/MyChar.h"
#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/Template/BufflTemplate.h"
#include "Char/Skill/SkillFunction.h"
#include "Char/CharMgr.h"

UCoolDown::UCoolDown() : Super()
{
	mSkillId = 0;
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
	{
		mSkillFunc->RemoveFromRoot();
		mSkillFunc = nullptr;
	}
}

void UCoolDown::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = mSkillTemplate->mId;
	mCDTime = mSkillTemplate->mCoolDown;
	mTimer = mCDTime;
	mIsOK = true;

	USkillFunction* skillFunc = GetSkillFunc();
	if (skillFunc)
	{
		skillFunc->SetSkillTemplate(_skillTemp);
	}
}

USkillFunction* UCoolDown::GetSkillFunc()
{
	if (mSkillFunc == nullptr)
	{
		USkillFunction* skillFunc = NewObject<USkillFunction>(UCoolDown::StaticClass()); //设置USkillFunction跟随UCoolDown销毁
		skillFunc->AddToRoot();
		mSkillFunc = skillFunc;
	}
	return mSkillFunc;
}

void UCoolDown::SetChar(AMyChar* _char)
{
	mOwnerChar = _char;
	if (mOwnerChar != nullptr)
	{
		mCDFinishDlg.Unbind();
		mCDFinishDlg.BindUObject(mOwnerChar, &AMyChar::OnCDFinish);

		USkillFunction* skillFunc = GetSkillFunc();
		if (skillFunc)
		{
			skillFunc->SetAttacker(mOwnerChar);
			if (mSkillTemplate)
			{
				skillFunc->SetSkillTemplate(mSkillTemplate);
			}
			else
			{
				UE_LOG(SkillLogger, Error, TEXT("--- UCoolDown::SetChar, must call UCoolDown::SetSkillTemplate before this"), mSkillId);
			}
		}
	}
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
			mCDFinishDlg.ExecuteIfBound(this); //cd完通知char，可以释放技能了
		}
	}
	else
		mTimer = mCDTime;
}
