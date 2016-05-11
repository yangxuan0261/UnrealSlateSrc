
#include "MySlate.h"
#include "MyAnimInstance.h"

#include "../MyChar.h"
#include "../MyBullet.h"
#include "../Skill/SkillFunction.h"
#include "../Skill/Template/SkillTemplate.h"

UMyAnimInstance::UMyAnimInstance()
{
	mOwnerChar = nullptr;
	mSpeed = 0.f;
	mCharState = CharState::IdleRun;
	mAnimType = EAnimType::None;

	mStateDlg.BindLambda([&](CharState _state)->void {
		mCharState = _state;
	});
}

UMyAnimInstance::~UMyAnimInstance()
{

}

bool UMyAnimInstance::IsMoving()
{
	return GetOwnerChar()->GetVelocity().Size() > 0.f ? true : false;
}

AMyChar* UMyAnimInstance::GetOwnerChar()
{
	if (!mOwnerChar)
	{
		APawn* owner = TryGetPawnOwner();
		mOwnerChar = owner ? Cast<AMyChar>(owner) : nullptr;
	}
	return mOwnerChar;
}

void UMyAnimInstance::SkillBegin()
{
	if (mOwnerChar != nullptr)
	{
		mOwnerChar->GetUsingSkill()->SkillBegin();
	}
}

void UMyAnimInstance::AnimNotify_BulletCreate(UAnimNotify * Notify)
{
	if (mOwnerChar != nullptr)
	{	//issue 不知道为啥，动画结束后还是会跑进来，先容错解决，待深究
		USkillFunction* skillFunc = mOwnerChar->GetUsingSkill();
		if (skillFunc != nullptr)
		{
			skillFunc->BulletCreate();
		}
	}
}

void UMyAnimInstance::AnimNotify_BulletShoot(UAnimNotify * Notify)
{
	if (mOwnerChar != nullptr)
	{
		USkillFunction* skillFunc = mOwnerChar->GetUsingSkill();
		if (skillFunc != nullptr)
		{
			skillFunc->BulletShoot();
		}
	}
}

void UMyAnimInstance::AnimNotify_SkillEnd(UAnimNotify* Notify)
{
	if (mOwnerChar != nullptr)
	{
		USkillFunction* skillFunc = mOwnerChar->GetUsingSkill();
		if (skillFunc != nullptr)
		{
			skillFunc->SkillEnd();
		}
	}
}

void UMyAnimInstance::SkillDataRelease()
{
	if (mOwnerChar != nullptr)
	{
		USkillFunction* skillFunc = mOwnerChar->GetUsingSkill();
		if (skillFunc != nullptr)
		{
			skillFunc->ReleaseData();
		}
	}
}

void UMyAnimInstance::AnimNotify_DeathOver(UAnimNotify* Notify)
{
	if (mOwnerChar != nullptr)
	{
		mOwnerChar->Destroy();
	}
}

void UMyAnimInstance::AnimNotify_Test(UAnimNotify* Notify)
{
	//if (mOwnerChar != nullptr)
	//{
	//	mSpeed = mOwnerChar->GetVelocity().Size(); //设置速度
	//	mCharState = mOwnerChar->mCharState; //设置动画状态
	//}
}

void UMyAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (mOwnerChar == nullptr)
	{
		mOwnerChar = GetOwnerChar();
	}

	if (mOwnerChar != nullptr)
	{	//TODO: 待优化，不变时不需要去get
		mSpeed = mOwnerChar->GetVelocity().Size(); //设置速度

		USkillFunction* skillFunc = mOwnerChar->GetUsingSkill();
		USkillTemplate* skillTemp = skillFunc != nullptr ? skillFunc->GetSkillTemplate() : nullptr;
		mAnimType = skillTemp != nullptr ? skillTemp->mAnimType : EAnimType::None; //设置动画类型
	}
}
