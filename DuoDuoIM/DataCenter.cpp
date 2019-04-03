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
}

CDataCenter::~CDataCenter(void)
{
}
