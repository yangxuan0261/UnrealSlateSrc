
#include "MySlate.h"
#include "BuffMgr.h"

#include "../../MyChar.h"
#include "./Buffs/AbsBuff.h"
#include "./Buffs/AppendBuff.h"
#include "./Buffs/CommonBuff.h"
#include "../Utils/SkillDataMgr.h"
#include "../Template/BufflTemplate.h"
#include "../SkillTypes.h"


UBuffMgr::UBuffMgr() : Super()
{

}

UBuffMgr::~UBuffMgr()
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::~UBuffMgr"));
}

void UBuffMgr::BeginDestroy()
{
	for (auto Iter = mBuffs.CreateIterator(); Iter; ++Iter)
	{
		for (UAbsBuff* tempBuff : Iter->Value)
		{
			tempBuff->RemoveFromRoot();
			tempBuff->ConditionalBeginDestroy();
		}
		Iter->Value.Empty();
	}
	mBuffs.Empty();

	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::BeginDestroy"));
	Super::BeginDestroy();
}

void UBuffMgr::Tick(float DeltaTime)
{
	UAbsBuff* buff = nullptr;
	for (auto Iter = mBuffs.CreateIterator(); Iter; ++Iter)
	{
		TArray<UAbsBuff*>&	buffs = Iter->Value;
		for (int32 i = 0;i < buffs.Num(); i++)
		{
			buff = buffs[i];
			if (buff->GetState() == EBuffState::Start)
			{
				buff->Tick(DeltaTime);//更新buffer
			}
			else if (buff->GetState() == EBuffState::Over
				|| buff->GetState() == EBuffState::Break) //Break暂时无用
			{
				ForceOver(buffs, buff, true);
				if (buffs.Num() == 0)
				{
					Iter.RemoveCurrent();
				}
			}
		}
	}
}

bool UBuffMgr::IsTickable() const
{
	return true;
}

TStatId UBuffMgr::GetStatId() const
{
	return TStatId();
}

void UBuffMgr::RunBeforePkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::RunEndPkBuffs(int32 _charId, UPkMsg* msg)
{

}

void UBuffMgr::AddBuff(AMyChar* _attacker, AMyChar* _target, int32 _skillId, int32 _buffId)
{
	UBufflTemplate* buffTemp = USkillDataMgr::GetInstance()->GetBuffTemplate(_buffId);
	if (buffTemp != nullptr && _target != nullptr)
	{
		int32 targetId = _target->GetUuid();
		UAbsBuff* beAdd = nullptr;
		if (buffTemp->mCanAdd) //叠加buff
		{
			beAdd = NewObject<UAppendBuff>(UAppendBuff::StaticClass());
		}
		else
		{
			beAdd = NewObject<UCommonBuff>(UCommonBuff::StaticClass());
		}
		beAdd->SetData(buffTemp, _attacker, _target, _skillId);

		TArray<UAbsBuff*>* buffs = mBuffs.Find(targetId);
		if (buffs != nullptr)
		{
			UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
				return _buff->GetBuffId() == _buffId; 
			});

			if (buff != nullptr)//原来已存在这个buffId
			{
				UAppendBuff* appBuff = Cast<UAppendBuff>(*buff);
				if (appBuff != nullptr)//存在的buff是缀加的，把缀加数据丢到进去，释放新创建的
				{
					appBuff->AppendBuff(beAdd);
					beAdd->ConditionalBeginDestroy(); 
				}
				else //不可缀加，去旧迎新
				{
					//UAbsBuff* tmpBuff = *buff;
					//tmpBuff->BuffOver();
					//buffs->Remove(tmpBuff);//非常重要：删除是必须把*buff赋值给一个临时对象，不然地址检查不通过导致崩溃
					//tmpBuff->RemoveFromRoot();
					//tmpBuff->ConditionalBeginDestroy();

					(*buff)->ChangeState(EBuffState::Over);

					beAdd->AddToRoot();
					beAdd->BuffStart();
					buffs->Add(beAdd);
				}
			}
			else
			{
				beAdd->AddToRoot();
				beAdd->BuffStart();
				buffs->Add(beAdd);
			}
		}
		else
		{
			beAdd->AddToRoot();
			beAdd->BuffStart();

			TArray<UAbsBuff*> tmpBuffs;
			tmpBuffs.Add(beAdd);
			mBuffs.Add(targetId, tmpBuffs);
		}
	}
	else
	{
		UE_LOG(BuffLogger, Error, TEXT("--- UBuffMgr::AddBuff, buff template == nullptr, id:%d"), _buffId);
	}
}

UAbsBuff* UBuffMgr::FindBuff(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
			return _buff->GetBuffId() == _buffId; 
		});

		return buff != nullptr ? *buff : nullptr;
	}
	return nullptr;
}

void UBuffMgr::ForceOver(TArray<UAbsBuff*>& _buffArr, UAbsBuff* _buff, bool remove /* = false */)
{
	_buff->BuffOver();
	_buff->RemoveFromRoot();
	_buff->ConditionalBeginDestroy();
	if (remove)
	{
		_buffArr.Remove(_buff);
	}
}

//移除某个角色身上的所有buff
void UBuffMgr::RemoveBuff(int32 _charId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		for (UAbsBuff* buff : *buffs)
		{
			ForceOver(*buffs, buff);
		}
		buffs->Empty();
		mBuffs.Remove(_charId);
	}
}

//移除某个角色身上的某个具体buff
void UBuffMgr::RemoveBuffSpec(int32 _charId, int32 _buffId)
{
	TArray<UAbsBuff*>* buffs = mBuffs.Find(_charId);
	if (buffs != nullptr)
	{
		UAbsBuff** buff = buffs->FindByPredicate([&](const UAbsBuff* _buff)->bool {
			return _buff->GetBuffId() == _buffId; 
		});

		if (buff != nullptr)
		{
			ForceOver(*buffs, *buff, true);
			if (buffs->Num() == 0)
			{
				mBuffs.Remove(_charId);
			}
			UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::RemoveBuffSpec, buffId:%d"), (*buff)->GetBuffId());
		}
	}
}

void UBuffMgr::CharDeathNotify(AMyChar* _char)
{
	UE_LOG(BuffLogger, Warning, TEXT("--- UBuffMgr::CharDeathNotify, char death, uuid:%d"), _char->GetUuid());

	RemoveBuff(_char->GetUuid());
}
