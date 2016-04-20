// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Common/ISingleton.h"
#include "GameTypes.h"

#include "CharMgr.generated.h"

class AMyChar;

UCLASS()
class UCharMgr : public UObject, public USingleton<UCharMgr>
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	UCharMgr();
	virtual ~UCharMgr();

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		AddChar(AMyChar* _char);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		AMyChar*	GetChar(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		RemoveChar(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetDestTeam(const ETeam& _atkTeam, int32 _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetIgnoreTeam(const ETeam& _atkTeam, int32 _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		GetIgnoreCharsByTeam(ETeam _type, UPARAM(ref) TArray<AMyChar*> _outChars) const;

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		TArray<AActor*>		ConvertCharsToActors(const TArray<AMyChar*> _srcChars);

	const TMap<int32, AMyChar*>&	GetAllChars() const { return mAllCharMap; }

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mSelfCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mTeamCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mEnemyCharArr;

private:
	TMap<int32, AMyChar*> mAllCharMap;
};
