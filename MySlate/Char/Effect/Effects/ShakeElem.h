
#pragma once

#include "../../Skill/SkillTypes.h"
#include "./BehavElem.h"
#include "ShakeElem.generated.h"

UCLASS(BlueprintType)
class UShakeElem : public UBehavElem //振动元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UShakeElem();
	virtual ~UShakeElem();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "UShakeElem")
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
		FVector		mLoc;
		FVector		mDtLoc;
		float		mRunTimer;
};