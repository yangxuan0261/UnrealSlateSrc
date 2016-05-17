
#pragma once

#include "../Common/ISingleton.h"
#include "./CharTypes.h"
#include "./Skill/SkillTypes.h"

#include "CharMgr.generated.h"

class AMyChar;
class UCharData;

UCLASS()
class UCharMgr : public UObject, public USingleton<UCharMgr>
{
	GENERATED_BODY()

public:
	UCharMgr();
	virtual ~UCharMgr();
	virtual void BeginDestroy() override;

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		AddChar(AMyChar* _char);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		AMyChar*	GetChar(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		RemoveChar(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetDestTeam(ETeam _atkTeam, ESelectType _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetIgnoreTeam(ETeam _atkTeam, ESelectType _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		GetIgnoreCharsByTeam(ETeam _type, UPARAM(ref) TArray<AMyChar*>& _outChars) const;

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		ConvertCharsToActors(UPARAM(ref) const TArray<AMyChar*>& _srcChars, TArray<AActor*>& _outActors);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		ConvertActorsToChars(UPARAM(ref) const TArray<AActor*>& _srcActors, TArray<AMyChar*>& _outChars);

	const TMap<int32, AMyChar*>&	GetAllChars() const { return mAllCharMap; }

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		UCharData*	GetCharData(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		LoadCharData();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mSelfCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mTeamCharArr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UCharManager")
		TArray<AMyChar*>		mEnemyCharArr;

private:
	TMap<int32, AMyChar*> mAllCharMap;
	TMap<int32, UCharData*> mCharDataMap;
};

#define gGetCharMgr()			UCharMgr::GetInstance()