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

void CUDPSendThread::_SendBroadcast(const std::string& strName, const std::string& strClientID, int& nPort)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("find_device");

	writer.String("name");				//计算机名
	writer.String(strName.c_str());

	writer.String("ip");				//ip
	writer.String("");

	writer.String("port");			//port
	writer.Int(nPort);

	writer.String("client_id");			//当前客户端ID
	writer.String(strClientID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	//addr.sin_addr.S_un.S_addr = htonl(INADDR_BROADCAST);
	addr.sin_addr.S_un.S_addr = inet_addr("255.255.255.255");

	//设置该套接字为广播类型，
	DWORD optval = 1;
	setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&optval, sizeof(DWORD)); //设置套接字选项
	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr,sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendBroadcastRequest(const std::string& strRemoteIP, const std::string& strName, const std::string& strClientID, int& nPort)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("broadcast_response");

	writer.String("name");				//计算机名
	writer.String(strName.c_str());

	writer.String("ip");				//ip
	writer.String("");

	writer.String("client_id");			//当前客户端ID
	writer.String(strClientID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendText(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("send_text");

	writer.String("from");				
	writer.String(strFrom.c_str());

	writer.String("to");				
	writer.String(strTo.c_str());

	writer.String("type");				
	writer.String("text");

	writer.String("content");			
	writer.String(strContent.c_str());

	writer.String("time");			
	writer.String(strTimestamp.c_str());

	writer.String("msgid");			
	writer.String(strMsgID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendImage(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("send_text");

	writer.String("from");				
	writer.String(strFrom.c_str());

	writer.String("to");				
	writer.String(strTo.c_str());

	writer.String("type");				
	writer.String("image");

	writer.String("content");			
	writer.String(strContent.c_str());

	writer.String("time");			
	writer.String(strTimestamp.c_str());

	writer.String("msgid");			
	writer.String(strMsgID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendFile(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("send_text");

	writer.String("from");				
	writer.String(strFrom.c_str());

	writer.String("to");				
	writer.String(strTo.c_str());

	writer.String("type");				
	writer.String("file");

	writer.String("content");			
	writer.String(strContent.c_str());

	writer.String("time");			
	writer.String(strTimestamp.c_str());

	writer.String("msgid");			
	writer.String(strMsgID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendAudio(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("send_text");

	writer.String("from");				
	writer.String(strFrom.c_str());

	writer.String("to");				
	writer.String(strTo.c_str());

	writer.String("type");				
	writer.String("audio");

	writer.String("content");			
	writer.String(strContent.c_str());

	writer.String("time");			
	writer.String(strTimestamp.c_str());

	writer.String("msgid");			
	writer.String(strMsgID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
	closesocket(sock);
}

void CUDPSendThread::_SendVideo(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent)
{
	MPAStringBuffer s;
	rapidjson::Writer<MPAStringBuffer> writer(s);
	//通过writer构造json串
	writer.StartObject();
	writer.String("cmd");
	writer.String("send_text");

	writer.String("from");				
	writer.String(strFrom.c_str());

	writer.String("to");				
	writer.String(strTo.c_str());

	writer.String("type");				
	writer.String("video");

	writer.String("content");			
	writer.String(strContent.c_str());

	writer.String("time");			
	writer.String(strTimestamp.c_str());

	writer.String("msgid");			
	writer.String(strMsgID.c_str());
	writer.EndObject();
	std::string strPacket = s.GetString();

	GENPACKET packet = {0};
	packet.m_header.m_nProtocolVersion = 1;
	packet.m_header.m_nHeadLen = 12;
	packet.m_header.m_nBodyLen = strPacket.length();
	strcpy(packet.m_szData, strPacket.c_str());

	SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = inet_addr(strRemoteIP.c_str());

	sendto(sock, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, sizeof(sockaddr));
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

void CUDPSender::SendBroadcast(const std::string& strName, const std::string& strClientID, int& nPort, int nPriority /* = 1 */)
{
	m_pThread->SendBroadcast(strName, strClientID, nPort, nPriority);
}

void CUDPSender::SendBroadcastRequest(const std::string& strRemoteIP, const std::string& strName, const std::string& strClientID, int& nPort, int nPriority /* = 1 */)
{
	m_pThread->SendBroadcastRequest(strRemoteIP, strName, strClientID, nPort, nPriority);
}

void CUDPSender::SendText(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority /* = 1 */)
{
	m_pThread->SendText(strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, nPriority);
}

void CUDPSender::SendImage(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority /* = 1 */)
{
	m_pThread->SendImage(strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, nPriority);
}

void CUDPSender::SendFile(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority /* = 1 */)
{
	m_pThread->SendFile(strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, nPriority);
}

void CUDPSender::SendAudio(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority /* = 1 */)
{
	m_pThread->SendAudio(strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, nPriority);
}

void CUDPSender::SendVideo(const std::string& strRemoteIP, const std::string& strFrom, const std::string& strTo, const std::string& strTimestamp, const std::string& strMsgID, const std::string& strContent, int nPriority /* = 1 */)
{
	m_pThread->SendVideo(strRemoteIP, strFrom, strTo, strTimestamp, strMsgID, strContent, nPriority);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////
CUDPRecvThread::CUDPRecvThread(SComMgr &comMgr, std::string strName)
{
	comMgr.CreateTaskLoop((IObjRef**)&m_pTaskLoop);
	SASSERT(m_pTaskLoop);
	m_pTaskLoop->start(strName.c_str(), ITaskLoop::Low);

	m_bRun = true;

	//InitServer();
}

CUDPRecvThread::~CUDPRecvThread()
{
	m_pTaskLoop->stop();
}

void CUDPRecvThread::_StartUDPRecv()
{
	if (InitServer())
	{
		while (m_bRun)
		{
			GENPACKET packet = {0};
			sockaddr_in addr = {0};
			int nLen = sizeof(addr);
			recvfrom(m_SvrSocket, (char*)&packet, sizeof(packet), 0, (sockaddr*)&addr, &nLen);

			//解析发送方的ip、port
			std::string strIP = inet_ntoa(addr.sin_addr);
			int nPort = htons(addr.sin_port);

			std::string strBody = packet.m_szData;
			if (!strBody.empty())
			{
				rapidjson::Document document(&m_parseAllocator);
				if (document.Parse<0>(strBody.c_str()).HasParseError())
				{
					printf("解析json串失败！ json串：%s\n", strBody);
					//释放解析器
					m_parseAllocator.Clear();
					((rapidjson::MemoryPoolAllocator<>::ChunkHeader*)m_parseBuffer)->size = 0;
					continue;
				}
				else{
					processSvrData(document, strIP, nPort);
				}
			}
		}
	}
}

bool CUDPRecvThread::InitServer()
{
	m_SvrSocket = socket(AF_INET, SOCK_DGRAM, 0);
	sockaddr_in addr = {0};
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT_DUODUO);
	addr.sin_addr.S_un.S_addr = htonl(INADDR_ANY);
	
	int nRet = bind(m_SvrSocket, (sockaddr*)&addr, sizeof(addr));
	if(nRet == -1)
	{
		printf("Bind sock failed!\n");

		//通知UI线程绑定端口失败，程序quit
		EventBindPortFailed* pEvt = new EventBindPortFailed(NULL);
		SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
		pEvt->Release();

		return false;
	}
	return true;
}

void CUDPRecvThread::processSvrData(const rapidjson::Value& data, std::string strIP, int nPort)
{
	assert(data.HasMember("cmd"));
	std::string strCmd = data["cmd"].GetString();
	if ("find_device" == strCmd)//网段内其他设备发送的查找设备的广播消息
		ProcessFindDevice(data, strIP, nPort);
	else if ("broadcast_response" == strCmd)//广播响应
		ProcessBroadcastResponse(data, strIP, nPort);
	else if ("send_text" == strCmd)//接收到其他设备发送的文本消息
		ProcessSendText(data);
	else if ("send_image" == strCmd)//接收到其他设备发送的图片消息
		ProcessSendImage(data);
	else if ("send_file" == strCmd)//接收到其他设备发送的文件消息
		ProcessSendFile(data);
	else if ("send_audio" == strCmd)//接收到其他设备发送的短语音消息
		ProcessSendAudio(data);
	else if ("send_video" == strCmd)//接收到其他设备发送的短视频消息
		ProcessSendVideo(data);
}

void CUDPRecvThread::ProcessFindDevice(const rapidjson::Value& data, std::string strIP, int nPort)
{
	assert(data.IsObject());
	assert(data.HasMember("name"));
	assert(data.HasMember("client_id"));

	std::string strName = data["name"].GetString();
	std::string strClientID = data["client_id"].GetString();

	EventFindDevice* pEvt = new EventFindDevice(NULL);
	pEvt->m_strIP = strIP;
	pEvt->m_strName = strName;
	pEvt->m_strClientID = strClientID;
	pEvt->m_nPort = nPort;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessBroadcastResponse(const rapidjson::Value& data,  std::string strIP, int nPort)
{
	assert(data.IsObject());
	assert(data.HasMember("name"));
	assert(data.HasMember("client_id"));

	std::string strName = data["name"].GetString();
	std::string strClientID = data["client_id"].GetString();

	EventBroadcastRequest* pEvt = new EventBroadcastRequest(NULL);
	pEvt->m_nPort = nPort;
	pEvt->m_strName = strName;
	pEvt->m_strClientID = strClientID;
	pEvt->m_strIP = strIP;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessSendText(const rapidjson::Value& data)
{
	assert(data.IsObject());
	assert(data.HasMember("from"));
	assert(data.HasMember("to"));
	assert(data.HasMember("type"));
	assert(data.HasMember("content"));
	assert(data.HasMember("time"));
	assert(data.HasMember("msgid"));

	std::string strFrom = data["from"].GetString();
	std::string strTo = data["to"].GetString();
	std::string strType = data["type"].GetString();
	std::string strContent = data["content"].GetString();
	std::string strTime = data["time"].GetString();
	std::string strMsgID = data["msgid"].GetString();

	//fire event
	EventSendText* pEvt = new EventSendText(NULL);
	pEvt->m_strFrom = strFrom;
	pEvt->m_strTo = strTo;
	pEvt->m_strType = strType;
	pEvt->m_strContent = strContent;
	pEvt->m_strTimestamp = strTime;
	pEvt->m_strMsgID = strMsgID;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessSendImage(const rapidjson::Value& data)
{
	//接收到图片消息
	assert(data.IsObject());
	assert(data.HasMember("from"));
	assert(data.HasMember("to"));
	assert(data.HasMember("type"));
	assert(data.HasMember("content"));
	assert(data.HasMember("time"));
	assert(data.HasMember("msgid"));

	std::string strFrom = data["from"].GetString();
	std::string strTo = data["to"].GetString();
	std::string strType = data["type"].GetString();
	std::string strContent = data["content"].GetString();
	std::string strTime = data["time"].GetString();
	std::string strMsgID = data["msgid"].GetString();

	//fire event
	EventSendImage* pEvt = new EventSendImage(NULL);
	pEvt->m_strFrom = strFrom;
	pEvt->m_strTo = strTo;
	pEvt->m_strType = strType;
	pEvt->m_strContent = strContent;
	pEvt->m_strTimestamp = strTime;
	pEvt->m_strMsgID = strMsgID;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessSendFile(const rapidjson::Value& data)
{
	//接收到文件消息
	assert(data.IsObject());
	assert(data.HasMember("from"));
	assert(data.HasMember("to"));
	assert(data.HasMember("type"));
	assert(data.HasMember("content"));
	assert(data.HasMember("time"));
	assert(data.HasMember("msgid"));

	std::string strFrom = data["from"].GetString();
	std::string strTo = data["to"].GetString();
	std::string strType = data["type"].GetString();
	std::string strContent = data["content"].GetString();
	std::string strTime = data["time"].GetString();
	std::string strMsgID = data["msgid"].GetString();

	//fire event
	EventSendFile* pEvt = new EventSendFile(NULL);
	pEvt->m_strFrom = strFrom;
	pEvt->m_strTo = strTo;
	pEvt->m_strType = strType;
	pEvt->m_strContent = strContent;
	pEvt->m_strTimestamp = strTime;
	pEvt->m_strMsgID = strMsgID;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessSendAudio(const rapidjson::Value& data)
{
	//接收到短语音消息
	assert(data.IsObject());
	assert(data.HasMember("from"));
	assert(data.HasMember("to"));
	assert(data.HasMember("type"));
	assert(data.HasMember("content"));
	assert(data.HasMember("time"));
	assert(data.HasMember("msgid"));

	std::string strFrom = data["from"].GetString();
	std::string strTo = data["to"].GetString();
	std::string strType = data["type"].GetString();
	std::string strContent = data["content"].GetString();
	std::string strTime = data["time"].GetString();
	std::string strMsgID = data["msgid"].GetString();

	//fire event
	EventSendAudio* pEvt = new EventSendAudio(NULL);
	pEvt->m_strFrom = strFrom;
	pEvt->m_strTo = strTo;
	pEvt->m_strType = strType;
	pEvt->m_strContent = strContent;
	pEvt->m_strTimestamp = strTime;
	pEvt->m_strMsgID = strMsgID;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
}

void CUDPRecvThread::ProcessSendVideo(const rapidjson::Value& data)
{
	//接收到短视频消息
	assert(data.IsObject());
	assert(data.HasMember("from"));
	assert(data.HasMember("to"));
	assert(data.HasMember("type"));
	assert(data.HasMember("content"));
	assert(data.HasMember("time"));
	assert(data.HasMember("msgid"));

	std::string strFrom = data["from"].GetString();
	std::string strTo = data["to"].GetString();
	std::string strType = data["type"].GetString();
	std::string strContent = data["content"].GetString();
	std::string strTime = data["time"].GetString();
	std::string strMsgID = data["msgid"].GetString();

	//fire event
	EventSendVideo* pEvt = new EventSendVideo(NULL);
	pEvt->m_strFrom = strFrom;
	pEvt->m_strTo = strTo;
	pEvt->m_strType = strType;
	pEvt->m_strContent = strContent;
	pEvt->m_strTimestamp = strTime;
	pEvt->m_strMsgID = strMsgID;
	SNotifyCenter::getSingletonPtr()->FireEventAsync(pEvt);
	pEvt->Release();
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