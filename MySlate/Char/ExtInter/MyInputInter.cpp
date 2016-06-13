#include "MySlate.h"
#include "MyInputInter.h"

#include "../MyChar.h"

UMyInputInterface::UMyInputInterface(const class FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

IMyInputInterface::IMyInputInterface()
{
	mOwnChar = nullptr;
	mAICtrl = nullptr;
}

void IMyInputInterface::SetChar(AMyChar* _target)
{
	mOwnChar = _target;
	AAIController* aiCtrl = Cast<AAIController>(_target->GetController());
	mAICtrl = aiCtrl;
	if (aiCtrl)
	{
		aiCtrl->GetPathFollowingComponent()->OnMoveFinished.AddUObject(_target, &IMyInputInterface::OnMoveCompleted);
	}
}

void IMyInputInterface::SetParticleVisible(bool _b)
{
	mOwnChar->mParticleComp->SetHiddenInGame(!_b);
}

void IMyInputInterface::MoveToDst(AMyChar* _target, const FVector& _loc, bool _isShift /* = false */)
{
	/*
	EPathFollowingStatus::Type moveState = mAICtrl->GetPathFollowingComponent()->GetStatus();
	UNavigationSystem* const NavSys = mOwnChar->GetWorld()->GetNavigationSystem();

	FVector dstLoc = _loc;
	if (_isShift)
	{
		mOperatorVec.Push(FOperator(FOpType::Move, _target, dstLoc));

		if (moveState == EPathFollowingStatus::Idle)
		{ }
	}
	else
	{
		if (moveState == EPathFollowingStatus::Moving)
			mOwnChar->GetController()->StopMovement();

		mOperatorVec.Empty();
		if (_target != nullptr)
		{
			NavSys->SimpleMoveToActor(mOwnChar->GetController(), _target);
		}
		{
			NavSys->SimpleMoveToLocation(mOwnChar->GetController(), _loc);
		}
	}

	if (moveState == EPathFollowingStatus::Moving)
	{
		if (!_isShift)
		{
			mOwnChar->GetController()->StopMovement();
			NavSys->SimpleMoveToLocation(mOwnChar->GetController(), _loc);
			
		}

	}
	else if (moveState == EPathFollowingStatus::Idle)
	{
	}
	*/

	if (mOwnChar->GetCharacterMovement()->Velocity.Size() > 0.f)
	{
		mOwnChar->GetController()->StopMovement();
	}

	UNavigationSystem* const NavSys = mOwnChar->GetWorld()->GetNavigationSystem();
	if (NavSys != nullptr)
	{
		NavSys->SimpleMoveToLocation(mOwnChar->GetController(), _loc);
	}
}

void IMyInputInterface::AttackTarget(AMyChar* _target, int32 _skillId /* = 0 */, bool _isShift /* = false */)
{
	if (mOwnChar->mUsingSkill != nullptr) //技能使用中则取消
	{
		mOwnChar->mUsingSkill->CancelSkill();
	}

	if (_skillId > 0)
	{
		mOwnChar->UseSkill(_skillId, _target, _target->GetActorLocation());
	}
	else
	{	//默认使用cd完的技能， pop出来
		if (mOwnChar->mCanUseSkillVec.Num() > 0)
		{
			UCoolDown* cd = mOwnChar->mCanUseSkillVec.Pop();
			USkillFunction* skillFunc = cd->GetSkillFunc();
			mOwnChar->UseSkill(skillFunc->GetSkillId(), _target, _target->GetActorLocation());
		}
	}
}

void IMyInputInterface::OnMoveCompleted(FAIRequestID RequestID, EPathFollowingResult::Type MovementResult)
{
	UE_LOG(SkillLogger, Warning, TEXT("-- IMyInputInterface::OnMoveCompleted:%d"), (int32)MovementResult);

	EPathFollowingStatus::Type moveState = mAICtrl->GetPathFollowingComponent()->GetStatus();
	UE_LOG(GameLogger, Warning, TEXT("--- IMyInputInterface::MoveToDst, state = %d"), (int32)moveState);
}
