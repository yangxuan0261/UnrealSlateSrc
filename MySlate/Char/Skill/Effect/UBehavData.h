
#pragma once

#include "UBehavData.generated.h"

UENUM()
enum class ESkillEffectType : uint8 //特效类型
{
	SelfFollow = 0,
	SelfUnfollow,
	TargetFollow,
	TargetUnfollow,
	Bullet,
	SceneCamera,
	Count,
};

UCLASS()
class UEffDataElem : public UObject //特效元素
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;

	int32		mId;					//特效id
	ESkillEffectType	mEffectType;	//特效类型
	FString		mBindPoint;				//绑定骨骼
	float		mDelayTime;			//延时时长
	FVector		mLoc;					//矩阵信息
	FVector		mScale;
	FRotator	mRotate;
};

UCLASS()
class UBehavData : public UObject //特效集合
{
	GENERATED_BODY()
public:
	UBehavData();
	virtual ~UBehavData();
	virtual void BeginDestroy() override;

	void Tick(float DeltaTime);
	TArray<UEffDataElem*>&	GetEffElems() { return mEffElems; }

	void loadEffecs();
public:
	int32		mId;//特效id
	TArray<UEffDataElem*>	mEffElems; //特效集
};
