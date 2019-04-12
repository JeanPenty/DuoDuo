#ifndef __PUBLIC_H__
#define __PUBLIC_H__

#pragma once

#include <map>
#include <string>
using namespace std;

typedef struct times
{
	int Year;
	int Mon;
	int Day;
	int Hour;
	int Min;
	int Second;
}Times;

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

typedef struct _tagMessageInfo
{
	std::string m_strFrom;
	std::string m_strTo;
	std::string m_strType;
	std::string m_strContent;
	std::string m_strTime;
	std::string m_strID;
}MESSAGE_INFO;
typedef std::map<std::string, MESSAGE_INFO>	LasttalkMap;

#endif