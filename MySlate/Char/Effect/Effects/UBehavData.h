
#pragma once

#include "../../Skill/SkillTypes.h"
#include "UBehavData.generated.h"

UCLASS(BlueprintType)
class UEffDataElem : public UObject //特效元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UEffDataElem();
	virtual ~UEffDataElem();
	virtual void BeginDestroy() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		int32		mResId;					//粒子资源id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UEffDataElem")
		ESkillEffectType	mEffectType;	//特效类型
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
	TArray<UEffDataElem*>&	GetEffElems(); 
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		int32		mId;//特效id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mEffElemVec; //特效集
};
