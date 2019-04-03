#include "StdAfx.h"
#include "UDPHelper.h"

template<>
CUDPSender* SSingleton<CUDPSender>::ms_Singleton = NULL;
CUDPRecver* SSingleton<CUDPRecver>::ms_Singleton = NULL;

/////////////////////////////////////////////////////////////////////////////////

CUDPSendThread::CUDPSendThread(SComMgr &comMgr, std::string strName)
{
	comMgr.CreateTaskLoop((IObjRef**)&m_pTaskLoop);
	SASSERT(m_pTaskLoop);
	m_pTaskLoop->start(strName.c_str(), ITaskLoop::Low);
}

CUDPSendThread::~CUDPSendThread()
{
	m_pTaskLoop->stop();
}

void CUDPSendThread::_SendBroadcast(const std::string& strBroadcastData)
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255"); //广播地址

	//设置该套接字为广播类型，
	DWORD optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(DWORD)); //设置套接字选项

	DWORD dwDataLen = strBroadcastData.length();

	sendto(sock, strBroadcastData.c_str(), dwDataLen + 8, 0, (SOCKADDR*)&addr,sizeof(SOCKADDR));

	closesocket(sock);
}
////////////////////////////

CUDPSender::CUDPSender(void)
{
	m_pThread = new CUDPSendThread(m_comMgr, "udp_sender");
}

CUDPSender::~CUDPSender(void)
{
	delete m_pThread;
}

bool CUDPSender::cancelTask(long taskID)
{
	return m_pThread->cancelTask(taskID);
}

void CUDPSender::SendBroadcast(const std::string& strBroadcastData, int nPriority /* = 1 */)
{
	m_pThread->SendBroadcast(strBroadcastData, nPriority);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
CUDPRecvThread::CUDPRecvThread(SComMgr &comMgr, std::string strName)
{
	comMgr.CreateTaskLoop((IObjRef**)&m_pTaskLoop);
	SASSERT(m_pTaskLoop);
	m_pTaskLoop->start(strName.c_str(), ITaskLoop::Low);

	m_bRun = true;
}

CUDPRecvThread::~CUDPRecvThread()
{
	m_pTaskLoop->stop();
}

void CUDPRecvThread::_StartUDPRecv()
{
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, 0);

	SOCKADDR_IN addr;
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	addr.sin_family = AF_INET;
	addr.sin_port=htons(PORT_DUODUO);

	int nRet = bind(sock, (SOCKADDR*)&addr, sizeof(SOCKADDR));
	if(nRet == -1)
	{
		printf("Bind sock failed!\n");
		return;
	}

	fd_set fd;
	FD_ZERO(&fd);
	FD_SET(sock, &fd);

	char szDataBuffer[2048];
	int nRecvSize;

	while (m_bRun)
	{
		fd_set fdOld = fd;
		int nResult = select(sock + 1, &fdOld, NULL, NULL, NULL);
		for (int i = 0; i < fd.fd_count; i++)
		{
			if (fd.fd_array[i] == sock)
			{
				memset(szDataBuffer, 0, 2048);
				nRecvSize = recv(fd.fd_array[i], szDataBuffer, 2048, 0);
				if (nRecvSize > 0)
				{
					std::string strBody = szDataBuffer;
					int nTemp = 0;
				}
			}
		}
	}
}

///////////////////////////

CUDPRecver::CUDPRecver(void)
{
	m_pThread = new CUDPRecvThread(m_comMgr, "udp_recver");
}

CUDPRecver::~CUDPRecver(void)
{
	delete m_pThread;
}

bool CUDPRecver::cancelTask(long taskID)
{
	return m_pThread->cancelTask(taskID);
}

void CUDPRecver::StartUDPRecv(int nPriority /* = 1 */)
{
	m_pThread->StartUDPRecv(nPriority);
}