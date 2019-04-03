#pragma once

#include <core/SSingleton.h>

class CDataCenter : public SObject
	, public SSingleton<CDataCenter>
	, public TAutoEventMapReg<CDataCenter>
{
	SOUI_CLASS_NAME(CDataCenter, L"DataCenter")

	enum { ObjectId = 65500 };

	virtual int GetID() const{
		return ObjectId;
	}
public:
	CDataCenter(void);
	~CDataCenter(void);

private:
	EVENT_MAP_BEGIN()
	EVENT_MAP_BREAK()

	template<class T>
	void ReFireEventSync(T*srcArgs)
	{
		T reArgs = *srcArgs;
		reArgs.handled = 0;
		reArgs.bubbleUp = true;
		reArgs.idFrom = GetID();
		reArgs.nameFrom = GetName();
		reArgs.sender = this;
		SNotifyCenter::getSingletonPtr()->FireEventSync(&reArgs);
	}

public:
	DWORD*	m_pdwLocalIP;
};
