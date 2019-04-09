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
	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	//addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

	//���ø��׽���Ϊ�㲥���ͣ�
	DWORD optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(DWORD)); //�����׽���ѡ��

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strBroadcastData.length();
	strcpy(packet.m_szData, strBroadcastData.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (SOCKADDR*)&addr,sizeof(SOCKADDR));

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

	InitServer();
}

CUDPRecvThread::~CUDPRecvThread()
{
	m_pTaskLoop->stop();
}

void CUDPRecvThread::_StartUDPRecv()
{
	while (m_bRun)
	{
		GENPACKET packet = {0};
		SOCKADDR_IN addr = {0};
		int nLen= sizeof(addr);
		recvfrom(m_SvrSocket, (char*)&packet, sizeof(packet), 0, (SOCKADDR*)&addr, &nLen);
		std::string strIP = inet_ntoa(addr.sin_addr);

		std::string strBody = packet.m_szData;
		rapidjson::Document document(&m_parseAllocator);
		if (document.Parse<0>(strBody.c_str()).HasParseError())
		{
			printf("����json��ʧ�ܣ� json����%s\n", strBody);
			//�ͷŽ�����
			m_parseAllocator.Clear();
			((rapidjson::MemoryPoolAllocator<>::ChunkHeader*)m_parseBuffer)->size = 0;
			continue;;
		}
		else
		{
			processSvrData(document, strIP);
		}
	}
}

bool CUDPRecvThread::InitServer()
{
	m_SvrSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	SOCKADDR_IN addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	int nRet = bind(m_SvrSocket, (SOCKADDR*)&addr, sizeof(addr));
	if(nRet == -1)
	{
		printf("Bind sock failed!\n");

		//֪ͨUI�̰߳󶨶˿�ʧ�ܣ�����quit
		EventBindPortFailed* pEvt = new EventBindPortFailed(NULL);
		SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
		pEvt->Release();

		return false;
	}
	return true;
}

void CUDPRecvThread::processSvrData(const rapidjson::Value& data, std::string strIP/* = ""*/)
{
	assert(data.HasMember("cmd"));
	std::string strCmd = data["cmd"].GetString();
	if ("find_device" == strCmd)//�����������豸���͵Ĳ����豸�Ĺ㲥��Ϣ
		ProcessFindDevice(data, strIP);
	else if ("broadcast_response" == strCmd)//�㲥��Ӧ
		ProcessBroadcastResponse(data, strIP);
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

void CUDPRecvThread::ProcessFindDevice(const rapidjson::Value& data, std::string strIP/* = ""*/)
{
	assert(data.IsObject());
	assert(data.HasMember("name"));
	assert(data.HasMember("port"));
	assert(data.HasMember("client_id"));

	std::string strName = data["name"].GetString();
	std::string strClientID = data["client_id"].GetString();
	int nPort = data["port"].GetInt();

	EventFindDevice* pEvt = new EventFindDevice(NULL);
	pEvt->m_strIP = strIP;
	pEvt->m_strName = strName;
	pEvt->m_strClientID = strClientID;
	pEvt->m_nPort = nPort;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessBroadcastResponse(const rapidjson::Value& data,  std::string strIP/* = ""*/)
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