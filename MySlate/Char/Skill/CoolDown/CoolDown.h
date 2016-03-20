// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"

#include "CoolDown.generated.h"

class AMyChar;
class USkillTemplate;

UCLASS()
class UCoolDown : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCoolDown();
	virtual ~UCoolDown();


	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		bool		IsOK();
	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		float		GetCDTimer();
	void			SetCDTimer(float timer);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		int32		GetSkillId();
	void			SetSkillId(int32 _id);

	void			SetSkillTemplate(USkillTemplate* _skillTemplate);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		ESkillType::Type	GetType();
	void			SetType(ESkillType::Type _type);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		UseSkill(AMyChar* _attActor, int32 _targetId);

	void			Restart();
	bool			IsNull();
	virtual void Tick(float DeltaTime);

private:
	USkillTemplate*		mSkillTemplate;
	ESkillType::Type	mType;
	int32		mSkillId;
	float		mCDTime;//cd时间
	float		mTimer;//cd计时
	float		mRatio;//
	bool		mIsOK;//
};

FORCEINLINE bool	UCoolDown::IsOK() { return mIsOK; }
FORCEINLINE float	UCoolDown::GetCDTimer() { return mCDTime; }
FORCEINLINE void	UCoolDown::SetCDTimer(float timer) { mCDTime = timer; }
FORCEINLINE int32	UCoolDown::GetSkillId() { return mSkillId; }
FORCEINLINE void	UCoolDown::SetSkillId(int32 _id) { mSkillId = _id; }
FORCEINLINE bool	UCoolDown::IsNull() { return mSkillId == -1 ? true : false; }
FORCEINLINE void	UCoolDown::SetType(ESkillType::Type _type) { mType = _type; }
FORCEINLINE ESkillType::Type	UCoolDown::GetType() { return mType; }