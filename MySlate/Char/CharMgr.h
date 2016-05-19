
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
		void		RemoveChar(AMyChar* _target);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetDestTeam(ETeam _atkTeam, ESelectType _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		ETeam		GetIgnoreTeam(ETeam _atkTeam, ESelectType _flag);//根据标记获取目的队伍标记

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		UCharData*	GetCharData(int32 _id);

	UFUNCTION(BlueprintCallable, Category = "UCharMgr")
		void		LoadCharData();

	void			GetDstCharVec(ETeam _dstType, float _radius, const FVector& _loc, TArray<AMyChar*>&	_outCharVec);
	AMyChar*		GetCloseChar(const TArray<AMyChar*>& _inVec, const FVector& _loc);
	const TMap<ETeam, TMap<int32, AMyChar*>>&	GetAllChars() const { return mGroupCharMap; }

private:
	TMap<int32, UCharData*> mCharDataMap;

	TMap<ETeam, TMap<int32, AMyChar*>>	mGroupCharMap;
};

#define gGetCharMgr()			UCharMgr::GetInstance()