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

UObject* UMyBpFuncLib::TestAsyncLoad(AMyChar* _myChar, UItemInfoDatabase* _database)
{
	if (!_myChar || !_database)
		return nullptr;

	FStringAssetReference HeadAssetToLoad;
	TArray<FStringAssetReference> ObjToLoad;
	FStreamableManager& BaseLoader = USolusDataSingleton::Get()->AssetLoader;
	for (int32 i = 0; i < _database->MeshList.Num(); ++i)
	{
		ObjToLoad.AddUnique(_database->MeshList[i].MeshResource.ToStringReference());
	}
	BaseLoader.RequestAsyncLoad(ObjToLoad, FStreamableDelegate::CreateUObject(_myChar, &AMyChar::TestAsyncLoad));

	return nullptr;
}

UItemInfoDatabase* UMyBpFuncLib::TestLoadBPObject(FString _path)
{
	auto cls = StaticLoadObject(UObject::StaticClass(), nullptr, *_path);
	return Cast<UItemInfoDatabase>(cls);
}