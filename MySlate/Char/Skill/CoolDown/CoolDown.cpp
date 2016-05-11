
#include "MySlate.h"
#include "CoolDown.h"

#include "../../MyChar.h"
#include "../Template/SkillTemplate.h"
#include "../SkillFunction.h"
#include "../../CharMgr.h"
#include "../../Object/ObjMgr.h"

UCoolDown::UCoolDown() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UCoolDown::~UCoolDown()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UCoolDown::~UCoolDown"));
}

void UCoolDown::BeginDestroy()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- UCoolDown::BeginDestroy, skillId:%d"), mSkillId);
	Super::BeginDestroy();
}

void UCoolDown::Reset()
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

void UCoolDown::Recycle()
{
	if (mSkillFunc != nullptr)
	{
		mSkillFunc->Recycle();
		mSkillFunc = nullptr;
	}

	IObjInterface::Recycle();
}

void UCoolDown::SetSkillTemplate(USkillTemplate* _skillTemp)
{
	mSkillTemplate = _skillTemp;
	mSkillId = mSkillTemplate->mId;
	mCDTime = (float)mSkillTemplate->mBltElem->mCoolDown;
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
		USkillFunction* skillFunc = GetObjMgr()->GetObj<USkillFunction>(GetObjMgr()->mSkillFuncCls); //设置USkillFunction跟随UCoolDown销毁
		skillFunc->AddToRoot();
		skillFunc->SetCD(this);//使用技能时需要重置这个cd，故丢进this指针
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
