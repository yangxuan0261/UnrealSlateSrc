
#pragma once

#include "../../Common/ISingleton.h"
#include "ObjMgr.generated.h"

class AMyChar;
class AMyBullet;
class UFightData;
class UPkProcess;
class UPkMsg;
class UParam;

class UCircleFilter;
class ULockFilter;
class URectFilter;

class UCoolDown;
class USkillFunction;

class UAppendBuff;
class UCommonBuff;

class UAddBuff;
class UAttack;
class UAttackPhy;
class USuckup;

UCLASS()
class UObjMgr : public UObject, public USingleton<UObjMgr>
{
	GENERATED_BODY()

public:
	UObjMgr();
	virtual ~UObjMgr();
	virtual void BeginDestroy() override;

public:
	template<typename TRetType>
	TRetType*		GetObj(UClass* _cls); //根据模板获取对象

	void			Recycle(UObject* _obj);
	auto&			GetObjMap() { return mObjMap; }

public:
	//蓝图对象类设置
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<AMyChar>		mCharCls; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<AMyBullet>		mBulletCls;

	//--------- pk Begin -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UFightData>		mFightDataCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UPkProcess>		mPkProcessCls; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UPkMsg>			mPkMsgCls; 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UParam>			mPkParamCls;
	//--------- pk End -----

	//--------- filter Begin -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UCircleFilter>	mCircleFltCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<ULockFilter>	mLockFltCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<URectFilter>	mRectFltCls;
	//--------- filter End -----

	
	//--------- skill Begin -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UCoolDown>	mCoolDownCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<USkillFunction>	mSkillFuncCls;
	//--------- skill End -----

	//--------- buff Begin -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UAppendBuff>	mAppBuffCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UCommonBuff>	mComBuffCls;
	//--------- buff End -----

	//--------- function Begin -----
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UAddBuff>		mAddBuffCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UAttack>		mAttackCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<UAttackPhy>		mAttackPhyCls;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "UObjMgr")
		TSubclassOf<USuckup>		mSuckupCls;
	//--------- function End -----

private:
	TMap<FString, TArray<UObject*>>		mObjMap; //对象回收池
};

#define GetObjMgr()			UObjMgr::GetInstance()