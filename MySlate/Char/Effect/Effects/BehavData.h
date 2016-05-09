
#pragma once

#include "../../Skill/SkillTypes.h"
#include "BehavData.generated.h"

class UEffDataElem;
class UShakeElem;

UCLASS()
class UBehavData : public UObject //特效集合
{
	GENERATED_BODY()
public:
	UBehavData();
	virtual ~UBehavData();
	virtual void BeginDestroy() override;
	void MyDestroy(TArray<UEffDataElem*>& _effectVec, TArray<UShakeElem*> _shakeVec);

	void Tick(float DeltaTime);
	UBehavData* Clone();
	TArray<UShakeElem*>&	GetTestShake() { return mAtkShkVec; } //TODO: 测试震动

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		int32		mId;//特效id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mAtkEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UShakeElem*>		mAtkShkVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mBltEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UShakeElem*>		mBltShkVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mTarEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UShakeElem*>		mTarShkVec;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UEffDataElem*>	mSceEffVec;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UBehavData")
		TArray<UShakeElem*>		mSceShkVec;
};
