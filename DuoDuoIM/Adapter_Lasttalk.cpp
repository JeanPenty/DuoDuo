#include "StdAfx.h"
#include "Adapter_Lasttalk.h"

CAdapter_Lasttalk::CAdapter_Lasttalk(SListView* pOwner, IListener* pListener)
: m_pOwner(pOwner)
, m_pListener(pListener)
, m_evtItemClick(&CAdapter_Lasttalk::OnEventItemPanelClick, this)
, m_evtItemRClick(&CAdapter_Lasttalk::OnEventItemPanelRClick, this)
{
	SASSERT(m_pOwner);
	m_pOwner->GetEventSet()->subscribeEvent(&CAdapter_Lasttalk::OnEventLvSelChangeing, this);
}

CAdapter_Lasttalk::~CAdapter_Lasttalk(void)
{
}

void CAdapter_Lasttalk::getView(int position, SWindow* pItem, pugi::xml_node xmlTemplate)
{
	if (0 == pItem->GetChildrenCount())
	{
		pItem->InitFromXml(xmlTemplate);
		pItem->GetEventSet()->subscribeEvent(EventItemPanelClick::EventID, m_evtItemClick);
		pItem->GetEventSet()->subscribeEvent(EventItemPanelRclick::EventID, m_evtItemRClick);
	}

	size_t sPos = static_cast<size_t>(position);
	if (sPos >= m_vecItems.size())
		return;

	ItemDate* pData = m_vecItems[sPos];
	if (NULL == pData)
		return;

	//设置可见数据(可判断是否设置了自定义头像，如果设置了就用自定义头像、反之使用默认头像)
	//face
	SImageWnd* pItemFace = pItem->FindChildByName2<SImageWnd>(L"item_face");
	SASSERT(pItemFace);
	SStringW sstrFace;
	pItemFace->SetAttribute(L"skin", L"skin_male32", TRUE);

	//name
	SStatic* pItemName = pItem->FindChildByName2<SStatic>(L"item_name");
	SASSERT(pItemName);
	SStringW sstrName;
	ClientInfoMap::iterator iterClient = CDataCenter::getSingleton().m_mapClients.find(pData->strID);
	if (iterClient != CDataCenter::getSingleton().m_mapClients.end())
	{
		std::string strName = iterClient->second.m_strName;
		sstrName = S_CA2W(strName.c_str());
	}
	else
		sstrName = S_CA2W(pData->strID.c_str());
	pItemName->SetWindowText(sstrName);

	//消息内容
	SStatic* pItemContent = pItem->FindChildByName2<SStatic>(L"item_content");
	SASSERT(pItemContent);
	SStringW sstrContent;
	LasttalkMap::iterator iterMessage = CDataCenter::getSingleton().m_mapLasttalks.find(pData->strID);
	if (iterMessage != CDataCenter::getSingleton().m_mapLasttalks.end())
	{
		if ("text" == iterMessage->second.m_strType)
		{
			std::string strContent = iterMessage->second.m_strContent;
			sstrContent = S_CA2W(strContent.c_str());
		}
		else if ("image" == iterMessage->second.m_strType)
			sstrContent = L"图片";
		else if ("file" == iterMessage->second.m_strType)
			sstrContent = L"文件";
		else if ("audio" == iterMessage->second.m_strType)
			sstrContent = L"语音";
		else if ("video" == iterMessage->second.m_strType)
			sstrContent = L"视频";
		else if ("location" == iterMessage->second.m_strType)
			sstrContent = L"位置";
		else
			sstrContent = L"未知";
	}
	else
		sstrContent = L"";
	pItemContent->SetWindowText(sstrContent);

	//消息时间设置
	SStatic* pItemTime = pItem->FindChildByName2<SStatic>(L"item_time");
	SASSERT(pItemTime);
	SStringW sstrTime;
	if (iterMessage != CDataCenter::getSingleton().m_mapLasttalks.end())
	{
		std::string strTime = iterMessage->second.m_strTime;
		std::wstring wstrTime = OperateTimestamp(strTime);
		sstrTime = wstrTime.c_str();
	}
	else
		sstrTime = L"";
	pItemTime->SetWindowText(sstrTime);
}

int CAdapter_Lasttalk::getCount()
{
	return static_cast<int>(m_vecItems.size());
}

SStringT CAdapter_Lasttalk::getColunName(int iCol) const
{
	return L"col_nick";
}

void CAdapter_Lasttalk::AddItem(const int& nType, const std::string& strID)
{
	ItemDate* pItemData = new ItemDate;
	pItemData->nType = nType;
	pItemData->strID = strID;

	m_vecItems.push_back(pItemData);
	notifyDataSetChanged();
}

void CAdapter_Lasttalk::MoveItemToTop(const std::string& strID)
{
	int nIndex = GetItemIndexByID(strID);
	if (-1 != nIndex)
	{
		size_t sIndex = static_cast<size_t>(nIndex);
		if(sIndex < 0 || sIndex >= m_vecItems.size())
			return ;
		ItemDate* pItemData = m_vecItems[nIndex];
		if (pItemData)
		{
			m_vecItems.erase(m_vecItems.begin() + sIndex);
			m_vecItems.insert(m_vecItems.begin(), pItemData);
		}
	}
}

void CAdapter_Lasttalk::EnsureVisable(const std::string& strID)
{
	int nIndex = GetItemIndexByID(strID);
	if (-1 != nIndex)
		m_pOwner->EnsureVisible(nIndex);
}

void CAdapter_Lasttalk::SetCurSel(const std::string& strID)
{
	int nIndex = GetItemIndexByID(strID);
	if (-1 != nIndex)
		m_pOwner->SetSel(nIndex, TRUE);
}

int CAdapter_Lasttalk::GetItemIndexByID(const std::string& strID)
{
	int nIndex = -1;
	for (int i = 0; i < m_vecItems.size(); i++)
	{
		if (m_vecItems[i]->strID == strID)
		{
			nIndex = i;
			break;
		}
	}
	return nIndex;
}

bool CAdapter_Lasttalk::OnEventItemPanelClick(EventArgs* e)
{
	EventItemPanelClick* pEvtItemClick = sobj_cast<EventItemPanelClick>(e);
	if (NULL == pEvtItemClick)
		return true;

	SItemPanel* pItem = sobj_cast<SItemPanel>(pEvtItemClick->sender);

	int nItem = static_cast<int>(pItem->GetItemIndex());
	ItemDate* pInfo = m_vecItems[nItem];
	if (NULL != pInfo)
	{
		m_pListener->LasttalkItemClick(pInfo->nType, pInfo->strID);
	}

	return true;
}

bool CAdapter_Lasttalk::OnEventItemPanelRClick(EventArgs* e)
{
	EventItemPanelRclick* pEvtItemRClick = sobj_cast<EventItemPanelRclick>(e);
	if(NULL == pEvtItemRClick) return true;

	SItemPanel* pItem = sobj_cast<SItemPanel>(pEvtItemRClick->sender);
	if(NULL == pItem) return true;

	int nItem = static_cast<int>(pItem->GetItemIndex());
	ItemDate* pInfo = m_vecItems[nItem];
	if (NULL != pInfo)
	{
		m_pListener->LasttalkItemRClick(pInfo->nType, pInfo->strID);
	}

	return true;
}

bool CAdapter_Lasttalk::OnEventLvSelChangeing(EventLVSelChanging* pEvt)
{
	if(NULL == pEvt)
		return true;

	pEvt->bubbleUp = false;
	if(-1 == pEvt->iNewSel)				// 不能设置 -1 
		pEvt->bCancel = TRUE;

	return true;
}

SStringW CAdapter_Lasttalk::OperateTimestamp(const std::string& strTimestamp)
{
	std::ostringstream os;
	time_t ttCurrent = time(NULL);
	Times t = stamp_to_standard(atoi(strTimestamp.c_str()));

	//获取当天0点的时间戳
	time_t ttMorning = time(NULL);
	struct tm* tmMorning = localtime(&ttMorning);
	tmMorning->tm_hour = 0;  
	tmMorning->tm_min = 0;  
	tmMorning->tm_sec = 0;

	unsigned int MorningTimestamp = mktime(tmMorning);
	unsigned int SundayTimestamp = MorningTimestamp - tmMorning->tm_wday * (24*60*60);//获取上周日0点的时间戳

	int nTimestamp = atoi(strTimestamp.c_str());		//消息时间戳
	if (nTimestamp >= MorningTimestamp)		//今天消息
	{
		os.str("");
		if (t.Hour > 12){
			if (t.Min >= 10)
				os<<"下午 "<<t.Hour<<":"<<t.Min;
			else
				os<<"下午 "<<t.Hour<<":0"<<t.Min;
		}
		else{
			if (t.Min >= 10)
				os<<"上午 "<<t.Hour<<":"<<t.Min;
			else
				os<<"上午 "<<t.Hour<<":0"<<t.Min;
		}

		std::string strTime = os.str();		
		SStringW sstrTime = S_CA2W(strTime.c_str());
		return sstrTime;
	}
	else if (nTimestamp < MorningTimestamp && nTimestamp >= MorningTimestamp - 86400){//昨天
		return L"昨天";
	}
	else{	//非今天跟昨天
		SStringW sstrResult = L"";
		if (nTimestamp < SundayTimestamp)//消息时间小于上周星期天0点
			sstrResult.Format(L"%d/%d/%d", t.Year, t.Mon, t.Day);		
		else
		{
			int elapsed_time = (int)difftime(nTimestamp, SundayTimestamp);//上周日0点到今天0点相差时间戳
			int elapsed_day = elapsed_time/(24*60*60);	//相差天数
			switch (elapsed_day)
			{
			case 0:
				sstrResult = L"星期日";
				break;
			case 1:
				sstrResult = L"星期一";
				break;
			case 2:
				sstrResult = L"星期二";
				break;
			case 3:
				sstrResult = L"星期三";
				break;
			case 4:
				sstrResult = L"星期四";
				break;
			case 5:
				sstrResult = L"星期五";
				break;
			case 6:
				sstrResult = L"星期六";
				break;
			default:
				sstrResult.Format(L"%d/%d/%d", t.Year, t.Mon, t.Day);
				break;
			}
		}
		return sstrResult;
	}
	return L"";
}

Times CAdapter_Lasttalk::stamp_to_standard(int stampTime)
{
	time_t tick = (time_t)stampTime;
	struct tm tm; 
	char s[100];
	Times standard;
	tm = *localtime(&tick);
	strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &tm); 

	standard.Year = atoi(s);
	standard.Mon = atoi(s+5);
	standard.Day = atoi(s+8);
	standard.Hour = atoi(s+11);
	standard.Min = atoi(s+14);
	standard.Second = atoi(s+17);

	return standard;
}