#include "StdAfx.h"
#include "DataCenter.h"

template<>
CDataCenter * SSingleton<CDataCenter>::ms_Singleton = NULL;

CDataCenter::CDataCenter(void)
{
	//处理local_ip
	char szHostName[128];
	gethostname(szHostName,128);					
	HOSTENT* p = gethostbyname(szHostName);

	std::string strName = p->h_name;

	for (int i = 0; p->h_addr_list[i] != 0; i++)
	{
		struct in_addr in;
		memcpy(&in, p->h_addr_list[i], sizeof(struct in_addr));
		std::string strHost = inet_ntoa(in);
		int j = 0;
	}

	m_LocalInfo.m_strName = strName;
	m_LocalInfo.m_nPort = PORT_DUODUO;
	m_LocalInfo.m_strClientID = GenerateUUID();

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
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnFindDevice(EventArgs* e)
{
	EventFindDevice* pEvt = sobj_cast<EventFindDevice>(e);
	if (pEvt)
	{
		//去重处理
		ClientInfoMap::iterator iter = m_mapClients.find(pEvt->m_strClientID);
		if (iter == m_mapClients.end())
		{
			m_mapClients.insert(std::make_pair(pEvt->m_strClientID, 
				CLIENT_INFO(pEvt->m_strName, pEvt->m_strIP, pEvt->m_strClientID, pEvt->m_nPort)));
		}

		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnBroadcastRequest(EventArgs* e)
{
	EventBroadcastRequest* pEvt = sobj_cast<EventBroadcastRequest>(e);
	if (pEvt)
	{
		//去重处理
		ClientInfoMap::iterator iter = m_mapClients.find(pEvt->m_strClientID);
		if (iter == m_mapClients.end())
		{
			m_mapClients.insert(std::make_pair(pEvt->m_strClientID, 
				CLIENT_INFO(pEvt->m_strName, pEvt->m_strIP, pEvt->m_strClientID, pEvt->m_nPort)));
		}

		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnSendText(EventArgs* e)
{
	EventSendText* pEvt = sobj_cast<EventSendText>(e);
	if (pEvt)
	{
		//将消息存入内存中的最近会话map中    或者该操作后续处理
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnSendImage(EventArgs* e)
{
	EventSendImage* pEvt = sobj_cast<EventSendImage>(e);
	if (pEvt)
	{
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnSendFile(EventArgs* e)
{
	EventSendFile* pEvt = sobj_cast<EventSendFile>(e);
	if (pEvt)
	{
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnSendAudio(EventArgs* e)
{
	EventSendAudio* pEvt = sobj_cast<EventSendAudio>(e);
	if (pEvt)
	{
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

void CDataCenter::OnSendVideo(EventArgs* e)
{
	EventSendVideo* pEvt = sobj_cast<EventSendVideo>(e);
	if (pEvt)
	{
		pEvt->bubbleUp = true;
		ReFireEventSync(pEvt);
	}
}

std::string CDataCenter::GenerateUUID()
{
	char szbuf[100];
	GUID guid;
	::CoCreateGuid(&guid);
	sprintf(szbuf,
		"%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X",
		guid.Data1,
		guid.Data2,
		guid.Data3,
		guid.Data4[0], guid.Data4[1],
		guid.Data4[2], guid.Data4[3],
		guid.Data4[4], guid.Data4[5],
		guid.Data4[6], guid.Data4[7]);

	std::string strUUID = szbuf;
	return strUUID;
}