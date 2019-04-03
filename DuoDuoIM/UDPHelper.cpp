#include "StdAfx.h"
#include "UDPHelper.h"

template<>
CUDPHelper * SSingleton<CUDPHelper>::ms_Singleton = NULL;

/////////////////////////////////////////////////////////////////////////////////

CUDPHelperThread::CUDPHelperThread(SComMgr &comMgr, std::string strName)
{
	comMgr.CreateTaskLoop((IObjRef**)&m_pTaskLoop);
	SASSERT(m_pTaskLoop);
	m_pTaskLoop->start(strName.c_str(), ITaskLoop::Low);
}

CUDPHelperThread::~CUDPHelperThread()
{
	m_pTaskLoop->stop();
}

void CUDPHelperThread::_SendBroadcast(const std::string& strBroadcastData)
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_BORDCAST);
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255"); //广播地址

	//设置该套接字为广播类型，
	DWORD optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(DWORD)); //设置套接字选项

	DWORD dwDataLen = strBroadcastData.length();

	sendto(sock, strBroadcastData.c_str(), dwDataLen + 8, 0, (SOCKADDR*)&addr,sizeof(SOCKADDR));

	closesocket(sock);
}
////////////////////////////////////////////////////////////////////////////////

CUDPHelper::CUDPHelper(void)
{
	m_pThread = new CUDPHelperThread(m_comMgr, "udp_thread");
}

CUDPHelper::~CUDPHelper(void)
{
	delete m_pThread;
}

bool CUDPHelper::cancelTask(long taskID)
{
	return m_pThread->cancelTask(taskID);
}

void CUDPHelper::SendBroadcast(const std::string& strBroadcastData, int nPriority /* = 1 */)
{
	m_pThread->SendBroadcast(strBroadcastData, nPriority);
}