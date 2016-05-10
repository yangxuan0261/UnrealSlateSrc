
#include "MySlate.h"
#include "CoolDownComp.h"

#include "./CoolDown.h"
#include "../../MyChar.h"
#include "../SkillMgr.h"
#include "../Template/SkillTemplate.h"
#include "../SkillFunction.h"
#include "../../Object/ObjMgr.h"

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
		cd->Recycle();
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
			mCDArr[i]->Recycle();
			mCDArr.RemoveAt(i);
			UE_LOG(CompLogger, Warning, TEXT("--- UCoolDownComp::RemoveCDById, skillId:%d"), _skillId);
			return;
		}
	}
}

void UCoolDownComp::AddCD(int32 _skillId, bool _isRestartCD)
{
	USkillTemplate* skillTemp = USkillMgr::GetInstance()->GetSkillTemplate(_skillId);
	if (skillTemp)
	{
		//Çå³ý¾ÉµÄ
		RemoveCDById(_skillId);

		UCoolDown* cd = GetObjMgr()->GetObj<UCoolDown>(GetObjMgr()->mCoolDownCls);
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
