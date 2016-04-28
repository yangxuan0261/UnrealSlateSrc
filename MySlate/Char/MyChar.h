// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "GameTypes.h"

#include "MyChar.generated.h"

class USMyAttachment;
class UCoolDownComp;
class UCoolDown;
class UMyCharDataComp;
class AMyBullet;
class USkillFunction;
class UCharMgr;
class UCharData;
class USkeletalMeshComponent;

DECLARE_MULTICAST_DELEGATE_OneParam(FDeathMultiNotify, AMyChar*);
DECLARE_DELEGATE_OneParam(FDeathOneNotify, AMyChar*);

USTRUCT()
struct FEffectBind
{
	GENERATED_USTRUCT_BODY()
public:
	FEffectBind() {}
	bool operator ==(const FEffectBind& _cp) //重载==操作符，TArray remove中需要用到
	{
		return mUuId == _cp.mUuId;
	}
	FEffectBind(int32 _id, int32 _uuid, FString _bindPos, FString _resPath, float _time) 
	{
		mEffectId = _id;
		mUuId = _uuid;
		mBindPos = _bindPos;
		mResPath = _resPath;
		mLeftTime = _time;
	}
	int32	mEffectId;
	int32	mUuId; //唯一识别，区分相同buff移除
	FString	mBindPos; //特效绑定点
	FString mResPath; //资源路径
	float	mLeftTime; //剩余时间
};

UCLASS()
class AMyChar : public ACharacter
{
	GENERATED_BODY()

public:
	AMyChar();
	virtual ~AMyChar();

	virtual void BeginPlay() override;
	virtual void Tick( float DeltaSeconds ) override;
	virtual void Destroyed() override; //用于释放成员，调用Destroy();会立即调用

public:
	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void	SetUuid(int32 _uuid) { mUuid = _uuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void	SetCharData(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		int32	GetUuid() const { return mUuid; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		IsAlive() const;

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		bool		UseSkill(int32 _skillId, int32 _targetId = 0, FVector _targetLoc = FVector::ZeroVector);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		SetUsingSkillNull() { mUsingSkill = nullptr; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		USkillFunction*	GetUsingSkill() const { return mUsingSkill; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		ChangeState(CharState _state);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		const CharState&	GetState() const { return mCharState; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual UMyCharDataComp* GetDataComp() const { return mDataComp; }

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		FaceToTargetLoc(const FVector& _targetLoc, bool _smooth = false);

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		void		Death();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar")
		void		OnDeath();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar") //临时播放特效用，攻击特效
		void		TempNotifyA();

	UFUNCTION(BlueprintImplementableEvent, Category = "MyChar") //临时播放特效用，受击特效
		void		TempNotifyB();

	UFUNCTION(BlueprintCallable, Category = "MyChar")
		virtual void Reset();

	void	OnCDFinish(UCoolDown* _cd);
	FDeathMultiNotify&	GetDeathMultiNotify() { return mDeathMultiNotify; }
	void	AddDeathNotify(const FDeathOneNotify& _notify);

	//特效
	void	AttachEffect(const FEffectBind& _effBind);
	void	DetachEffect(int32 _uuid);

public:
	/* 设置子弹蓝图类 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		TSubclassOf<AMyBullet> BulletClass;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UCoolDownComp*		mCDComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UMyCharDataComp*	mDataComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		USkillFunction*		mUsingSkill;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		CharState			mCharState;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		TArray<UCoolDown*>	mCanUseSkillArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		int32				mUuid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyChar")
		UCharData*			mCharData;

private:
	UCharMgr*		gCharMgr; //char 管理器
	FTimerHandle	mTimer;
	FVector			mTurnToLoc; //用来平滑旋转时保存目标Loc，因为用了内部函数lambda
	FRotator		mTurnToRot; //用来平滑旋转时保存目标Rotate,

	TArray<FEffectBind>	mEffects; //特效数组

	FDeathMultiNotify mDeathMultiNotify; //绑定： buff管理器等等
};
