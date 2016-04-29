
#pragma once

#include "../../../Common/CommonHeader.h"
#include "../SkillTypes.h"

#include "BufflTemplate.generated.h"

class UAbsPkEvent;

UCLASS(Blueprintable)
class UBufflTemplate : public UObject
{
	GENERATED_BODY()

public:
	UBufflTemplate();
	virtual ~UBufflTemplate();
	virtual void BeginDestroy() override;

	TArray<UAbsPkEvent*>& GetAttrs();
	TArray<UAbsPkEvent*>& GetBeforePk();
	TArray<UAbsPkEvent*>& GetEndPk();

	void ParseFuncStr(const FString& _funcStr, TArray<UAbsPkEvent*>& _funcArr);

public:
	TArray<UAbsPkEvent*> mAttrs;
	TArray<UAbsPkEvent*> mBeforePk;
	TArray<UAbsPkEvent*> mEndPk;

public:
	//读表属性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mId;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mDescr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mBuffTime; //持续时间
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		bool			mCanDisperse; //是否驱散
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		bool			mCanAdd; //可否缀加
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		EIntervalType	mInterType; //buff周期性
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBindPos; //特效绑定点
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		int32			mBehavDataId; //表现数据id

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mAttrsStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mBeforePkStr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "USkillTemplate")
		FString			mEndPkStr;
};
