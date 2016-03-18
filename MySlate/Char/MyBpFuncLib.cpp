// Fill out your copyright notice in the Description page of Project Settings.

#include "MySlate.h"
#include "MyBpFuncLib.h"

#include "MyChar.h"
#include "Animation/AnimBlueprint.h"
#include "Engine/StreamableManager.h"
#include "Engine.h"
#include "Engine/LevelStreamingKismet.h"
#include "Singleton/SolusDataSingleton.h"
#include "Singleton/ItemInfoDatabase.h"
#include "MyAttachment.h"

DECLARE_LOG_CATEGORY_EXTERN(MyContaimTest, Log, All);
DEFINE_LOG_CATEGORY(MyContaimTest)

bool UMyBpFuncLib::TestChangeCharAnimInstance(AMyChar* _myChar, FString _pathMesh, FString _pathAnim)
{

	FStreamableManager* stream = new FStreamableManager();
	FStringAssetReference ref1(*_pathMesh);
	USkeletalMesh* TmpMesh = Cast<USkeletalMesh>(stream->SynchronousLoad(ref1));
	_myChar->GetMesh()->SetSkeletalMesh(TmpMesh);

	FStringAssetReference ref2(*_pathAnim);
	UAnimBlueprint* TmpMeshAnim = Cast<UAnimBlueprint>(stream->SynchronousLoad(ref2));
	_myChar->GetMesh()->SetAnimInstanceClass((UClass*)TmpMeshAnim->GetAnimBlueprintGeneratedClass());
	delete stream;
	return true;
}

bool UMyBpFuncLib::VictoryLoadLevelInstance(UObject * WorldContextObject, FString mapPath, int32 InstanceNumber, FVector Location, FRotator Rotation)
{
	if (!WorldContextObject) return false;

	UWorld* const World = GEngine->GetWorldFromContextObject(WorldContextObject);
	if (!World) return false;
	//~~~~~~~~~~~

	//Full Name
	FString FullName = mapPath;

	FName LevelFName = FName(*FullName);
	FString PackageFileName = FullName;

	ULevelStreamingKismet* StreamingLevel = NewObject<ULevelStreamingKismet>((UObject*)GetTransientPackage(), ULevelStreamingKismet::StaticClass());

	if (!StreamingLevel)
	{
		return false;
	}

	//Long Package Name
	FString LongLevelPackageName = FPackageName::FilenameToLongPackageName(PackageFileName);

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Here is where a unique name is chosen for the new level asset
	//    Ensure unique names to gain ability to have multiple instances of same level!
	//	   <3 Rama

	//Create Unique Name based on BP-supplied instance value
	FString UniqueLevelPackageName = LongLevelPackageName;
	UniqueLevelPackageName += "_VictoryInstance_" + FString::FromInt(InstanceNumber);
	//Set!// Associate a package name.
	StreamingLevel->SetWorldAssetByPackageName(FName(*UniqueLevelPackageName));

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

	if (World->IsPlayInEditor())
	{
		FWorldContext WorldContext = GEngine->GetWorldContextFromWorldChecked(World);
		StreamingLevel->RenameForPIE(WorldContext.PIEInstance);
	}

	StreamingLevel->LevelColor = FColor::MakeRandomColor();
	StreamingLevel->bShouldBeLoaded = true;
	StreamingLevel->bShouldBeVisible = true;
	StreamingLevel->bShouldBlockOnLoad = false;
	StreamingLevel->bInitiallyLoaded = true;
	StreamingLevel->bInitiallyVisible = true;

	//Transform
	StreamingLevel->LevelTransform = FTransform(Rotation, Location);
	StreamingLevel->PackageNameToLoad = LevelFName;

	if (!FPackageName::DoesPackageExist(StreamingLevel->PackageNameToLoad.ToString(), NULL, &PackageFileName))
	{
		return false;
	}

	//~~~

	//Actual map package to load
	StreamingLevel->PackageNameToLoad = FName(*LongLevelPackageName);

	//~~~

	// Add the new level to world.
	World->StreamingLevels.Add(StreamingLevel);

	//UGameplayStatics::OpenLevel((UObject*s) );
	return false;
}

void UMyBpFuncLib::TestNSLocatext(int32 _dayCount, int32 _hp)
{
	FFormatNamedArguments Args;
	Args.Add("DayCount", _dayCount);
	Args.Add("Hp", _hp);
	FText txt1 = FText::Format(NSLOCTEXT("Solus", "Day", "--- Day1 {DayCount}"), Args);
	FText txt2 = FText::Format(NSLOCTEXT("Solus", "HP", "--- HP1 {Hp}"), Args);

	FFormatOrderedArguments Args2;
	Args2.Add(_dayCount);
	Args2.Add(_hp);
	FText txt3 = FText::Format(NSLOCTEXT("Solus", "Day", "--- Day2 {0}"), Args2);
	FText txt4 = FText::Format(NSLOCTEXT("Solus", "HP", "--- HP2 {1}"), Args2);


	FString str = txt1.ToString()
		+ TEXT("\n")
		+ txt2.ToString()
		+ TEXT("\n")
		+ txt3.ToString()
		+ TEXT("\n")
		+ txt4.ToString();
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
}

void UMyBpFuncLib::TestRefArgs1(UPARAM(ref) TArray<int32>& _numAry, UPARAM(ref)TArray<int32>& _numAry2)
{
	for (auto& num : _numAry)
		num += 100;
}

void UMyBpFuncLib::TestRefArgs2(UPARAM(ref)TArray<int32>& _numAry, TArray<int32>& _numAry2)
{
	for (auto& num : _numAry)
		num += 100;

	_numAry2 = _numAry;
}

void UMyBpFuncLib::TestRefArgs3(TArray<int32>& _numAry2)
{
	TArray<int32> tmp;
	tmp.Add(7);
	tmp.Add(8);
	tmp.Add(9);
	_numAry2 = tmp; //这种方式外部获取到的_numAry2竟然可以正常遍历，晕
}

void UMyBpFuncLib::TestFileWriteCompressed(FString _path)
{
	//FPlatformFileManager::Get().SetPlatformFile(*CurrentPlatformFile);
	//Step 1: Variable Data -> Binary
	uint8 b = 1;
	int32 num = 123;
	float height = 456.789;
	FString dataStr = FString::Printf(TEXT("--- dataStr"));
	FVector tmp(11.11, 22.22, 33.33);
	TArray<FRotator> SaveDataRotatorArray;
	for (int32 i = 0; i < 10; i++)
		SaveDataRotatorArray.Push(FRotator(i*10, i*10, i*10));

	FBufferArchive ToBinary;
	ToBinary << b;
	ToBinary << num;
	ToBinary << height;
	ToBinary << dataStr;
	ToBinary << tmp; //save player location to hard disk
	ToBinary << SaveDataRotatorArray;

	//Save data 
	//FString SavePath = "C:\\mysavefileCp.save";

	//No Data
	if (ToBinary.Num() <= 0) return;

	// Compress File 
	//tmp compressed data array
	TArray<uint8> CompressedData;
	FArchiveSaveCompressedProxy Compressor =
		FArchiveSaveCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	//Send entire binary array/archive to compressor
	Compressor << ToBinary;

	//send archive serialized data to binary array
	Compressor.Flush();

	//test size
	FString str = FString::Printf(TEXT("--- befor Compresse:%d, after Compresse:%d"), ToBinary.Num(), CompressedData.Num());
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	////Step 2: Binary to Hard Disk - compress
	//vibes to file, return successful or not
	if (FFileHelper::SaveArrayToFile(CompressedData, *_path))
	{
		// Free Binary Arrays 
		Compressor.FlushCache();
		CompressedData.Empty();

		ToBinary.FlushCache();
		ToBinary.Empty();

		// Close Buffer 
		ToBinary.Close();
		return;
	}
	else
	{
		// Free Binary Arrays 
		Compressor.FlushCache();
		CompressedData.Empty();

		ToBinary.FlushCache();
		ToBinary.Empty();

		// Close Buffer 
		ToBinary.Close();
		return;
	}
}

void UMyBpFuncLib::TestFileReadCompressed(FString _path)
{
	//Load the Compressed data array
	TArray<uint8> CompressedData;
	if (!FFileHelper::LoadFileToArray(CompressedData, *_path))
	{
		FString str = FString::Printf(TEXT("--- FFILEHELPER:>> Invalid File"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	// Decompress File 
	FArchiveLoadCompressedProxy Decompressor =
		FArchiveLoadCompressedProxy(CompressedData, ECompressionFlags::COMPRESS_ZLIB);

	//Decompression Error?
	if (Decompressor.GetError())
	{
		FString str = FString::Printf(TEXT("--- FArchiveLoadCompressedProxy>> ERROR : File Was Not Compressed"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	//Decompress
	FBufferArchive DecompressedBinaryArray;
	Decompressor << DecompressedBinaryArray;

	uint8 b = 0;
	int32 num = 0;
	float height = 0.f;
	FString dataStr(TEXT(""));
	FVector location;
	TArray<FRotator> rotatorArr;

	//Read the Data Retrieved by GFileManager
	FMemoryReader FromBinary = FMemoryReader(DecompressedBinaryArray, true); //true, free data after done
	FromBinary.Seek(0);
	FromBinary << b;
	FromBinary << num;
	FromBinary << height;
	FromBinary << dataStr;
	FromBinary << location;
	FromBinary << rotatorArr;

	CompressedData.Empty();
	Decompressor.FlushCache();
	FromBinary.FlushCache();

	// Empty & Close Buffer 
	DecompressedBinaryArray.Empty();
	DecompressedBinaryArray.Close();


	//print
	FString str2 = FString::Printf(TEXT("--- b:%d, num:%d, height:%f, dataStr:%s\n"), b, num, height, *dataStr);
	FString str3 = FString::Printf(TEXT("--- location x:%f, y:%f, z:%f\n"), location.X, location.Y, location.Z);

	FString str4("");
	for (auto rot : rotatorArr)
	{
		FString tmp = FString::Printf(TEXT("--- rotator Pitch:%f, Yaw:%f, Roll:%f\n"), rot.Pitch, rot.Yaw, rot.Roll);
		str4.Append(tmp);
	}
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str2 + str3 + str4);
}

void UMyBpFuncLib::TestFileWriteUnCompressed(FString _path)
{
	//FPlatformFileManager::Get().SetPlatformFile(*CurrentPlatformFile);
	//Step 1: Variable Data -> Binary
	FBufferArchive ToBinary;
	uint8 b = 1;
	int32 num = 123;
	float height = 456.789;
	FString dataStr = FString::Printf(TEXT("--- dataStr"));
	FVector tmp(11.11, 22.22, 33.33);
	TArray<FRotator> SaveDataRotatorArray;
	for (int32 i = 0; i < 10; i++)
		SaveDataRotatorArray.Push(FRotator(i * 10, i * 10, i * 10));

	ToBinary << b;
	ToBinary << num;
	ToBinary << height;
	ToBinary << dataStr;
	ToBinary << tmp; //save player location to hard disk
	ToBinary << SaveDataRotatorArray;

	//Save data 
	//FString SavePath = "C:\\mysavefileUnCp.save";

	//No Data
	if (ToBinary.Num() <= 0) return;

	//Step 2: Binary to Hard Disk
	if (FFileHelper::SaveArrayToFile(ToBinary, *_path))
	{
		// Free Binary Array 	
		ToBinary.FlushCache();
		ToBinary.Empty();

		FString str = FString::Printf(TEXT("--- SaveFile Success"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	// Free Binary Array 	
	ToBinary.FlushCache();
	ToBinary.Empty();
}

void UMyBpFuncLib::TestFileReadUnCompressed(FString _path)
{
	//Load the data array,
	// 	you do not need to pre-initialize this array,
	//		UE4 C++ is awesome and fills it 
	//		with whatever contents of file are, 
	//		and however many bytes that is
	TArray<uint8> TheBinaryArray;
	if (!FFileHelper::LoadFileToArray(TheBinaryArray, *_path))
	{
		FString str = FString::Printf(TEXT("--- LoadFileToArray Fail"));
		GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);
		return;
	}

	//Testing
	FString str = FString::Printf(TEXT("--- Loaded File Size:%d"), TheBinaryArray.Num());
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Green, str);

	//File Load Error
	if (TheBinaryArray.Num() <= 0) return;

	uint8 b = 0;
	int32 num = 0;
	float height = 0.f;
	FString dataStr(TEXT(""));
	FVector location;
	TArray<FRotator> rotatorArr;

	//Read the Data Retrieved by GFileManager
	FMemoryReader FromBinary = FMemoryReader(TheBinaryArray, true); //true, free data after done
	FromBinary.Seek(0);

	FromBinary << b;
	FromBinary << num;
	FromBinary << height;
	FromBinary << dataStr;
	FromBinary << location;
	FromBinary << rotatorArr;

	//Clean up 
	FromBinary.FlushCache();
	FromBinary.Close();

	// Empty & Close Buffer 
	TheBinaryArray.Empty();

	//print
	FString str2 = FString::Printf(TEXT("--- b:%d, num:%d, height:%f, dataStr:%s\n"), b, num, height, *dataStr);
	FString str3 = FString::Printf(TEXT("--- location x:%f, y:%f, z:%f\n"), location.X, location.Y, location.Z);

	FString str4("");
	for (auto rot : rotatorArr)
	{
		FString tmp = FString::Printf(TEXT("--- rotator Pitch:%f, Yaw:%f, Roll:%f\n"), rot.Pitch, rot.Yaw, rot.Roll);
		str4.Append(tmp);
	}
	GEngine->AddOnScreenDebugMessage(0, 5.0f, FColor::Yellow, str2 + str3 + str4);
}

USolusDataSingleton * UMyBpFuncLib::GetSolusData(bool & IsValid)
{	//IsValid看起来时新参，其实是蓝图中的返回值
	IsValid = false;
	USolusDataSingleton* DataInstance = Cast<USolusDataSingleton>(GEngine->GameSingleton); //这里指定配置文件中指定的单例类

	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}

USolusDataSingleton* UMyBpFuncLib::GetSolusSingleton(bool & IsValid)
{
	IsValid = false;
	USolusDataSingleton* DataInstance = USolusDataSingleton::Get();
	if (!DataInstance) return NULL;
	if (!DataInstance->IsValidLowLevel()) return NULL;

	IsValid = true;
	return DataInstance;
}

bool UMyBpFuncLib::TestAsyncLoad(AMyChar* _myChar)
{
	if (!_myChar)
		return false;

	FStreamableManager* BaseLoader = USolusDataSingleton::Get()->AssetLoader;
	UItemInfoDatabase* _database = USolusDataSingleton::Get()->ItemDatabase;

	if (!BaseLoader || !_database)
		return false;

	TArray<FStringAssetReference> ObjToLoad;
	for (int32 i = 0; i < _database->MeshList.Num(); ++i)
	{
		ObjToLoad.AddUnique(_database->MeshList[i].MeshResource.ToStringReference());
	}
	//请求异步加载
	BaseLoader->RequestAsyncLoad(ObjToLoad, FStreamableDelegate::CreateUObject(_myChar, &AMyChar::TestAsyncLoad));
	return true;
}

void UMyBpFuncLib::TestObjFunc(AMyChar* _myChar,FString _funcName)
{
	FName FuncFName = FName(*_funcName);
	UFunction* Function = _myChar->FindFunction(FuncFName);
	if (Function)
	{
		FString str = FString::Printf(TEXT("--- UFunction arg num:%d"), Function->NumParms); //这个方法的参数个数
		GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Green, str);

		struct FAnimNotifierHandler_Parms //结构体和方法参数的类型和顺序要一致
		{
			int32 NotifyNum;
			FString NotifyStr;
		};

		FAnimNotifierHandler_Parms Parms;
		Parms.NotifyNum = 987;
		Parms.NotifyStr = FString(TEXT("yangx"));
		_myChar->ProcessEvent(Function, &Parms);
	}
}

void UMyBpFuncLib::TestBpDelegate(AMyChar * _myChar, int32 _num)
{
	_myChar->OnMyDelegate2.Broadcast(_num);
}

void UMyBpFuncLib::TestDressWeapon(AMyChar * _myChar)
{
	if (!_myChar->Weapon1)
	{
		USMyAttachment* MyArmor = NewObject<USMyAttachment>(_myChar, *_myChar->Weapon1Class);
		MyArmor->RegisterComponent();
		MyArmor->AttachTo(_myChar->GetMesh(), MyArmor->AttachPoint);
		_myChar->Weapon1 = MyArmor;
	}
}

void UMyBpFuncLib::TestHasBpImpl(AMyChar * _myChar)
{
	FString str = FString::Printf(TEXT("--- has bp func:%d"), _myChar->hasOnDeathImplementEvent);
	GEngine->AddOnScreenDebugMessage(0, 2.0f, FColor::Red, str);

	_myChar->OnDeath(FString(TEXT("aaa")), 123);
}

static void testArr1()
{
	auto printFunc1 = [&](TArray<FString>& _arr)->void{
		for (int32 i = 0; i < _arr.Num(); i++)
		{
			//FString str = FString::Printf(TEXT("--- index:%d, value:%s "), i, *_arr[i]);
			//GEngine->AddOnScreenDebugMessage(0, 3.0f, FColor::Red, str);
			UE_LOG(MyContaimTest, Warning, TEXT("--- index:%d, value:%s "),i, *_arr[i]);
		}
	};

	auto printFunc2 = [&](TArray<FString>& _arr)->void {
		for (const FString& val : _arr)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- value111:%s"), *val);
		}
	};

	auto printFunc3 = [&](TArray<FString>& _arr)->void {
		for (TArray<FString>::TConstIterator iter = _arr.CreateConstIterator(); iter; ++iter)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- value222:%s"), *(*iter));
		}
	};

	auto printFunc4 = [&](TArray<int32>& _arr)->void {
		for (TArray<int32>::TConstIterator iter = _arr.CreateConstIterator(); iter; ++iter)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- value333:%d"), (*iter));
		}
	};

	//TODO: ------------------  华丽分割线 TArray 增 ------------
	// 创建一个数组
	TArray<int32> IntArray;

	// 通过同一个元素填充初始化
	IntArray.Init(10, 5);
	// IntArray == [10, 10, 10, 10, 10]

	// 增加新元素
	// Add会引入临时对象，优先使用Emplace
	TArray<FString> StrArr;
	StrArr.Add(TEXT("Hello"));
	StrArr.Emplace(TEXT("World"));
	// StrArr == ["Hello", "World"]
	//printFunc1(StrArr);

	// 追加多个元素
	FString Arr[] = { TEXT("of"), TEXT("Tomorrow") };
	StrArr.Append(Arr, ARRAY_COUNT(Arr));
	// StrArr == ["Hello", "World", "of", "Tomorrow"]
	//printFunc1(StrArr);

	// 只有容器中不存在该元素的时候，才添加
	StrArr.AddUnique(TEXT("!"));
	// StrArr = ["Hello", "World", "of", "Tomorrow", "!"]
	//printFunc1(StrArr);
	StrArr.AddUnique(TEXT("!"));
	// StrArr没有变
	//printFunc1(StrArr);

	// 插入
	StrArr.Insert(TEXT("Brave"), 1);
	// StrArr == ["Hello","Brave","World","of","Tomorrow","!"]
	//printFunc1(StrArr);

	// 直接设置数组的元素个数
	// 如果大于当前值，那么使用元素类型的默认构造函数创建新元素
	// 如果下雨当前值，相当于删除元素
	StrArr.SetNum(8);
	// StrArr == ["Hello","Brave","World","of","Tomorrow","!","",""]
	//printFunc1(StrArr);

	StrArr.SetNum(6);
	// StrArr == ["Hello","Brave","World","of","Tomorrow", "!"]
	//printFunc1(StrArr);
	//printFunc2(StrArr);
	//printFunc3(StrArr);

	//TODO: ------------------  华丽分割线 TArray 排序 ------------
	// 排序（快排序，不稳定的）
	// 默认按照operator <
	StrArr.Sort();
	// StrArr == ["!","Brave","Hello","of","Tomorrow","World"]

	// 自定义排序规则
	StrArr.Sort([](const FString& A, const FString& B) {
		return A.Len() < B.Len();
	});
	// StrArr == ["!","of","Hello","Brave","World","Tomorrow"]
	//printFunc1(StrArr);

	// 堆排序（也不稳定的）
	StrArr.HeapSort([](const FString& A, const FString& B) {
		return A.Len() < B.Len();
	});
	// StrArr == ["!","of","Brave","Hello","World","Tomorrow"]
	//printFunc1(StrArr);

	// 合并排序（稳定的）
	StrArr.StableSort([](const FString& A, const FString& B) {
		return A.Len() < B.Len();
	});
	// StrArr == ["!","of","Brave","Hello","World","Tomorrow"]
	//printFunc1(StrArr);

	//TODO: ------------------  华丽分割线 TArray 查 ------------
	// 查询
	// 数量
	int32 Count = StrArr.Num();
		// Count == 6

	// 直接访问
	// 如果容器是const，那么返回的指针也是const的
	FString* StrPtr = StrArr.GetData();
	// StrPtr[0] == "!"
	// StrPtr[1] == "of"
	// ...

	// 一个元素的大小
	uint32 ElementSize = StrArr.GetTypeSize();
	// ElementSize == sizeof(FString)

	// 判断索引
	bool bValidM1 = StrArr.IsValidIndex(-1);
	// bValidM1 == false

	// operator[] 返回索引
	//StrArr[3] = StrArr[3].ToUpper();
	// StrArr == ["!","of","Brave","HELLO","World","Tomorrow"]

	// 从后面访问
	FString ElemEnd = StrArr.Last();
	FString ElemEnd0 = StrArr.Last(0);
	FString ElemEnd1 = StrArr.Last(1);
	FString ElemTop = StrArr.Top();
	// ElemEnd  == "Tomorrow"
	// ElemEnd0 == "Tomorrow"
	// ElemEnd1 == "World"
	// ElemTop  == "Tomorrow"

	// 查询是否存在某元素
	bool bHello = StrArr.Contains(TEXT("Hello"));
	bool bGoodbye = StrArr.Contains(TEXT("Goodbye"));
	// bHello   == true
	// bGoodbye == false

	// 自定义查询规则
	bool bLen5 = StrArr.ContainsByPredicate([](const FString& Str) {
		return Str.Len() == 5;
	});
	bool bLen6 = StrArr.ContainsByPredicate([](const FString& Str) {
		return Str.Len() == 6;
	});
	// bLen5 == true
	// bLen6 == false

	// 查找，返回索引
	int32 Index;
	if (StrArr.Find(TEXT("Hello"), Index))
	{
		// Index == 3
	}
	int32 IndexLast;
	if (StrArr.FindLast(TEXT("Hello"), IndexLast))
	{
		// IndexLast == 3, because there aren't any duplicates
	}
	// 还可以直接返回index, 如果找不到会返回INDEX_NONE
	int32 Index2 = StrArr.Find(TEXT("Hello"));
	int32 IndexLast2 = StrArr.FindLast(TEXT("Hello"));
	int32 IndexNone = StrArr.Find(TEXT("None"));
	// Index2     == 3
	// IndexLast2 == 3
	// IndexNone  == INDEX_NONE

	// 还可以用IndexOfByKey, 采用operator==(ElementType, KeyType)比较
	int32 Index3 = StrArr.IndexOfByKey(TEXT("Hello"));
	// Index == 3

	int32 Index4 = StrArr.IndexOfByPredicate([](const FString& Str) {
		return Str.Contains(TEXT("r"));
	});
	// Index == 2

	// 除了返回索引，也可以返回指针
	auto* OfPtr = StrArr.FindByKey(TEXT("of"));
	auto* ThePtr = StrArr.FindByKey(TEXT("the"));
	// OfPtr  == &StrArr[1]
	// ThePtr == nullptr

	auto* Len5Ptr = StrArr.FindByPredicate([](const FString& Str) {
		return Str.Len() == 5;
	});
	auto* Len6Ptr = StrArr.FindByPredicate([](const FString& Str) {
		return Str.Len() == 6;
	});
	// Len5Ptr == &StrArr[2]
	// Len6Ptr == nullptr

	//TODO: ------------------  华丽分割线 TArray 删 ------------
	// 删除所有匹配的元素
	StrArr.Remove(TEXT("hello"));
	// StrArr == ["!","of","Brave","World","Tomorrow"]
	StrArr.Remove(TEXT("goodbye"));
	// StrArr is unchanged, as it doesn't contain "goodbye"

	// 删除最后的元素
	StrArr.Pop();
	// StrArr == ["!", "of", "Brave", "World"]

	// 删除第一个匹配元素
	TArray<int32> ValArr;
	int32 Temp[] = { 10, 20, 30, 5, 10, 15, 20, 25, 30 };
	ValArr.Append(Temp, ARRAY_COUNT(Temp));
	// ValArr == [10,20,30,5,10,15,20,25,30]

	ValArr.Remove(20);
	// ValArr == [10,30,5,10,15,25,30]
	ValArr.RemoveSingle(30);
	// ValArr == [10,5,10,15,25,30]
	// 通过索引删除
	ValArr.RemoveAt(2); // Removes the element at index 2
						// ValArr == [10,5,15,25,30]
	//ValArr.RemoveAt(99);
	// This will cause a runtime error as
	// there is no element at index 99

	// 条件删除
	ValArr.RemoveAll([](int32 Val) {
		return Val % 3 == 0;
	});
	// ValArr == [10,5,25]

	// 如果删除元素之后无顺序要求，可以用更高效的方法
	//原理：把最后的元素移动到被删除的地方，这样就无需移动 被删除元素以后的元素
	TArray<int32> ValArr2;
	for (int32 i = 0; i != 10; ++i)
		ValArr2.Add(i % 5);
	// ValArr2 == [0,1,2,3,4,0,1,2,3,4]

	ValArr2.RemoveSwap(2); //删除等于2的元素
	// ValArr2 == [0,1,4,3,4,0,1,3]

	ValArr2.RemoveAtSwap(1); //删除索引为1的元素
	// ValArr2 == [0,3,4,3,4,0,1]

	ValArr2.RemoveAllSwap([](int32 Val) { //删除所有3的倍数
		return Val % 3 == 0;
	});
	// ValArr2 == [1,4,4]

	// 清空
	ValArr2.Empty();
	// ValArr2 == []

	//TODO: ------------------  华丽分割线 TArray 支持的操作符, 也支持move语义 ------------
	TArray<int32> ValArr3;
	ValArr3.Add(1);
	ValArr3.Add(2);
	ValArr3.Add(3);

	auto ValArr4 = ValArr3;
	// ValArr4 == [1,2,3];
	ValArr4[0] = 5;
	// ValArr3 == [1,2,3];
	// ValArr4 == [5,2,3];

	ValArr4 += ValArr3;
	// ValArr4 == [5,2,3,1,2,3]

	// move语义，源数组会被清空
	ValArr3 = MoveTemp(ValArr4);
	// ValArr3 == [5,2,3,1,2,3]
	// ValArr4 == []

	TArray<FString> FlavorArr1;
	FlavorArr1.Emplace(TEXT("Chocolate"));
	FlavorArr1.Emplace(TEXT("Vanilla"));
	// FlavorArr1 == ["Chocolate","Vanilla"]

	auto FlavorArr2 = FlavorArr1;
	// FlavorArr2 == ["Chocolate","Vanilla"]
	bool bComparison1 = FlavorArr1 == FlavorArr2;
	// bComparison1 == true
	if (bComparison1)
		UE_LOG(MyContaimTest, Warning, TEXT("--- FlavorArr1 == FlavorArr2"));

	for (auto& Str : FlavorArr2)
	{
		Str = Str.ToUpper();
	}
	// FlavorArr2 == ["CHOCOLATE","VANILLA"]

	bool bComparison2 = FlavorArr1 == FlavorArr2;
	// bComparison2 == true, because FString comparison ignores case
	if (bComparison2)
		UE_LOG(MyContaimTest, Warning, TEXT("--- FlavorArr1 == FlavorArr2 too"));

	Exchange(FlavorArr2[0], FlavorArr2[1]); //交换两个元素
	// FlavorArr2 == ["VANILLA","CHOCOLATE"]
	bool bComparison3 = FlavorArr1 == FlavorArr2;
	// bComparison3 == false, because the order has changed
}

static void testArr2()
{
	// 堆
	TArray<int32> HeapArr;
	for (int32 Val = 10; Val != 0; --Val)
		HeapArr.Add(Val);
	// HeapArr == [10,9,8,7,6,5,4,3,2,1]
	HeapArr.Heapify();
	// HeapArr == [1,2,4,3,6,5,8,10,7,9]

	HeapArr.HeapPush(4);
	// HeapArr == [1,2,4,3,4,5,8,10,7,9,6]
	int32 TopNode;
	HeapArr.HeapPop(TopNode);
	// TopNode == 1
	// HeapArr == [2,3,4,6,4,5,8,10,7,9]
	HeapArr.HeapRemoveAt(1);
	// HeapArr == [2,4,4,6,9,5,8,10,7]
	int32 Top = HeapArr.HeapTop();
	// Top == 2
}

static void testArr3()
{
	auto printFunc1 = [&](TArray<int32>& _arr)->void {
		UE_LOG(MyContaimTest, Warning, TEXT("--- GetSlack:%d, Num:%d, Max:%d"),
			_arr.GetSlack(), _arr.Num(), _arr.Max());
	};

	// slack
	// GetSlack() is equivalent to Max() - Num():
	TArray<int32> SlackArray;
	// SlackArray.GetSlack() == 0
	// SlackArray.Num()      == 0
	// SlackArray.Max()      == 0
	//printFunc1(SlackArray);

	SlackArray.Add(1);
	// SlackArray.GetSlack() == 3
	// SlackArray.Num()      == 1
	// SlackArray.Max()      == 4
	//printFunc1(SlackArray);

	SlackArray.Add(2);
	SlackArray.Add(3);
	SlackArray.Add(4);
	SlackArray.Add(5);
	// SlackArray.GetSlack() == 17
	// SlackArray.Num()      == 5
	// SlackArray.Max()      == 22
	//printFunc1(SlackArray); //重新分配内存的公式Retval = NumElements + 3*NumElements/8 + 16;

	SlackArray.Empty(); //内存也清空
	// SlackArray.GetSlack() == 0
	// SlackArray.Num()      == 0
	// SlackArray.Max()      == 0
	//printFunc1(SlackArray);

	SlackArray.Empty(3);//只是清空元素，内存还在
	// SlackArray.GetSlack() == 3
	// SlackArray.Num()      == 0
	// SlackArray.Max()      == 3

	SlackArray.Add(1);
	SlackArray.Add(2);
	SlackArray.Add(3);
	// SlackArray.GetSlack() == 0
	// SlackArray.Num()      == 3
	// SlackArray.Max()      == 3

	SlackArray.Reset(0); //只是清空元素，内存还在
	// SlackArray.GetSlack() == 3
	// SlackArray.Num()      == 0
	// SlackArray.Max()      == 3
	SlackArray.Reset(10);//大于当前的Max（10>3），重新分配内存
	// SlackArray.GetSlack() == 10
	// SlackArray.Num()      == 0
	// SlackArray.Max()      == 10

	SlackArray.Add(5);
	SlackArray.Add(10);
	SlackArray.Add(15);
	SlackArray.Add(20);
	// SlackArray.GetSlack() == 6
	// SlackArray.Num()      == 4
	// SlackArray.Max()      == 10
	SlackArray.Shrink(); //缩减内存到当前元素的个数
	// SlackArray.GetSlack() == 0
	// SlackArray.Num()      == 4
	// SlackArray.Max()      == 4
}

struct FMyStruct
{
	// String which identifies our key
	FString UniqueID;

	// Some state which doesn't affect struct identity
	float SomeFloat;

	explicit FMyStruct(float InFloat)
		: UniqueID(FGuid::NewGuid().ToString())
		, SomeFloat(InFloat)
	{
	}
};
template <typename ValueType>
struct TMyStructMapKeyFuncs :
	BaseKeyFuncs<
	TPair<FMyStruct, ValueType>,
	FString
	>
{
private:
	typedef BaseKeyFuncs<
		TPair<FMyStruct, ValueType>,
		FString
	> Super;

public:
	typedef typename Super::ElementInitType ElementInitType;
	typedef typename Super::KeyInitType     KeyInitType;

	static KeyInitType GetSetKey(ElementInitType Element)
	{
		return Element.Key.UniqueID;
	}

	static bool Matches(KeyInitType A, KeyInitType B)
	{
		return A.Compare(B, ESearchCase::CaseSensitive) == 0;
	}

	static uint32 GetKeyHash(KeyInitType Key)
	{
		return FCrc::StrCrc32(*Key);
	}
};

static void testMap1()
{
	auto printFunc1 = [&](TMap<int32, FString>& _map)->void {
		for (TPair<int32, FString>& element : _map)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- key:%d, value111:%s "),
				element.Key, *element.Value);
		}
	};

	auto printFunc2 = [&](TMap<int32, FString>& _map)->void {
		for (TMap<int32, FString>::TConstIterator iter = _map.CreateConstIterator(); iter; ++iter)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- key:%d, value222:%s "),
				iter->Key, *iter->Value);
		}
	};

	//TODO: ------------------  华丽分割线 TMap 增 ------------
	// 创建
	// key比较使用==
	// hashcode计算使用GetTypeHash
	TMap<int32, FString> FruitMap;

	FruitMap.Add(5, TEXT("Banana"));
	FruitMap.Add(2, TEXT("Grapefruit"));
	FruitMap.Add(7, TEXT("Pineapple"));
	// FruitMap == [
	//  { Key: 5, Value: "Banana"     },
	//  { Key: 2, Value: "Grapefruit" },
	//  { Key: 7, Value: "Pineapple"  }
	// ]
	FruitMap.Add(2, TEXT("Pear")); //相同key值，顶掉value
	// FruitMap == [
	//  { Key: 5, Value: "Banana"    },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" }
	// ]

	FruitMap.Add(4);//没有value值，会构造一个默认值进去
	// FruitMap == [
	//  { Key: 5, Value: "Banana"    },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: ""          }
	// ]

	FruitMap.Emplace(3, TEXT("Orange"));
	// FruitMap == [
	//  { Key: 5, Value: "Banana"    },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: ""          },
	//  { Key: 3, Value: "Orange"    }
	// ]

	TMap<int32, FString> FruitMap2;
	FruitMap2.Emplace(4, TEXT("Kiwi"));
	FruitMap2.Emplace(9, TEXT("Melon"));
	FruitMap2.Emplace(5, TEXT("Mango"));
	FruitMap.Append(FruitMap2); //已有的会顶掉，没有就完后叠
	// FruitMap == [
	//  { Key: 5, Value: "Mango"     },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: "Kiwi"      },
	//  { Key: 3, Value: "Orange"    },
	//  { Key: 9, Value: "Melon"     }
	// ]
	//printFunc1(FruitMap);

	//TODO: ------------------  华丽分割线 TMap 查 ------------
	//---------- 通过key查找到value
	// 查询
	int32 Count = FruitMap.Num();
	// Count == 6

	FString Val7 = FruitMap[7];
	// Val7 == "Pineapple"
	//FString Val8 = FruitMap[8]; // assert!//查找不存在的会造成运行时崩溃

	bool bHas7 = FruitMap.Contains(7);
	bool bHas8 = FruitMap.Contains(8);
	// bHas7 == true
	// bHas8 == false

	FString* Ptr7 = FruitMap.Find(7); //返回的是value的指针
	FString* Ptr8 = FruitMap.Find(8);
	// *Ptr7 == "Pineapple"
	//  Ptr8 == nullptr

	FString& Ref7 = FruitMap.FindOrAdd(7); //返回的是引用
	// Ref7     == "Pineapple"
	// FruitMap == [
	//  { Key: 5, Value: "Mango"     },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: "Kiwi"      },
	//  { Key: 3, Value: "Orange"    },
	//  { Key: 9, Value: "Melon"     }
	// ]

	FString& Ref8 = FruitMap.FindOrAdd(8); //不存在则构造一个添加进去，返回引用
	// Ref8     == ""
	// FruitMap == [
	//  { Key: 5, Value: "Mango"     },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: "Kiwi"      },
	//  { Key: 3, Value: "Orange"    },
	//  { Key: 9, Value: "Melon"     },
	//  { Key: 8, Value: ""          }
	// ]

	FString Val10 = FruitMap.FindRef(7); //存在则复制拷贝到变量中，不存在则变量自己构造
	FString Val9 = FruitMap.FindRef(6);
	// Val10    == "Pineapple"
	// Val9     == ""
	// FruitMap == [
	//  { Key: 5, Value: "Mango"     },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: "Kiwi"      },
	//  { Key: 3, Value: "Orange"    },
	//  { Key: 9, Value: "Melon"     },
	//  { Key: 8, Value: ""          }
	// ]

	//---------- 通过value查找到key
	const int32* KeyMangoPtr = FruitMap.FindKey(TEXT("Mango"));
	const int32* KeyKumquatPtr = FruitMap.FindKey(TEXT("Kumquat"));
	// *KeyMangoPtr   == 5
	//  KeyKumquatPtr == nullptr

	TArray<int32>   FruitKeys;
	TArray<FString> FruitValues;
	FruitMap.GenerateKeyArray(FruitKeys); //生成key、value数组
	FruitMap.GenerateValueArray(FruitValues);
	// FruitKeys   == [ 5,2,7,4,3,9,8 ]
	// FruitValues == [ "Mango","Pear","Pineapple","Kiwi","Orange",
	//                  "Melon","" ]

	//TODO: ------------------  华丽分割线 TMap 删 ------------
	FruitMap.Remove(8);
	// FruitMap == [
	//  { Key: 5, Value: "Mango"     },
	//  { Key: 2, Value: "Pear"      },
	//  { Key: 7, Value: "Pineapple" },
	//  { Key: 4, Value: "Kiwi"      },
	//  { Key: 3, Value: "Orange"    },
	//  { Key: 9, Value: "Melon"     }
	// ]

	FString Removed7 = FruitMap.FindAndRemoveChecked(7); //查找并移除
	// Removed7 == "Pineapple"
	// FruitMap == [
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 2, Value: "Pear"   },
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 3, Value: "Orange" },
	//  { Key: 9, Value: "Melon"  }
	// ]

	//FString Removed8 = FruitMap.FindAndRemoveChecked(8); // assert!不存在，运行时崩溃

	FString Removed;
	bool bFound2 = FruitMap.RemoveAndCopyValue(2, Removed); //存在这个拷贝数据，返回true
	// bFound2  == true
	// Removed  == "Pear"
	// FruitMap == [
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 3, Value: "Orange" },
	//  { Key: 9, Value: "Melon"  }
	// ]

	bool bFound8 = FruitMap.RemoveAndCopyValue(8, Removed); //不存在，则不改变Removed的值，返回false
	// bFound8  == false
	// Removed  == "Pear", i.e. unchanged
	// FruitMap == [
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 3, Value: "Orange" },
	//  { Key: 9, Value: "Melon"  }
	// ]

	TMap<int32, FString> FruitMapCopy = FruitMap;
	// FruitMapCopy == [
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 3, Value: "Orange" },
	//  { Key: 9, Value: "Melon"  }
	// ]

	FruitMapCopy.Empty();//清空
	// FruitMapCopy == []

	//TODO: ------------------  华丽分割线 TMap 排序 ------------
	// 排序
	FruitMap.KeySort([](int32 A, int32 B) {
		return A > B; // sort keys in reverse
	});
	// FruitMap == [
	//  { Key: 9, Value: "Melon"  },
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 3, Value: "Orange" }
	// ]

	FruitMap.ValueSort([](const FString& A, const FString& B) {
		return A.Len() < B.Len(); // sort strings by length
	});
	// FruitMap == [
	//  { Key: 4, Value: "Kiwi"   },
	//  { Key: 5, Value: "Mango"  },
	//  { Key: 9, Value: "Melon"  },
	//  { Key: 3, Value: "Orange" }
	// ]

	//TODO: ------------------  华丽分割线 TMap 支持的操作符, 也支持move语义 ------------
	// 操作符
	TMap<int32, FString> NewMap = FruitMap;
	NewMap[5] = "Apple";
	NewMap.Remove(3);
	// NewMap == [
	//  { Key: 4, Value: "Kiwi"  },
	//  { Key: 5, Value: "Apple" },
	//  { Key: 9, Value: "Melon" }
	// ]

	FruitMap = MoveTemp(NewMap); //move
	// FruitMap == [
	//  { Key: 4, Value: "Kiwi"  },
	//  { Key: 5, Value: "Apple" },
	//  { Key: 9, Value: "Melon" }
	// ]
	// NewMap == []

	// Slack
	FruitMap.Reset();//内存也清空
	// FruitMap == [<invalid>, <invalid>, <invalid>]
	printFunc1(FruitMap);

	FruitMap.Reserve(10);//预设了10个大小的内存，add时候从后往前叠；没有FruitMap.Reserve(10);则是从前往后叠
	for (int32 i = 0; i != 10; ++i)
	{
		FruitMap.Add(i, FString::Printf(TEXT("Fruit%d"), i));
	}
	// FruitMap == [
	//  { Key: 9, Value: "Fruit9" },
	//  { Key: 8, Value: "Fruit8" },
	//  ...
	//  { Key: 1, Value: "Fruit1" },
	//  { Key: 0, Value: "Fruit0" }
	// ]
	//printFunc1(FruitMap);

	for (int32 i = 0; i != 10; i += 2)
	{
		FruitMap.Remove(i); //移除后，还是有内存占用
	}
	// FruitMap == [
	//  { Key: 9, Value: "Fruit9" },
	//  <invalid>,
	//  { Key: 7, Value: "Fruit7" },
	//  <invalid>,
	//  { Key: 5, Value: "Fruit5" },
	//  <invalid>,
	//  { Key: 3, Value: "Fruit3" },
	//  <invalid>,
	//  { Key: 1, Value: "Fruit1" },
	//  <invalid>
	// ]
	//printFunc1(FruitMap);

	FruitMap.Shrink();//移除最后又一个有效内存 后的 所有无效的内存占用
	// FruitMap == [
	//  { Key: 9, Value: "Fruit9" },
	//  <invalid>,
	//  { Key: 7, Value: "Fruit7" },
	//  <invalid>,
	//  { Key: 5, Value: "Fruit5" },
	//  <invalid>,
	//  { Key: 3, Value: "Fruit3" },
	//  <invalid>,
	//  { Key: 1, Value: "Fruit1" }
	// ]
	//printFunc1(FruitMap);

	FruitMap.Compact(); //把无效的都丢到后面
	// FruitMap == [
	//  { Key: 9, Value: "Fruit9" },
	//  { Key: 7, Value: "Fruit7" },
	//  { Key: 5, Value: "Fruit5" },
	//  { Key: 3, Value: "Fruit3" },
	//  { Key: 1, Value: "Fruit1" },
	//  <invalid>,
	//  <invalid>,
	//  <invalid>,
	//  <invalid>
	// ]
	FruitMap.Shrink();
	// FruitMap == [
	//  { Key: 9, Value: "Fruit9" },
	//  { Key: 7, Value: "Fruit7" },
	//  { Key: 5, Value: "Fruit5" },
	//  { Key: 3, Value: "Fruit3" },
	//  { Key: 1, Value: "Fruit1" }
	// ]

	//TODO: ------------------  华丽分割线 TMap 自定义key ------------
	// 自定义key
	TMap < FMyStruct, int32,
		FDefaultSetAllocator, TMyStructMapKeyFuncs < int32 >> MyMapToInt32;

	// Add some elements
	MyMapToInt32.Add(FMyStruct(3.14f), 5);
	MyMapToInt32.Add(FMyStruct(1.23f), 2);

	// MyMapToInt32 == [
	//  {
	//      Key: {
	//          UniqueID:  "D06AABBA466CAA4EB62D2F97936274E4",
	//          SomeFloat: 3.14f
	//      },
	//      Value: 5
	//  },
	//  {
	//      Key: {
	//          UniqueID:  "0661218447650259FD4E33AD6C9C5DCB",
	//          SomeFloat: 1.23f
	//      },
	//      Value: 5
	//  }
	// ]


}

static void testMultiMap()
{
	auto printFunc1 = [&](TMultiMap<int32, FString>& _map)->void {
		for (auto iter = _map.CreateConstIterator(); iter; ++iter)
		{
			UE_LOG(MyContaimTest, Warning, TEXT("--- key:%d, value111:%s "), iter->Key, *iter->Value);
		}
	};

	auto printFunc2 = [&](TMultiMap<int32, FString>& _map)->void {
		int32 a = 1;
		for (auto iter = _map.CreateIterator(); iter; ++iter)
		{
			if (a == 2)
			{
				iter.RemoveCurrent(); //移除当前的键值对，iter不为const才有这个方法
			}
			++a;
		}
	};

	//auto printFunc3 = [&](TMultiMap<int32, FString>& _map)->void {
	//	for (TMultiMap<uint8, FString>::TKeyIterator KeyIt(_map, 3); KeyIt; ++KeyIt)
	//	{
	//		KeyIt.RemoveCurrent();
	//	}

	//};

	//TODO: ------------------  华丽分割线 TArray 查 ------------
	TMultiMap<int32, FString> mtMap1;
	mtMap1.AddUnique(5, TEXT("aaa"));
	mtMap1.AddUnique(3, TEXT("bbb"));
	mtMap1.AddUnique(7, TEXT("ccc"));
	mtMap1.AddUnique(6, TEXT("ddd"));

	printFunc1(mtMap1);
	printFunc2(mtMap1);
	printFunc1(mtMap1);
}

void UMyBpFuncLib::TestBaseDataContain()
{
	//testArr1();
	//testArr2();
	//testArr3();

	//跟stl一样，Unreal有两种类型map: TMap和TMultiMap。
	//TMap相当于stl中的unorder_map,如果键为自定义结构体的话，需要重写hash方法，和==操作符
	//testMap1();
	testMultiMap();
}