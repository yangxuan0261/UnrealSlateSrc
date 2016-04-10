// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Char/Skill/SkillTypes.h"

#include "CoolDown.generated.h"

//cd finish notify Char
class UCoolDown;
DECLARE_DELEGATE_OneParam(FCDFinishDlg, UCoolDown*);

class AMyChar;
class USkillTemplate;
class UCoolDownComp;
class USkillFunction;

UCLASS()
class UCoolDown : public UObject
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCoolDown();
	virtual ~UCoolDown();

	virtual void BeginDestroy() override;

public:
	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		bool		IsOK() const { return mIsOK; }
	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		float		GetCDTimer() const { return mCDTime; }
	void			SetCDTimer(float timer) { mCDTime = timer; }

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		int32		GetSkillId() const { return mSkillId; }

	void			SetSkillTemplate(USkillTemplate* _skillTemp);

	void			SetChar(AMyChar* _owner);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		UseSkill(AMyChar* _attActor, int32 _targetId);

	UFUNCTION(BlueprintCallable, Category = "UCoolDown")
		void		SetRatio(float _ratio) { mRatio = _ratio; }

	void			Restart();
	bool			IsNull() const { return mSkillId == -1 ? true : false; }

	virtual void Tick(float DeltaTime);

public:
	int32		mSkillId;
	float		mCDTime;//cd时间
	float		mTimer;//cd计时
	float		mRatio;//比例，用于加快cd
	bool		mIsOK;//

	USkillTemplate*		mSkillTemplate;
	USkillFunction*		mSkillFunc;
	AMyChar*	mOwnerChar;

	FCDFinishDlg				mCDFinishDlg;//通知代理
};