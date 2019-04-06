#ifndef __EVENTS_DEFINE_H__
#define __EVENTS_DEFINE_H__

#pragma once

enum {
	EVT_BINDPORT_FAILED = EVT_EXTERNAL_BEGIN + 1,
	EVT_FINDDEVICE,
	EVT_BROADCAST_RESPONSE,
	EVT_SENDTEXT,
	EVT_SENDIMAGE,
	EVT_SENDFILE,
	EVT_SENDAUDIO,
	EVT_SENDVIDEO,
};


SEVENT_BEGIN(EventBindPortFailed, EVT_BINDPORT_FAILED)
SEVENT_END()

SEVENT_BEGIN(EventFindDevice, EVT_FINDDEVICE)
std::string m_strName;
std::string m_strIP;
std::string m_strPort;
std::string m_strClientID;
SEVENT_END()

SEVENT_BEGIN(EventBroadcastRequest, EVT_BROADCAST_RESPONSE)
std::string m_strName;
std::string m_strIP;
std::string m_strPort;
std::string m_strClientID;
SEVENT_END()

SEVENT_BEGIN(EventSendText, EVT_SENDTEXT)
std::string m_strFrom;
std::string m_strTo;
std::string m_strType;
std::string m_strContent;
std::string m_strTimestamp;
std::string m_strMsgID;
SEVENT_END()

SEVENT_BEGIN(EventSendImage, EVT_SENDIMAGE)
std::string m_strFrom;
std::string m_strTo;
std::string m_strType;
std::string m_strContent;
std::string m_strTimestamp;
std::string m_strMsgID;
SEVENT_END()

SEVENT_BEGIN(EventSendFile, EVT_SENDFILE)
std::string m_strFrom;
std::string m_strTo;
std::string m_strType;
std::string m_strContent;
std::string m_strTimestamp;
std::string m_strMsgID;
SEVENT_END()

SEVENT_BEGIN(EventSendAudio, EVT_SENDAUDIO)
std::string m_strFrom;
std::string m_strTo;
std::string m_strType;
std::string m_strContent;
std::string m_strTimestamp;
std::string m_strMsgID;
SEVENT_END()

SEVENT_BEGIN(EventSendVideo, EVT_SENDVIDEO)
std::string m_strFrom;
std::string m_strTo;
std::string m_strType;
std::string m_strContent;
std::string m_strTimestamp;
std::string m_strMsgID;
SEVENT_END()
#endif