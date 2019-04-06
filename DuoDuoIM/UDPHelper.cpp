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
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255"); //�㲥��ַ

	//���ø��׽���Ϊ�㲥���ͣ�
	DWORD optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(DWORD)); //�����׽���ѡ��

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

		//֪ͨUI�̰߳󶨶˿�ʧ�ܣ�����quit
		EventBindPortFailed* pEvt = new EventBindPortFailed(NULL);
		SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
		pEvt->Release();

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
					rapidjson::Document document(&m_parseAllocator);
					if (document.Parse<0>(strBody.c_str()).HasParseError())
					{
						printf("����json��ʧ�ܣ� json����%s\n", strBody);
						//�ͷŽ�����
						m_parseAllocator.Clear();
						((rapidjson::MemoryPoolAllocator<>::ChunkHeader*)m_parseBuffer)->size = 0;
					}
					else
					{
						if (document.IsObject())	//����object
							processSvrData(document);
					}
				}
			}
		}
	}
}

void CUDPRecvThread::processSvrData(const rapidjson::Value& data)
{
	assert(data.HasMember("cmd"));
	std::string strCmd = data["cmd"].GetString();
	if ("find_device" == strCmd)//�����������豸���͵Ĳ����豸�Ĺ㲥��Ϣ
		ProcessFindDevice(data);
	else if ("broadcast_response" == strCmd)//�㲥��Ӧ
		ProcessBroadcastResponse(data);
	else if ("send_text" == strCmd)//���յ������豸���͵��ı���Ϣ
		ProcessSendText(data);
	else if ("send_image" == strCmd)//���յ������豸���͵�ͼƬ��Ϣ
		ProcessSendImage(data);
	else if ("send_file" == strCmd)//���յ������豸���͵��ļ���Ϣ
		ProcessSendFile(data);
	else if ("send_audio" == strCmd)//���յ������豸���͵Ķ�������Ϣ
		ProcessSendAudio(data);
	else if ("send_video" == strCmd)//���յ������豸���͵Ķ���Ƶ��Ϣ
		ProcessSendVideo(data);
}

void CUDPRecvThread::ProcessFindDevice(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessBroadcastResponse(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessSendText(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessSendImage(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessSendFile(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessSendAudio(const rapidjson::Value& data)
{
	//
}

void CUDPRecvThread::ProcessSendVideo(const rapidjson::Value& data)
{
	//
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