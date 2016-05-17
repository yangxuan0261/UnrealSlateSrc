
#include "MySlate.h"
#include "MyChar.h"

#include "./Skill/CoolDown/CoolDownComp.h"
#include "./Skill/CoolDown/CoolDown.h"
#include "./Skill/SkillFunction.h"
#include "./Comp/MyCharDataComp.h"
#include "./AI/MyAIController.h"
#include "./CharMgr.h"
#include "./CharData.h"
#include "./Skill/Buff/BuffMgr.h"
#include "./Effect/Effects/BehavElem.h"

AMyChar::AMyChar() : Super()
{
	PrimaryActorTick.bCanEverTick = true;

	//--------- 
	gCharMgr = nullptr;
	mCDComp = nullptr;
	mDataComp = nullptr;
	mUsingSkill = nullptr;
	mCharState = CharState::IdleRun;
	mUuid = 0;
	mCharData = nullptr;
	mTurnToLoc = FVector::ZeroVector;
	mAnimation = nullptr;
}

AMyChar::~AMyChar()
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::~AMyChar"));
}

void AMyChar::BeginPlay()
{
	Super::BeginPlay();
	gCharMgr = gGetCharMgr();

	//设置默认AI控制类，并生成一下
	AIControllerClass = AMyAIController::StaticClass();
	SpawnDefaultController();

	//注册cd组件
	mCDComp = NewObject<UCoolDownComp>(this, TEXT("CDComponent"));
	mCDComp->RegisterComponent();
	mCDComp->SetOwner(this);

	//注册data组件
	mDataComp = NewObject<UMyCharDataComp>(this, TEXT("CharDataComponent"));
	mDataComp->RegisterComponent();

	//绑定buff管理器
	mDeathMultiNotify.Add(FDeathOneNotify::CreateUObject(gGetBuffMgr(), &UBuffMgr::CharDeathNotify));
	//GetMesh()->SetSkeletalMesh(nullptr);

	//动画实例
	mAnimation = Cast<UMyAnimInstance>(GetMesh()->GetAnimInstance());
	if (mAnimation != nullptr)
	{
		UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::BeginPlay, UMyAnimInstance load success"));
	}
}

void AMyChar::Tick( float DeltaTime )
{
	AActor::Tick( DeltaTime );
	IBehavInterface::BehavTick(DeltaTime);

	if (mCDComp != nullptr)
	{
		mCDComp->MyTick(DeltaTime);
	}

	if (mUsingSkill != nullptr)
	{
		mUsingSkill->Tick(DeltaTime);
	}
}	

void AMyChar::Destroyed()
{

	if (mCDComp != nullptr)
	{
		mCDComp->DestroyComponent();
		mCDComp = nullptr;
	}

	if (mDataComp != nullptr)
	{
		mDataComp->DestroyComponent();
		mDataComp = nullptr;
	}

	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::Destroyed"));
	Super::Destroyed();
}

void AMyChar::OnCDFinish(UCoolDown* _cd)
{
	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::OnCDFinish, skillId:%d"), _cd->GetSkillId());
	mCanUseSkillArr.AddUnique(_cd);
}

void AMyChar::AddDeathNotify(const FDeathOneNotify& _notify)
{
	mDeathMultiNotify.Add(_notify);
}

void AMyChar::SetCharData(int32 _id)
{
	mDataComp->SetCharData(_id);
}

bool AMyChar::IsAlive() const
{
	return mDataComp->mHealth > 0.f ? true : false;
}

bool AMyChar::UseSkill(int32 _skillId, int32 _targetId /* = 0 */, FVector _targetLoc /* = FVector::ZeroVector */)
{
	bool canUse = false;
	if (mUsingSkill == nullptr)
	{	
		//可以容错，但不是必须，因为使用技能是目标肯定是存在的
		//AMyChar* target = _targetId > 0 ? gGetCharMgr()->GetChar(_targetId) : nullptr;
		//if (target == nullptr)
		//{
		//	return canUse;
		//}

		AMyChar* target = gGetCharMgr()->GetChar(_targetId);

		USkillFunction* skillFunc = mCDComp->CanUseSkill(_skillId);
		if (skillFunc != nullptr)
		{
			skillFunc->UseSkill(target, _targetLoc);
			mUsingSkill = skillFunc;
			canUse = true;
		}
	}		
	else
	{
		UE_LOG(SkillLogger, Error, TEXT("--AMyChar::Turing- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	}

	return canUse;
}

void AMyChar::ChangeState(CharState _state)
{
	UE_LOG(GameLogger, Warning, TEXT("--- AMyChar::ChangeState, state = %s"), *GetEnumAsString("CharState", _state));
	mCharState = _state;
	if (mAnimation != nullptr)
	{
		mAnimation->mStateDlg.ExecuteIfBound(_state);
	}
	//for test
	//USkillFunction* sdf = GetUsingSkill();
	//bool b = sdf != nullptr ? sdf->CanAttack() : false;
	//if (b)
	//{
	//	UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::UseSkill, mUsingSkill != nullptr, skillId:%d"), mUsingSkill->mSkillId);
	//}
}

void AMyChar::FaceToTargetLoc(const FVector& _targetLoc, bool _smooth /* = false */)
{
	if (!_smooth)
	{
		SetActorRotation(
			UKismetMathLibrary::FindLookAtRotation(
				GetActorLocation()
				, _targetLoc)
			);
	}
	else //平滑旋转
	{
		mTurnToLoc = _targetLoc;
		mTurnToRot = FRotator::ZeroRotator;

		auto rotaInterp = [&]() -> void{
			mTurnToRot = UKismetMathLibrary::RInterpTo(
				GetActorRotation()
				, UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), mTurnToLoc)
				, GetWorld()->GetDeltaSeconds()
				, 10.f);

			if (GetActorRotation().Equals(mTurnToRot, 1.f))
			{
				this->GetWorldTimerManager().ClearTimer(mTimer); //清理定时器
				UE_LOG(SkillLogger, Warning, TEXT("--- AMyChar::FaceToTargetLoc, stop rotate"));
			}
			else
			{
				SetActorRotation(mTurnToRot);
			}
		};

		GetWorldTimerManager().SetTimer(mTimer, FTimerDelegate::CreateLambda(rotaInterp), GetWorld()->GetDeltaSeconds(), true); //设置定时器
	}
}

void AMyChar::Death()
{
	mDeathMultiNotify.Broadcast(this);//通知所有绑定了的代理
	IBehavInterface::RemoveBehavElemAll();

	//施放技能中被打死，释放创建的子弹和pkMsg
	if (mUsingSkill != nullptr)
	{
		mUsingSkill->ReleaseData();
		mUsingSkill = nullptr;
	}

	//TODO: 从管理器中移除，这里应该做回收，而不是销毁，暂时先销毁
	gCharMgr->RemoveChar(mUuid);

	OnDeath(); //通知一下蓝图

	ChangeState(CharState::Death);//等动画状态机通知销毁
}

void AMyChar::Reset()
{

}