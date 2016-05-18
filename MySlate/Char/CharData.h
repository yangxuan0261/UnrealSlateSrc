/*
角色基础数据
*/
#pragma once

#include "CharData.generated.h"

class UFightData;

UCLASS(Blueprintable)
class UCharData : public UObject
{
	GENERATED_BODY()
public:
	UCharData();
	virtual ~UCharData();
	virtual void BeginDestroy() override;

	void Init();
	UFightData*	GetFightData() const { return mFightData; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		int32		mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		FString		mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		FString		mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mHeath;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mHeathMax;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		float		mWarnRange;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharData")
		UFightData*	mFightData;
};
