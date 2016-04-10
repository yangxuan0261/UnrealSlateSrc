#include "MySlate.h"
#include "BTTaskMyBase.h"

#include "Char/AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/Skill/CoolDown/CoolDownComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/CoolDown/CoolDown.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTTaskMyBase::UBTTaskMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mBTComp = nullptr;
}

UBTTaskMyBase::~UBTTaskMyBase()
{

}

AMyChar* UBTTaskMyBase::GetMyChar()
{
	AMyChar* myChar = Cast<AMyChar>(AIOwner->GetPawn());
	return myChar != nullptr ? myChar : nullptr;
}



UBehaviorTreeComponent* UBTTaskMyBase::GetBTComp()
{
	UBehaviorTreeComponent* btComp = Cast<UBehaviorTreeComponent>(AIOwner->GetBrainComponent());
	return btComp != nullptr ? btComp : nullptr;
}

bool UBTTaskMyBase::MoveToTarget()
{
	if (!mOwnerChar)
		mOwnerChar = GetMyChar();

	if (!mBTComp)
		mBTComp = GetBTComp();


	if (mOwnerChar->mUsingSkill != nullptr)
	{
		/* 
		USkillTemplate* skillTemp = mOwnerChar->mUsingSkill->mSkillTemplate;


		UBlackboardComponent* BlackboardComp = mBTComp->GetBlackboardComponent();
		if (BlackboardComp)
		{
			int32 EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
			AMyChar* enemy = Cast<AMyChar>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
			if (enemy)
			{
				const float DistSq = (enemy->GetActorLocation() - mOwnerChar->GetActorLocation()).Size();
				if (skillTemp->mAttackDist > DistSq)
				{
					return true;
				}
				else
				{
					AIOwner->MoveToActor(enemy, skillTemp->mAttackDist - 1.f); //不在攻击范围内就一直移动
				}
			}
		}
		*/

	}
	return false;
}

