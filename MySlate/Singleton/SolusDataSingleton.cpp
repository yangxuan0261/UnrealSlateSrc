#include "MySlate.h"
#include "SolusDataSingleton.h"

USolusDataSingleton::USolusDataSingleton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	SolusCoreFilePath = "I am Mr. Yang"; //初始化两个参数，另外两个等下蓝图中初始化
	SolusEssentialVector = FVector(900, 800, 700);
}