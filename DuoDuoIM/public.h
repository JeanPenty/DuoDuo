#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#pragma once

#include <map>
#include <string>
using namespace std;

typedef struct _tagClientInfo
{
	std::string m_strName;
	std::string m_strIP;
	std::string m_strClientID;
	int m_nPort;

	_tagClientInfo(){
		m_strName = "";
		m_strIP = "";
		m_strClientID = "";
		m_nPort = -1;
	}

	_tagClientInfo(const std::string& strName, const std::string& strIP, 
		const std::string& strClientID, int nPort){
			m_strName = strName;
			m_strIP = strIP;
			m_strClientID = strClientID;
			m_nPort = nPort;
	}
}CLIENT_INFO;
typedef std::map<std::string, CLIENT_INFO>	ClientInfoMap;

#endif