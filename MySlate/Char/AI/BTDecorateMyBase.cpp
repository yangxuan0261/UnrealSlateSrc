#include "MySlate.h"
#include "BTDecorateMyBase.h"

#include "Char/AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/Skill/CoolDown/CoolDownComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/CoolDown/CoolDown.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UBTDecorateMyBase::UBTDecorateMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mBTComp = nullptr;
}

UBTDecorateMyBase::~UBTDecorateMyBase()
{

}

void UBTDecorateMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	if (!mOwnerChar)
		mOwnerChar = GetMyChar();
}

AMyChar* UBTDecorateMyBase::GetMyChar()
{
	AMyChar* myChar = Cast<AMyChar>(AIOwner->GetPawn());
	return myChar != nullptr ? myChar : nullptr;
}



UBehaviorTreeComponent* UBTDecorateMyBase::GetBTComp()
{
	UBehaviorTreeComponent* btComp = Cast<UBehaviorTreeComponent>(AIOwner->GetBrainComponent());
	return btComp != nullptr ? btComp : nullptr;
}

bool UBTDecorateMyBase::CanUseSkill()
{
	if (!mOwnerChar)
		mOwnerChar = GetMyChar();

	if (!mOwnerChar)
		return false;

	if (mOwnerChar->mCharState != CharState::Attack) //不在攻击状态且有可放的技能
	{
		if (mOwnerChar->mCanUseSkillArr.Num() > 0)
		{
			return true;
		}
	}
	return false;
}

void UBTDecorateMyBase::UseSkill()
{
	if (!mOwnerChar)
		mOwnerChar = GetMyChar();

	if (mOwnerChar->mCanUseSkillArr.Num() > 0)
	{
		mOwnerChar->mCDComp->UseSkill(mOwnerChar->mCanUseSkillArr[0], 0);
	}

}

bool UBTDecorateMyBase::IsAttackRange()
{
	if (!mOwnerChar)
		mOwnerChar = GetMyChar();

	if (!mBTComp)
		mBTComp = GetBTComp();

	if (mOwnerChar->mUsingSkill != nullptr)
	{
		USkillTemplate* skillTemp = mOwnerChar->mUsingSkill->mSkillTemplate;


		UBlackboardComponent* BlackboardComp = mBTComp->GetBlackboardComponent();
		if (BlackboardComp)
		{
			int32 EnemyKeyID = BlackboardComp->GetKeyID("Enemy");
			AMyChar* enemy = Cast<AMyChar>(BlackboardComp->GetValue<UBlackboardKeyType_Object>(EnemyKeyID));
			if (enemy)
			{
				const float DistSq = (enemy->GetActorLocation() - mOwnerChar->GetActorLocation()).Size();
				return skillTemp->mAttackDist > DistSq ? true : false;
			}
		}
		
	}

	return false;
}
