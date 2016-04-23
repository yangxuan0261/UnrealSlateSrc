#pragma once

#include "../SkillTypes.h"
#include "AbsFilter.generated.h"

/*
一般定义：
float		mValue; //数值
int32		mOwner; //所属者 -- 1:攻击者，-1:受击者
int32		mLimitId; //技能限制
*/

class AMyChar;
class UPkMsg;

UCLASS()
class UAbsFilter : public UObject
{
	GENERATED_BODY()

public:
	UAbsFilter();
	virtual ~UAbsFilter();
	virtual void BeginDestroy() override;

	virtual void Filter(UPkMsg* _msg, EFilterType _filterType = EFilterType::Locked, float _radius = 0.f, const FVector& _boxSize = FVector::ZeroVector); //过虑可选actor
	virtual UAbsFilter* Clone() { return nullptr; }
	virtual void Parser(const TArray<FString>& _params) {}//解释数据
	virtual void DebugDraw(const FVector& _start, const TArray<AMyChar*>& _targets);

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

public:
		FString		mKey;
		int32		mCount; //限制人数
		ESelectType	mSelectType;
		TArray<AMyChar*>	mDestChars; //目标集合
};
