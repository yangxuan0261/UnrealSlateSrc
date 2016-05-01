
#include "MySlate.h"
#include "AbsAttrFunc.h"

#include "../../../MyChar.h"

UAbsAttrFunc::UAbsAttrFunc() : Super()
{
	mBuff = nullptr;
	mAttacker = nullptr;
	mOwnerChar = nullptr;
}

UAbsAttrFunc::~UAbsAttrFunc()
{

}

void UAbsAttrFunc::BeginDestroy()
{
	Super::BeginDestroy();
}

void UAbsAttrFunc::SetData(UAbsBuff* _buff, AMyChar* _attacker, AMyChar* _owner)
{
	mBuff = _buff;
	mAttacker = _attacker;
	mOwnerChar = _owner;
}
