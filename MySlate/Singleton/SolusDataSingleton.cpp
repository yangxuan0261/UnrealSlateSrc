#include "MySlate.h"
#include "SolusDataSingleton.h"

#include "Engine.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //初始化两个参数，另外两个等下蓝图中初始化
	SolusEssentialVector = FVector(900, 800, 700);
}

USolusDataSingleton* USolusDataSingleton::Get()
{
	USolusDataSingleton* DataInstance = Cast<USolusDataSingleton>(GEngine->GameSingleton); //这里指定配置文件中指定的单例类
	if (!DataInstance)
		return nullptr;
	else
		return DataInstance;
}
