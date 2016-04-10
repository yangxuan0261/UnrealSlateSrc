#include "MySlate.h"
#include "BTTaskMyBase.h"

#include "Char/MyChar.h"
#include "Char/AI/MyAIController.h"
#include "Char/Skill/CoolDown/CoolDownComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/CoolDown/CoolDown.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

DECLARE_LOG_CATEGORY_EXTERN(BTDTaskLogger, Log, All);
DEFINE_LOG_CATEGORY(BTDTaskLogger)

UBTTaskMyBase::UBTTaskMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;

	//设置每帧tick
	bNotifyTick = 1;
}

UBTTaskMyBase::~UBTTaskMyBase()
{

}

void UBTTaskMyBase::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
}

void UBTTaskMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	mBTComp = &OwnerComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

void UBTTaskMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

bool UBTTaskMyBase::MoveToTarget()
{
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

