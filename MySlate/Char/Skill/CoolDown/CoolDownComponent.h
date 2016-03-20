// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"
#include "Tickable.h"
#include "Char/Skill/SkillTypes.h"

#include "CoolDownComponent.generated.h"

class UCoolDown;
class AMyChar;

UCLASS()
class UCoolDownComponent : public UActorComponent
{
	GENERATED_UCLASS_BODY()

public:
	// Sets default values for this character's 
	virtual ~UCoolDownComponent();

public:
	// Begin UActorComponent Interface.
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	// End UActorComponent Interface.

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		SetOwner(AMyChar* _owner);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		CreateCD(int32 _skillId, TSubclassOf<UCoolDown> _class); //可以把蓝图类传进来

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		UseSkill(int32 _skillId, int32 _targetId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		RestartCD(int32 _skillId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		RemoveCDByType(ESkillType::Type _skillType);

	UFUNCTION(BlueprintCallable, Category = "UCoolDownComponent")
		void		AddCD(ESkillType::Type _skillType, int32 _skillId, bool _isRestartCD);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComponent")
		TArray<UCoolDown*>		mCDArr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCoolDownComponent")
		AMyChar*				mOwner;

};

FORCEINLINE void UCoolDownComponent::SetOwner(AMyChar* _owner) { mOwner = _owner; }
