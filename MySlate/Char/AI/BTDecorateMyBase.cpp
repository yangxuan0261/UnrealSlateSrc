#include "MySlate.h"
#include "BTDecorateMyBase.h"

#include "Char/AI/MyAIController.h"
#include "Char/MyChar.h"
#include "Char/Skill/CoolDown/CoolDownComp.h"
#include "Char/Skill/Template/SkillTemplate.h"
#include "Char/Skill/CoolDown/CoolDown.h"
#include "Char/AI/MyAIController.h"

DECLARE_LOG_CATEGORY_EXTERN(BTDecorateLogger, Log, All);
DEFINE_LOG_CATEGORY(BTDecorateLogger)

UBTDecorateMyBase::UBTDecorateMyBase()
	: Super()
{
	mOwnerChar = nullptr;
	mOwnerAI = nullptr;
	mBTComp = nullptr;

	//设置tick 开关
	bNotifyTick = true;
}

UBTDecorateMyBase::~UBTDecorateMyBase()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTDecorateMyBase::~UBTDecorateMyBase"));
}


void UBTDecorateMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

//初始化成员都放在这个方法
void UBTDecorateMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	mBTComp = &OwnerComp;
	mOwnerAI = mBTComp != nullptr ? Cast<AMyAIController>(mBTComp->GetOwner()) : nullptr;
	mOwnerChar = mOwnerAI != nullptr ? Cast<AMyChar>(mOwnerAI->GetPawn()) : nullptr;
}

void UBTDecorateMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

bool UBTDecorateMyBase::CanUseSkill()
{
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
	if (mOwnerChar->mCanUseSkillArr.Num() > 0)
	{
		//mOwnerChar->mCDComp->UseSkill(mOwnerChar->mCanUseSkillArr[0], 0);
	}
}

bool UBTDecorateMyBase::IsAttackRange()
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
				return skillTemp->mAttackDist > DistSq ? true : false;
			}
		}
		*/
	}

	return false;
}
