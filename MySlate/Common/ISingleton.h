
#pragma once

template<class T> 
class USingleton
{
public:
	USingleton() {};
	virtual ~USingleton() {};

public:
	static T* GetInstance()
	{
		return ManagerInstance();
	}
	static void	ReleaseInstance()
	{
		ManagerInstance( true );
	}
	static void SetInstance(UObject* _obj) //for system spawn obj
	{
		static T* m_sInstance = Cast<T>(_obj);
	}

protected:
	static T* ManagerInstance( bool destroy = false )
	{
		static T* m_sInstance = nullptr;

		if( destroy )
		{
			//delete m_sInstance;
			m_sInstance->RemoveFromRoot();
			m_sInstance->ConditionalBeginDestroy();
			m_sInstance = nullptr;
		}
		else
		{
			if( !m_sInstance )
			{
				//m_sInstance = new T();
				m_sInstance = NewObject<T>();
				m_sInstance->AddToRoot();
			}
		}

		return m_sInstance;
	}
};
