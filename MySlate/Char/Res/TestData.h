
#pragma once

#include "Engine/DataTable.h"
#include "TestData.generated.h"


USTRUCT(Blueprintable)
struct FTestData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()
public:
	FTestData();
	virtual ~FTestData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTestData")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTestData")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FTestData")
		FString			mDescr;
};
