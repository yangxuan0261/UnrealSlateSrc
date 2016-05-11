
#include "MySlate.h"
#include "SkillInfo.h"

FBulletInfo::FBulletInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBulletInfo::FBulletInfo construct"));
}

FBulletInfo::~FBulletInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FBulletInfo::~FBulletInfo"));
}

FSkillInfo::FSkillInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FSkillInfo::FSkillInfo construct"));
}

FSkillInfo::~FSkillInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FSkillInfo::~FSkillInfo"));
}


