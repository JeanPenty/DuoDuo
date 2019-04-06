#include "StdAfx.h"
#include "DataCenter.h"

template<>
CDataCenter * SSingleton<CDataCenter>::ms_Singleton = NULL;

CDataCenter::CDataCenter(void)
{
	//处理local_ip
	char szHostName[128];
	gethostname(szHostName,128);
	HOSTENT* phe = gethostbyname(szHostName);
	int i = 0;
	while(phe->h_addr_list[i]) i++;
	m_pdwLocalIP = new DWORD[i+1];
	i=0;
	while(phe->h_addr_list[i]){
		memcpy(m_pdwLocalIP + i, phe->h_addr_list[i], 4);
		i++;
	}
	m_pdwLocalIP[i] = 0;

	//处理本机信息(用于广播时向网内其他设备发送)


	SNotifyCenter::getSingleton().addEvent(EVENTID(EventBindPortFailed));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventFindDevice));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventBroadcastRequest));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventSendText));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventSendImage));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventSendFile));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventSendAudio));
	SNotifyCenter::getSingleton().addEvent(EVENTID(EventSendVideo));
}

CDataCenter::~CDataCenter(void)
{
}

void CDataCenter::OnBindBroadcastPortFailed(EventArgs* e)
{
	EventBindPortFailed* pEvt = sobj_cast<EventBindPortFailed>(e);
	if (pEvt)
	{
		//提示绑定端口号失败！
		//退出进程
	}
}

void CDataCenter::OnFindDevice(EventArgs* e)
{
	EventFindDevice* pEvt = sobj_cast<EventFindDevice>(e);
	if (pEvt)
	{
		//
	}
}

void CDataCenter::OnBroadcastRequest(EventArgs* e)
{
	EventBroadcastRequest* pEvt = sobj_cast<EventBroadcastRequest>(e);
	if (pEvt)
	{
		//
	}
}

void CDataCenter::OnSendText(EventArgs* e)
{
	EventSendText* pEvt = sobj_cast<EventSendText>(e);
	if (pEvt)
	{
		//
	}
}

void CDataCenter::OnSendImage(EventArgs* e)
{
	EventSendImage* pEvt = sobj_cast<EventSendImage>(e);
	if (pEvt)
	{
	}
}

void CDataCenter::OnSendFile(EventArgs* e)
{
	EventSendFile* pEvt = sobj_cast<EventSendFile>(e);
	if (pEvt)
	{
	}
}

void CDataCenter::OnSendAudio(EventArgs* e)
{
	EventSendAudio* pEvt = sobj_cast<EventSendAudio>(e);
	if (pEvt)
	{
	}
}

void CDataCenter::OnSendVideo(EventArgs* e)
{
	EventSendVideo* pEvt = sobj_cast<EventSendVideo>(e);
	if (pEvt)
	{
	}
}