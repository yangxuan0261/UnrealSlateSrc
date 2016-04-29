#pragma once

#include "CommonDef.generated.h"

//UEmpty只是为了引入引擎的类，比如FString
UCLASS()
class UEmpty : public UObject
{
	GENERATED_BODY()

public:
	UEmpty() {}
	virtual ~UEmpty() {}
};

#define  Split_Com		TEXT(",")
#define  Split_Line		TEXT("_")
#define  Split_Pound	TEXT("#")
#define  Split_Sem		TEXT(";")

#define  GetProperty(Var,VarName) inline auto Get##VarName() const ->decltype(Var) { return Var;}
#define  SetProperty(Var,VarName) inline void Set##VarName(decltype(Var) _v){ Var = _v;}
#define  GetSetProperty(Var,VarName)\
	GetProperty(Var, VarName)\
	SetProperty(Var, VarName)