#pragma once

#include "./AbsAttrFunc.h"
#include "AbsPkEvent.generated.h"

class UPkMsg;
class UAbsBuff;

UCLASS()
class UAbsPkEvent : public UAbsAttrFunc
{
	GENERATED_BODY()

public:
	struct PkInfo
	{
		PkInfo(int32 attId, int sId, int32 targetId, UAbsBuff* buff)
			:attUniqueId(attId)
			, skillId(sId)
			, targetUniqueId(targetId)
			, buffer(buff)
		{
		}

		uint32_t attUniqueId;	//buffer释放者
		int skillId;			//释放buffer的技能
		uint32_t targetUniqueId;//buffer所有者
		UAbsBuff* buffer;	//buffer
	};

public:
	UAbsPkEvent();
	virtual ~UAbsPkEvent();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	virtual UAbsPkEvent* Clone() { return nullptr; }

	virtual void RunBeforeSkill(UPkMsg* msg) {}
	virtual void RunBeforePk(UPkMsg* msg) {}
	virtual void RunBeforeEvns(UPkMsg* msg) {}
	virtual void RunEndEvns(UPkMsg* msg) {}
	virtual void RunEndPk(UPkMsg* msg) {}
	virtual void RunEndSkill(UPkMsg* msg) {}

	virtual void Parser(const TArray<FString>& _params) {}//解释数据

	FString		GetKey() const { return mKey; }
	void		SetKey(const FString& _key) { mKey = _key; }

protected:
	bool CheckPercent(const FString& _value);

protected:
	FString		mKey;
	bool		mIsPercent;
};
