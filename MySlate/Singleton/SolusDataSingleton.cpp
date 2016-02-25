#include "MySlate.h"
#include "SolusDataSingleton.h"

#include "Engine.h"
#include "Engine/StreamableManager.h"
#include "Singleton/SolusDataSingleton.h"
#include "Singleton/ItemInfoDatabase.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //初始化两个参数，另外两个等下蓝图中初始化
	SolusEssentialVector = FVector(900, 800, 700);
	AssetLoader = new FStreamableManager();

	//加载itemDataBase蓝图
	UObject* obj = AssetLoader->SynchronousLoad(FStringAssetReference(TEXT("/Game/TopDownCPP/MeshItems/MeshDateBaseBP")));
	ItemDatabase = Cast<UItemInfoDatabase>(obj);
}

USolusDataSingleton::~USolusDataSingleton()
{
	if (AssetLoader)
		delete AssetLoader;
}

USolusDataSingleton* USolusDataSingleton::Get()
{
	USolusDataSingleton* DataInstance = Cast<USolusDataSingleton>(GEngine->GameSingleton); //这里指定配置文件中指定的单例类
	if (!DataInstance)
		return nullptr;
	else
		return DataInstance;
}
