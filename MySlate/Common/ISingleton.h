
#pragma once

//#include "MySlate.h"
//#include "ISingleton.generated.h"

template<class T> 
class USingleton
{
public:
	static T* GetInstance()
	{
		return ManagerInstance();
	}
	static void	ReleaseInstance()
	{
		ManagerInstance( true );
	}

protected:

	static T* ManagerInstance( bool destroy = false )
	{
		static T* m_sInstance; //

		if( destroy )
		{
			//delete m_sInstance;
			m_sInstance->RemoveFromRoot();
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

	virtual ~USingleton() {};
	USingleton() {};
};
