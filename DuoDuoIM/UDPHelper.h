#pragma once

#include <core/SSingleton.h>
#include <helper/SCriticalSection.h>
#include <interface/STaskLoop-i.h>
#include <helper/SFunctor.hpp>

#include "DataCenter.h"

typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> > MPAStringBuffer;

class CUDPSendThread
{
public:
	CUDPSendThread(SComMgr &comMgr, std::string strName);
	~CUDPSendThread();

	bool cancelTask(long taskId){
		return m_pTaskLoop->cancelTask(taskId);
	}

	long SendBroadcast(const std::string& strBroadcastData, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendBroadcast, strBroadcastData, false, nPriority);
	}

protected:
	void _SendBroadcast(const std::string& strBroadcastData);

private:
	CAutoRefPtr<ITaskLoop> m_pTaskLoop;
};

class CUDPSender : public SSingleton<CUDPSender>
{
public:
	CUDPSender(void);
	~CUDPSender(void);

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
	CUDPSendThread*	m_pThread;
	SComMgr				m_comMgr;
	DWORD*				m_pdwLocalIP;
};


/////////////////////////////////////////////////////////////////////////////////////////////////
class CUDPRecvThread
{
public:
	CUDPRecvThread(SComMgr &comMgr, std::string strName);
	~CUDPRecvThread();

	bool cancelTask(long taskId){
		m_bRun = false;
		return m_pTaskLoop->cancelTask(taskId);
	}

	long StartUDPRecv(int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPRecvThread::_StartUDPRecv, false, nPriority);
	}

protected:
	void _StartUDPRecv();
	
private:
	void processSvrData(const rapidjson::Value& data);
	void ProcessFindDevice(const rapidjson::Value& data);
	void ProcessBroadcastResponse(const rapidjson::Value& data);
	void ProcessSendText(const rapidjson::Value& data);
	void ProcessSendImage(const rapidjson::Value& data);
	void ProcessSendFile(const rapidjson::Value& data);
	void ProcessSendAudio(const rapidjson::Value& data);
	void ProcessSendVideo(const rapidjson::Value& data);
private:
	CAutoRefPtr<ITaskLoop> m_pTaskLoop;

	bool	m_bRun;

	//json解析
#define PARSEBUFFER_SIZE 8192 //8k
	char m_parseBuffer[PARSEBUFFER_SIZE];
	rapidjson::MemoryPoolAllocator<> m_parseAllocator;

	//json打包
#define BUILDBUFFER_SIZE 8192 //8k
	char m_buildBuffer[BUILDBUFFER_SIZE];
	rapidjson::MemoryPoolAllocator<> m_buildAllocator;
};

class CUDPRecver : public SSingleton<CUDPRecver>
{
public:
	CUDPRecver(void);
	~CUDPRecver(void);

	bool cancelTask(long taskID);

public:
	void StartUDPRecv(int nPriority = 1);
private:
	CUDPRecvThread*		m_pThread;
	SComMgr				m_comMgr;

	//json解析
#define PARSEBUFFER_SIZE 8192 //8k
	char m_parseBuffer[PARSEBUFFER_SIZE];
	rapidjson::MemoryPoolAllocator<> m_parseAllocator;

	//json打包
#define BUILDBUFFER_SIZE 8192 //8k
	char m_buildBuffer[BUILDBUFFER_SIZE];
	rapidjson::MemoryPoolAllocator<> m_buildAllocator;
};