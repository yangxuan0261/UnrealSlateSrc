
#include "MySlate.h"
#include "SkillDataMgr.h"

#include "../../../Common/CommonHeader.h"
#include "../Template/SkillTemplate.h"
#include "../Template/BufflTemplate.h"
#include "../SkillTypes.h"

USkillDataMgr::USkillDataMgr() : Super()
{

}

USkillDataMgr::~USkillDataMgr()
{
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::~USkillDataMgr"));
}

void USkillDataMgr::BeginDestroy()
{
	for (TMap<int32, USkillTemplate*>::TConstIterator iter = mSkillTempMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mSkillTempMap.Empty();

	for (TMap<int32, UBufflTemplate*>::TConstIterator iter = mBuffTempMap.CreateConstIterator(); iter; ++iter)
	{
		iter->Value->RemoveFromRoot();
		iter->Value->ConditionalBeginDestroy();
	}
	mBuffTempMap.Empty();

	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- USkillDataMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void USkillDataMgr::InitFakeDate()
{
	//USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	//skill1->mId = 10001;
	//skill1->mName = TEXT("Skill1 Name");
	//skill1->mDescr = TEXT("Skill1 Descr");
	//skill1->mCoolDown = 3;
	//skill1->mLockedType = ELockedType::Char;
	//skill1->mAttackDist = 100;
	//skill1->mTolerance = 5;
	//skill1->mBulletSpeed = 400;
	//skill1->mFlyDist = 0;
	//skill1->mSkillType = ESkillType::Normal;
	//skill1->mFilterStr = TEXT("circle,0,-1,500");
	//skill1->mAttachPoint = TEXT("BulletPos");
	//skill1->mAnimType = EAnimType::Skill_1;

	//USkillTemplate* skill2 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	//skill2->mId = 10002;
	//skill2->mName = TEXT("Skill2 Name");
	//skill2->mDescr = TEXT("Skill2 Descr");
	//skill2->mCoolDown = 7;
	//skill2->mLockedType = ELockedType::Loc;
	//skill2->mAttackDist = 50;
	//skill2->mTolerance = 5;
	//skill2->mBulletSpeed = 5;
	//skill2->mFlyDist = 50;
	//skill2->mSkillType = ESkillType::Initiative;
	//skill2->mFilterStr = TEXT("circle,0,-1,500");
	//skill2->mAttachPoint = TEXT("BulletPos");
	//skill2->mAnimType = EAnimType::Skill_2;

	//USkillTemplate* skill3 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	//skill3->mId = 10003;
	//skill3->mName = TEXT("Skill3 Name");
	//skill3->mDescr = TEXT("Skill3 Descr");
	//skill3->mCoolDown = 5;
	//skill3->mLockedType = ELockedType::Char;
	//skill3->mAttackDist = 80;
	//skill3->mTolerance = 5;
	//skill3->mBulletSpeed = 5;
	//skill3->mFlyDist = 0;
	//skill3->mSkillType = ESkillType::Initiative;
	//skill3->mFilterStr = TEXT("circle,0,-1,200");
	//skill3->mAttachPoint = TEXT("lhand");
	//skill3->mAnimType = EAnimType::Skill_3;
}

USkillTemplate* USkillDataMgr::CreateSkillTemp(int32 _id)
{
	USkillTemplate* skill1 = NewObject<USkillTemplate>(USkillTemplate::StaticClass());
	skill1->mId = _id;
	//USkillTemplate** skillTemp = mSkillTempMap.Find(_skillTemp->mId); //
	//if (skillTemp != nullptr)
	//{
	//	UE_LOG(GolbalFuncLogger, Error, TEXT("--- USkillDataMgr::AddSkillTemp, add same id data, id:%"), skillTemp->mId);
	//	return;
	//}
	skill1->AddToRoot();
	mSkillTempMap.Add(skill1->mId, skill1);
	return skill1;
}

UBufflTemplate* USkillDataMgr::CreateBuffTemp(int32 _id)
{
	UBufflTemplate* buff1 = NewObject<UBufflTemplate>(UBufflTemplate::StaticClass());
	buff1->mId = _id;
	buff1->AddToRoot();
	mBuffTempMap.Add(buff1->mId, buff1);
	return buff1;
}

USkillTemplate * USkillDataMgr::GetSkillTemplate(int32 _skillId)
{
	USkillTemplate** tempPtr = mSkillTempMap.Find(_skillId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}

UBufflTemplate * USkillDataMgr::GetBuffTemplate(int32 _buffId)
{
	UBufflTemplate** tempPtr = mBuffTempMap.Find(_buffId);
	return tempPtr != nullptr ? *tempPtr : nullptr;
}


