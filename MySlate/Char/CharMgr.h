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

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mSelfCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mTeamCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mEnemyCharArr;
};
