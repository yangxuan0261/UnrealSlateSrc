
#include "MySlate.h"
#include "SkillInfo.h"

FSkillInfo::FSkillInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FSkillInfo::FSkillInfo construct"));
}

FSkillInfo::~FSkillInfo()
{
	UE_LOG(ResLogger, Warning, TEXT("--- FSkillInfo::~FSkillInfo"));
}

