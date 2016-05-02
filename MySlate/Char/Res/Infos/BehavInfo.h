
#pragma once

#include "Engine/DataTable.h"
#include "BehavInfo.generated.h"

USTRUCT(Blueprintable)
struct FBehavInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FBehavInfo();
	virtual ~FBehavInfo();

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		int32		mId;//表现id
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FBehavInfo")
		FString		mEffIdsStr;//特效集
};
