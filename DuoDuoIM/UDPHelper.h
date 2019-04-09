#pragma once

#include <core/SSingleton.h>
#include <helper/SCriticalSection.h>
#include <interface/STaskLoop-i.h>
#include <helper/SFunctor.hpp>

#include "DataCenter.h"

typedef rapidjson::GenericStringBuffer<rapidjson::UTF8<>, rapidjson::MemoryPoolAllocator<> > MPAStringBuffer;

//header定义
typedef struct _tagHeader
{
	int m_nHeadLen;
	DWORD m_nProtocolVersion;
	int m_nBodyLen;
}HEADER, *LPHEADER;

//标准数据包定义
typedef struct _tagGenPacket
{
	HEADER	m_header;
	char	m_szData[2048];
}GENPACKET, *LPGENPACKET;

class CUDPSendThread
{
public:
	CUDPSendThread(SComMgr &comMgr, std::string strName);
	~CUDPSendThread();

	bool cancelTask(long taskId){
		return m_pTaskLoop->cancelTask(taskId);
	}

	long SendBroadcast(const std::string& strName, const std::string& strClientID, int& nPort, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendBroadcast, strName, strClientID, nPort, false, nPriority);
	}

	long SendBroadcastRequest(const std::string& strRemoteIP, const std::string& strName, const std::string& strClientID, int& nPort, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendBroadcastRequest, strRemoteIP, strName, strClientID, nPort, false, nPriority);
	}

	long SendText(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendText, strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, false, nPriority);
	}

	long SendImage(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendText, strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, false, nPriority);
	}

	long SendFile(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendText, strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, false, nPriority);
	}

	long SendAudio(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendText, strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, false, nPriority);
	}

	long SendVideo(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPSendThread::_SendText, strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, false, nPriority);
	}

protected:
	void _SendBroadcast(const std::string& strName, const std::string& strClientID, int& nPort);
	void _SendBroadcastRequest(const std::string& strRemoteIP, const std::string& strName, const std::string& strClientID, int& nPort);
	void _SendText(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent);
	void _SendImage(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent);
	void _SendFile(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent);
	void _SendAudio(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent);
	void _SendVideo(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent);
private:
	CAutoRefPtr<ITaskLoop>	m_pTaskLoop;
	SOCKET					m_sockClient; //客户端SOCKET句柄
};

class CUDPSender : public SSingleton<CUDPSender>
{
public:
	CUDPSender(void);
	~CUDPSender(void);

	bool cancelTask(long taskID);

public:
	void SendBroadcast(const std::string& strName, const std::string& strClientID, int& nPort, int nPriority = 1);
	void SendBroadcastRequest(const std::string& strRemoteIP, const std::string& strName, const std::string& strClientID, int& nPort, int nPriority = 1);
	void SendText(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendImage(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendFile(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendVideo(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
	void SendAudio(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority = 1);
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
		return m_pTaskLoop->cancelTask(taskId);
	}

	long StartUDPRecv(int nPriority = 1){
		return STaskHelper::post(m_pTaskLoop, this, &CUDPRecvThread::_StartUDPRecv, false, nPriority);
	}

protected:
	void _StartUDPRecv();
	
	bool InitServer();
private:
	void processSvrData(const rapidjson::Value& data, std::string strIP = "", int nPort = -1);
	void ProcessFindDevice(const rapidjson::Value& data, std::string strIP = "", int nPort = -1);
	void ProcessBroadcastResponse(const rapidjson::Value& data, std::string strIP = "", int nPort = -1);
	void ProcessSendText(const rapidjson::Value& data);
	void ProcessSendImage(const rapidjson::Value& data);
	void ProcessSendFile(const rapidjson::Value& data);
	void ProcessSendAudio(const rapidjson::Value& data);
	void ProcessSendVideo(const rapidjson::Value& data);
private:
	CAutoRefPtr<ITaskLoop> m_pTaskLoop;

	bool	m_bRun;

	SOCKET	m_SvrSocket; // 服务器端SOCKET句柄

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