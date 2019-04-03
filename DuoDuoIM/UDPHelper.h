#pragma once

#include <core/SSingleton.h>
#include <helper/SCriticalSection.h>
#include <interface/STaskLoop-i.h>
#include <helper/SFunctor.hpp>

#include "DataCenter.h"

class CUDPHelperThread
{
public:
	CUDPHelperThread(SComMgr &comMgr, std::string strName);
	~CUDPHelperThread();

	bool cancelTask(long taskId){
		return m_pTaskLoop->cancelTask(taskId);
	}

	long SendBroadcast(const std::string& strBroadcastData, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPHelperThread::_SendBroadcast, strBroadcastData, false, nPriority);
	}

protected:
	void _SendBroadcast(const std::string& strBroadcastData);

private:
	CAutoRefPtr<ITaskLoop> m_pTaskLoop;
};

class CUDPHelper : public SSingleton<CUDPHelper>
{
public:
	CUDPHelper(void);
	~CUDPHelper(void);

	bool cancelTask(long taskID);

public:
	void SendBroadcast(const std::string& strBroadcastData, int nPriority = 1);
	void SendText(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendImage(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendFile(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendVideo(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendAudio(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	//void SendImage(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	//void SendImage(const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
private:
	CUDPHelperThread*	m_pThread;
	SComMgr				m_comMgr;
	DWORD*				m_pdwLocalIP;
};
