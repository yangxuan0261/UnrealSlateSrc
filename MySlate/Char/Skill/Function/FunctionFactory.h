// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"
#include "FunctionFactory.generated.h"

//== 选人 A ==
#define Filter_Lock			TEXT("lock")
#define Filter_Rect			TEXT("rect")
#define Filter_Circle		TEXT("circle")
#define Filter_Circlemine	TEXT("circlemine")
#define Filter_Sector		TEXT("sector")
#define Filter_Team			TEXT("team")
//== 选人 B ==
//== 技能 A ==
#define Func_Attack			TEXT("attack")
#define Func_Phyattack		TEXT("phyattack")
#define Func_Mgattack		TEXT("mgattack")
#define Func_Damagebyhp		TEXT("damagebyhp")
#define Func_Damagebychop	TEXT("damagebychop")
#define Func_Damagebystatus	TEXT("damagebystatus")
#define Func_Damage			TEXT("damage")
#define Func_Phydmg			TEXT("phydmg")
#define Func_Mgdmg			TEXT("mgdmg")
#define Func_Suckhp			TEXT("suckhp"
#define Func_Curerank		TEXT("curerank")
#define Func_Buff			TEXT("buff")
#define Func_Bullettime		TEXT("bullettime")
#define Func_Buffactor		TEXT("buffactor")
#define Func_Dmgrebound		TEXT("dmgrebound")
#define Func_Mpadd			TEXT("mpadd")
#define Func_Hpadd			TEXT("hpadd")
#define Func_Buffbreak		TEXT("buffbreak")
#define Func_Dmgoverlap		TEXT("dmgoverlap")
#define Func_Buffaddrect		TEXT("buffaddrect")
#define Func_Dmgcountaddhp	TEXT("dmgcountaddhp")
#define Func_Dmgcount		TEXT("dmgcount")
#define Func_Atkcount		TEXT("atkcount")
#define Func_Reborn			TEXT("reborn")
#define Func_Deathskill		TEXT("deathskill")
#define Func_Filter			TEXT("filter")
#define Func_Taunt			TEXT("taunt")
#define Func_Property		TEXT("property")
#define Func_Clearbuff		TEXT("clearbuff")
#define Func_Dmgsuckmax		TEXT("dmgsuckmax")
#define Func_Buffover		TEXT("buffover")
#define Func_Hurtduration	TEXT("hurtduration")
//== 技能 B ==
//== 属性 A ==
#define	Func_Hpmaxadd		TEXT("hpmaxadd")
#define	Func_Phyattack		TEXT("phyattack")
#define	Func_Phyarmor		TEXT("phyarmor")
#define	Func_Mgattack		TEXT("mgattack")
#define	Func_Magarmor		TEXT("magarmor")	
#define	Func_Phyignore		TEXT("phyignore")	
#define	Func_Magignore		TEXT("magignore")	
#define	Func_Critrate		TEXT("critrate")	
#define	Func_Hprec			TEXT("hprec")		
#define	Func_Mprec			TEXT("mprec")		
#define	Func_Movespeed		TEXT("movespeed")	
#define	Func_Atspeed		TEXT("atspeed")
#define	Func_Dodrate		TEXT("dodrate")	
#define	Func_Suckhplv		TEXT("suckhplv")
#define	Func_Phydmgimmunity	TEXT("phydmgimmunity")
#define	Func_Magdmgimmunity	TEXT("magdmgimmunity")
#define Func_Buffoverlimit	TEXT("dmgoverlimit")
#define Func_Hpcheck		TEXT("hpcheck")
#define Func_Actorcheck		TEXT("actorcheck")
#define Func_Moveactor		TEXT("moveactor"
#define Func_Changeskillmpadd TEXT("changeskillmpadd")
#define Func_Skillmpadd		TEXT("skillmpadd")
#define Func_Tenacity		TEXT("tenacity")
#define Func_Hit			TEXT("hit")
#define Func_Suckhp			TEXT("suckhp")
#define Func_Rebound		TEXT("rebound")
#define Func_Attackmove		TEXT("attackmove")
#define Func_Dmgaddlock		TEXT("dmgaddlock")
#define Func_Buffaddtype	TEXT("buffaddtype")
#define Func_Enlarge		TEXT("enlarge")
#define Func_Teleport		TEXT("teleport")
#define Func_Buffaddtbuff	TEXT("buffaddbuff")
#define Func_Actorclone		TEXT("actorclone")
#define Func_Explode		TEXT("explode")
#define Func_Attackmoveedg	TEXT("attackmoveedg")
//== 属性 B ==

class UAbsPkEvent;
class UAbsFilter;

UCLASS()
class UFunctionFactory : public UObject, public USingleton<UFunctionFactory>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UFunctionFactory();
	virtual ~UFunctionFactory();

	void InitFuncAndFilters();
	UAbsFilter* createFilter(const FString& _str);
	UAbsPkEvent* createFunction(const FString& _str);

private:
	void registerFunction(UAbsPkEvent* _object);//注册Function
	void registerFilter(UAbsFilter* _object);//注册选人

private:
	TMap<FString, UAbsPkEvent*>	mFunctionMap;
	TMap<FString, UAbsFilter*>	mFilterMap;
};
