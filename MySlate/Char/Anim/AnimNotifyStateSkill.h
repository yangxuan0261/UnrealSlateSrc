
#pragma once

#include "AnimNotifyStateSkill.generated.h"

class AMyChar;

UCLASS()
class UAnimNotifyStateSkill : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	UAnimNotifyStateSkill();
	virtual ~UAnimNotifyStateSkill();

public:
	virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;
	virtual void NotifyTick(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float FrameDeltaTime) override;
	virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;

public:
	AMyChar*		mOwnerChar;

};