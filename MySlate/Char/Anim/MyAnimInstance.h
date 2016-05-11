
#pragma once

#include "../GameTypes.h"
#include "../Skill/SkillTypes.h"
#include "MyAnimInstance.generated.h"

class AMyChar;
class USkillTemplate;
class UMyAnimInstance;

DECLARE_DELEGATE_OneParam(FStateNotify, CharState); 

UCLASS()
class UMyAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMyAnimInstance();
	virtual ~UMyAnimInstance();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		bool IsMoving();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		AMyChar* GetOwnerChar();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void SkillBegin();

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_BulletCreate(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_BulletShoot(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_SkillEnd(UAnimNotify* Notify); //动画正常结束

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void SkillDataRelease(); //技能动画被打断，释放资源，从技能状态切换到其他状态一定会调用的方法

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_DeathOver(UAnimNotify* Notify);

	UFUNCTION(BlueprintCallable, Category = "UMyAnimInstance")
		void AnimNotify_Test(UAnimNotify* Notify);

	virtual	void NativeUpdateAnimation(float DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		AMyChar*	mOwnerChar;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		float		mSpeed;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		CharState	mCharState;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UMyAnimInstance")
		EAnimType	mAnimType;

	FStateNotify	mStateDlg;
};
