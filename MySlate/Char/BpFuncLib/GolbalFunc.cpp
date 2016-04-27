// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "GolbalFunc.h"

#include "Char/Skill/Utils/SkillDataMgr.h"
#include "Char/Skill/SkillMgr.h"
#include "Char/CharMgr.h"
#include "Kismet/KismetMathLibrary.h"
#include "Char/Skill/Function/FuncFactory.h"
#include "BaseDatas/BaseDataMgr.h"
#include "Char/Skill/Buff/BuffMgr.h"
#include "Char/Res/ResMgr.h"
#include "Char/MyChar.h"

USkillDataMgr*	UGolbalFunc::gSkillDataMgr	= nullptr;
USkillMgr*		UGolbalFunc::gSkillMgr		= nullptr;
UCharMgr*		UGolbalFunc::gCharMgr		= nullptr;
UFuncFactory*	UGolbalFunc::gFunctionMgr	= nullptr;
UBaseDataMgr*	UGolbalFunc::gBaseDataMgr	= nullptr;
UBuffMgr*		UGolbalFunc::gBuffMgr		= nullptr;
UResMgr*		UGolbalFunc::gResMgr		= nullptr;

// Sets default values
//UGolbalFunc::UGolbalFunc(const UGolbalFunc& ObjectInitializer) : Super(ObjectInitializer)
UGolbalFunc::UGolbalFunc() : Super()
{
	
}

UGolbalFunc::~UGolbalFunc()
{

}

void UGolbalFunc::InitMgrs()
{
	gSkillDataMgr = USkillDataMgr::GetInstance();
	gSkillMgr = USkillMgr::GetInstance();
	gCharMgr = UCharMgr::GetInstance();
	gFunctionMgr = UFuncFactory::GetInstance();
	gFunctionMgr->InitFuncAndFilters();
	gBaseDataMgr = UBaseDataMgr::GetInstance();
	gBuffMgr = UBuffMgr::GetInstance();
	gResMgr = UResMgr::GetInstance();
}

void UGolbalFunc::DestroyMgrs()
{
	USkillDataMgr::ReleaseInstance();
	USkillMgr::ReleaseInstance();
	UCharMgr::ReleaseInstance();
	UFuncFactory::ReleaseInstance();
	UBaseDataMgr::ReleaseInstance();
	UBuffMgr::ReleaseInstance();
	UResMgr::ReleaseInstance();
	gSkillDataMgr = nullptr;
	gSkillMgr = nullptr;
	gCharMgr = nullptr;
	gFunctionMgr = nullptr;
	gBaseDataMgr = nullptr;
	gBuffMgr = nullptr;
	gResMgr = nullptr;
}

void UGolbalFunc::TurnForward(AActor* _actor, const FVector& _targetLoc)
{
	FRotator rota = UKismetMathLibrary::FindLookAtRotation(_actor->GetActorLocation(), _targetLoc);
	_actor->SetActorRotation(rota);
}

void UGolbalFunc::DrawSegment(const FVector& _start, const FVector& _end, float _time /* = 5.f */)
{
	::DrawDebugLine(GWorld, _start, _end, FColor::Red, true, _time);
	::DrawDebugSolidBox(GWorld, _start, FVector(5.f, 5.f, 5.f), FColor::Green, true, _time);
	::DrawDebugSolidBox(GWorld, _end, FVector(5.f, 5.f, 5.f), FColor::Green, true, _time);

	//dist
	int32 dist = (int32)(_end - _start).Size();
	::DrawDebugString(GWorld, (_start + _end) / 2.f, FString::Printf(TEXT("%d"), dist), nullptr, FColor::Green, 5.f, true);
}

void UGolbalFunc::TestStrSplit()
{
	FString str = TEXT("aaa,bbb,,ccc,ddd");
	TArray<FString> params;
	str.ParseIntoArray(params, TEXT(","), true);

	for (int32 i = 0; i < params.Num(); ++i)
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- index:%d, value:%s"), i, *params[i]);
	}

}

void UGolbalFunc::TestMapRmove()
{
	//TMap<int32, FString> map1;
	//map1.Add(1, "aaa");
	//map1.Add(2, "bbb");
	//map1.Add(3, "ccc");
	//map1.Add(4, "ddd");
	//map1.Add(5, "eee");

	//for (auto Iter = map1.CreateIterator(); Iter;++Iter)
	//{
	//	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- %d, %s"), Iter->Key, *Iter->Value);
	//	if (Iter->Key == 3)
	//	{
	//		Iter.RemoveCurrent();
	//	}
	//}

	//for (auto Iter = map1.CreateIterator(); Iter; ++Iter)
	//{
	//	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- %d, %s"), Iter->Key, *Iter->Value);
	//}


	TArray<int32> mArr;
	mArr.Add(1);
	mArr.Add(222);
	mArr.Add(3);
	mArr.Add(4);
	mArr.Add(5);

	for (int32 i = 0;i < mArr.Num(); ++i)
	{
		if (mArr[i] == 222)
		{
			mArr.RemoveAt(i);
		}
	}

	for (auto tmp : mArr)
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- tmp:%d"), tmp);
	}
}

void UGolbalFunc::TestForceGC()
{
	GWorld->GetWorld()->ForceGarbageCollection(true);
}

void UGolbalFunc::TestStrContains(FString _str)
{
	bool b = _str.Contains(TEXT("%"));
	UE_LOG(GolbalFuncLogger, Warning, TEXT("--- TestStrContains result:%d"), (int32)b);
}

void UGolbalFunc::TestFilter(AMyChar* _actor, float _radius)
{
	TArray<AActor*> ignoreChars; //不忽略任何Actor，一般会忽略自身
	ignoreChars.Add(_actor);
	TArray<TEnumAsByte<EObjectTypeQuery>>  destObjectTypes; //目的类型集合
	destObjectTypes.Add((EObjectTypeQuery)ECollisionChannel::ECC_Pawn); //这里强转一下，一一对应的
	TArray<AActor*> destActors;
	UKismetSystemLibrary::SphereOverlapActors_NEW(
		GWorld
		,_actor->GetActorLocation()
		, _radius
		, destObjectTypes
		, AMyChar::StaticClass() //只要这种类的Actor
		, ignoreChars, destActors);

	//UE_LOG(GolbalFuncLogger, Warning, TEXT("--- destActors length:%d"), destActors.Num());
	for (auto elem : destActors)
	{
		AMyChar* mychar = Cast<AMyChar>(elem);
		if (mychar)
		{
			//UE_LOG(GolbalFuncLogger, Warning, TEXT("--- mychar uuid:%d"), mychar->GetUuid());
			//这里绘制一下，才能看出半径究竟有多长
			UGolbalFunc::DrawSegment(_actor->GetActorLocation(), mychar->GetActorLocation());
		}
	}
}

void UGolbalFunc::TestSpwanBullet(AMyChar* _actor)
{
	FActorSpawnParameters SpawnInfo;
	SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	AMyBullet* bullet = GWorld->SpawnActor<AMyBullet>(_actor->BulletClass, _actor->GetActorLocation(), _actor->GetActorRotation(), SpawnInfo);
}

void UGolbalFunc::TestArrLambda(FString _str)
{
	TArray<FString> arr;
	arr.Add(TEXT("aaa"));
	arr.Add(TEXT("ccc"));
	arr.Add(TEXT("eee"));
	arr.Add(TEXT("ddd"));

	//lambda表达式条件式查找，返回指针
	FString* result = arr.FindByPredicate([&](const FString& str)->bool { return str == _str; });
	if (result != nullptr)
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- Find result:%s"), **result);

		FString temp = *result;//必须要给一个临时对象，直接这样arr.Remove(**temp)会引发崩溃，检查地址不通过
		arr.Remove(temp);
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- len:%d"), arr.Num());

		for (FString str : arr)
		{
			UE_LOG(GolbalFuncLogger, Warning, TEXT("--- %s"), *str);
		}
	}
	else
	{
		UE_LOG(GolbalFuncLogger, Warning, TEXT("--- not Find result"));
	}
}

