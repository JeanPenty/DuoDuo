#pragma once

#include <core/SSingleton.h>

#include "public.h"

#include "EventsDefine.h"

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
	void OnBindBroadcastPortFailed(EventArgs* e);
	void OnFindDevice(EventArgs* e);
	void OnBroadcastRequest(EventArgs* e);
	void OnSendText(EventArgs* e);
	void OnSendImage(EventArgs* e);
	void OnSendFile(EventArgs* e);
	void OnSendAudio(EventArgs* e);
	void OnSendVideo(EventArgs* e);

private:
	EVENT_MAP_BEGIN()
		EVENT_ID_HANDLER(0, EventBindPortFailed::EventID, OnBindBroadcastPortFailed)
		EVENT_ID_HANDLER(0, EventFindDevice::EventID, OnFindDevice)
		EVENT_ID_HANDLER(0, EventBroadcastRequest::EventID, OnBroadcastRequest)
		EVENT_ID_HANDLER(0, EventSendText::EventID, OnSendText)
		EVENT_ID_HANDLER(0, EventSendImage::EventID, OnSendImage)
		EVENT_ID_HANDLER(0, EventSendFile::EventID, OnSendFile)
		EVENT_ID_HANDLER(0, EventSendAudio::EventID, OnSendAudio)
		EVENT_ID_HANDLER(0, EventSendVideo::EventID, OnSendVideo)
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
	std::string GenerateUUID();
public:
	CLIENT_INFO	m_LocalInfo;

	ClientInfoMap	m_mapClients;
};
