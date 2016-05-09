
#pragma once

#include "../../Skill/SkillTypes.h"
#include "BehavElem.generated.h"

class UBehavElem;
class IBehavInterface;

DECLARE_DELEGATE_OneParam(FBehavElemDlg, UBehavElem*);

UENUM()
enum class EElemState : uint8 //特效状态
{
	Idle = 0,
	Start,
	Delay,
	Ticking,
	Over,
};

UCLASS(BlueprintType)
class UBehavElem : public UObject //振动元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UBehavElem();
	virtual ~UBehavElem();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime);
	virtual void Start();
	virtual void SetActor(IBehavInterface* _actor);

	void AddOverDlg(FBehavElemDlg _dlg);
	void MyDestroy(bool _needNotify = true);

public:
	int32		mGroupId;		//特效组id，每一次behav都分配一个mGroupId，以便索引删除

protected:
	IBehavInterface*	mTarget;				//振动者
	float		mDelayer;
	float		mDelayTime;
	EElemState	mState;
	FBehavElemDlg	mOverDlg;
};

UCLASS(BlueprintType)
class UShakeElem : public UBehavElem //振动元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UShakeElem();
	virtual ~UShakeElem();
	virtual void BeginDestroy() override;

	virtual void Tick(float DeltaTime) override;
	virtual void Start() override;

	UShakeElem* Clone();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		int32		mA;						//振幅
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mW;						//角速度
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mTime;					//持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FEffElemInfo")
		bool		mIsX;					//X方向
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;				//所属者
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;				//延时时长

private:
		AActor*		mTarget;				//振动者
		FVector		mLoc;
		FVector		mDtLoc;
		float		mRunTimer;
};

UCLASS(BlueprintType)
class UEffDataElem : public UBehavElem //特效元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;
	
	virtual void Tick(float DeltaTime) override;
	virtual void Start() override;

	void SetData(UParticleSystemComponent* _psComp);
	void OnCompleted(UParticleSystemComponent* _psComp);
	UEffDataElem* Clone();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mResId;					//粒子资源id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EOwnType	mOwnType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		EFollowType	mFollowType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FString		mBindPoint;				//绑定骨骼
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		float		mDelayTime;			//延时时长
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mLoc;					//矩阵信息
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FVector		mScale;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		FRotator	mRotate;

private:
	UParticleSystemComponent*	mPsComp;
};