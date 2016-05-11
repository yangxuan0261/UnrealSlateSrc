
#pragma once

#include "../../Skill/SkillTypes.h"
#include "../../Object/ObjInter.h"
#include "BehavElem.generated.h"

class UBehavElem;
class IBehavInterface;

DECLARE_DELEGATE_OneParam(FBehavElemDlg, UBehavElem*);

UENUM()
enum class EElemState : uint8 //特效状态
{
	Idle = 0,
	Start,
	Delay,
	Ticking,
	Over,
};

UCLASS(BlueprintType)
class UBehavElem : public UObject, public IObjInterface //振动元素，给特效编辑器编辑的数据
{
	GENERATED_BODY()
public:
	UBehavElem();
	virtual ~UBehavElem();
	virtual void BeginDestroy() override;
	virtual void Reset() override;

public:
	virtual void Tick(float DeltaTime);
	virtual void Start();
	virtual void SetActor(IBehavInterface* _actor);
	virtual void MyDestroy(bool _needNotify = true);

	void AddOverDlg(FBehavElemDlg _dlg);
	EElemState	GetElemState() const { return mState; }

public:
	int32		mGroupId;		//特效组id，每一次behav都分配一个mGroupId，以便索引删除

protected:
	IBehavInterface*	mTarget;				//振动者
	float		mDelayer;
	float		mDelayTime;
	EElemState	mState;
	FBehavElemDlg	mOverDlg;
};
