#include "MySlate.h"
#include "BTServiceMyBase.h"

#include "../MyChar.h"
#include "../CharMgr.h"
#include "../Comp/MyCharDataComp.h"
#include "../CharData.h"
#include "./MyAIController.h"


UBTServiceMyBase::UBTServiceMyBase() : Super(), IBTNodeInterface()
{
	//设置每帧tick
	bNotifyTick = 1;
}

UBTServiceMyBase::~UBTServiceMyBase()
{
	UE_LOG(AILogger, Warning, TEXT("--- UBTServiceMyBase::~UBTServiceMyBase"));
}

void UBTServiceMyBase::TickNode(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

}

void UBTServiceMyBase::OnInstanceCreated(UBehaviorTreeComponent& OwnerComp)
{
	IBTNodeInterface::InitData(&OwnerComp);
}

void UBTServiceMyBase::OnInstanceDestroyed(UBehaviorTreeComponent& OwnerComp)
{

}

AMyChar* UBTServiceMyBase::GetCloestEnemy()
{
	//TODO:暂时先选择敌人
	ETeam dstType = gGetCharMgr()->GetDestTeam(mOwnerChar->GetTeamType(), ESelectType::Enemy); 
	float warnRange = mOwnerChar->GetDataComp()->GetCharhData()->mWarnRange;
	FVector loc = mOwnerChar->GetActorLocation();
	TArray<AMyChar*> dstChars;
	gGetCharMgr()->GetDstCharVec(dstType, warnRange, loc, dstChars);

	return gGetCharMgr()->GetCloseChar(dstChars, loc);
}

bool UBTServiceMyBase::IsAutoAI() const
{
	return GetController()->mAutoAI;
}

