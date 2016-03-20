
#pragma once
#define  GetProperty(Var, VarName, Cate) \
UFUNCTION(BlueprintCallable, Category = #Cate) \
auto Get##VarName() const ->decltype(Var) \
{ return Var;}

#define  SetProperty(Var, VarName, Cate) \
UFUNCTION(BlueprintCallable, Category = #Cate) \
void Set##VarName(decltype(Var) _v) \
{ Var = _v;}

#define  GetSetProperty(Var, VarName, Cate)\
	GetProperty(Var, VarName, Cate)\
	SetProperty(Var, VarName, Cate)


//usage:
//UE_LOG(MyLogger, Warning, TEXT("--- key:%d, value222:%s "),
//	iter->Key, *iter->Value);