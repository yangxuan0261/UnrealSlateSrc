
#include "MySlate.h"
#include "AbsAttrFunc.h"

#include "../../../MyChar.h"

UAbsAttrFunc::UAbsAttrFunc() : Super(), IObjInterface()
{
	IObjInterface::SetObj(this);
}

UAbsAttrFunc::~UAbsAttrFunc()
{

}

void UAbsAttrFunc::BeginDestroy()
{
	Super::BeginDestroy();
}

void UAbsAttrFunc::Reset()
{
	mBuff = nullptr;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
}

void UAbsAttrFunc::Recycle()
{
	IObjInterface::Recycle();
}

void UAbsAttrFunc::SetData(UAbsBuff* _buff, AMyChar* _attacker, AMyChar* _owner)
{
	mBuff = _buff;
	mAttacker = _attacker;
	mOwnerChar = _owner;
}
