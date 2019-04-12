#pragma once

#include <helper/SAdapterBase.h>
#include "DataCenter.h"

struct ItemContactData
{
	ItemContactData():bGroup(false){}
	std::string strID;
	int nType;			//用户的组ID
	SStringT strImg ;	//用户图像
	SStringT strName;	//用户名
	bool bGroup;
};
class CAdapter_Contact :public STreeAdapterBase<ItemContactData>
{
public:
	struct IListener
	{
		virtual void ContactItemClick(int nType, const std::string& strID) = 0;
		virtual void ContactItemDBClick(int nType, const std::string& strID) = 0;
		virtual void ContactItemRClick(int nType, const std::string& strID) = 0;
	};
public:
	bool IsItemExist(const std::string& strID)
	{
		HSTREEITEM hParent = GetFirstVisibleItem();
		while (ITEM_NULL != hParent)
		{
			if (HasChildren(hParent))		//有子节点则遍历子节点
			{
				HSTREEITEM hFirstChild = GetFirstChildItem(hParent);
				while (ITEM_NULL != hFirstChild)
				{
					ItemInfo& info = m_tree.GetItemRef(hFirstChild);
					if (info.data.strID == strID)
						return true;

					hFirstChild = GetNextSiblingItem(hFirstChild);
				}
			}
			hParent = GetNextSiblingItem(hParent);
		}
		return false;
	}
	void AddContact(int nType, const std::string& strID)
	{
		if (IsItemExist(strID))
			return;

		HSTREEITEM hParent = GetFirstVisibleItem();
		while (ITEM_NULL != hParent)
		{
			ItemInfo& info = m_tree.GetItemRef(hParent);
			if (info.data.nType == nType && info.data.bGroup == true)
			{
				ClientInfoMap::iterator iter = CDataCenter::getSingleton().m_mapClients.find(strID);
				if (iter != CDataCenter::getSingleton().m_mapClients.end())
				{
					std::string strName = iter->second.m_strName;
					SStringW sstrName = S_CA2W(strName.c_str());
					ItemContactData data;
					data.nType = 2;		
					data.bGroup = false;			
					data.strID = strID;
					data.strName = sstrName;
					data.strImg = L"skin_male32";
					InsertItem(data, hParent);
				}
			}
			hParent = GetNextSiblingItem(hParent);
		}

		notifyBranchChanged(ITvAdapter::ITEM_ROOT);
	}
public:	
	CAdapter_Contact(IListener* pListener) 
	{
		m_pListener = pListener;

		/*
		//暂时先注释掉群相关的
		ItemContactData dataGroup;
		dataGroup.strName = L"群";		
		dataGroup.nType = 1;
		dataGroup.bGroup = true;

		HSTREEITEM hRootGroup = InsertItem(dataGroup);
		SetItemExpanded(hRootGroup, TRUE);
		*/

		ItemContactData dataPersonal;
		dataPersonal.strName = L"个人好友";		
		dataPersonal.nType = 2;
		dataPersonal.bGroup = true;

		HSTREEITEM hRootPersonal = InsertItem(dataPersonal);
		SetItemExpanded(hRootPersonal, TRUE);
	}

	~CAdapter_Contact() {}

	virtual void getView(SOUI::HTREEITEM loc, SWindow * pItem, pugi::xml_node xmlTemplate)
	{
		ItemInfo & ii = m_tree.GetItemRef((HSTREEITEM)loc);
		int itemType = getViewType(loc);
		if (pItem->GetChildrenCount() == 0)
		{
			switch (itemType)
			{
			case 0:xmlTemplate = xmlTemplate.child(L"item_group");
				break;
			case 1:xmlTemplate = xmlTemplate.child(L"item_data");
				break;
			}
			pItem->InitFromXml(xmlTemplate);
			if(itemType==0)
			{//不让它点	
				pItem->GetEventSet()->setMutedState(true);			
			}
		}
		if(itemType == 1)
		{
			pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_CLICK, Subscriber(&CAdapter_Contact::OnItemPanelClick, this));	
			pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_DBCLICK, Subscriber(&CAdapter_Contact::OnItemPanelDBClick, this));	
			pItem->GetEventSet()->subscribeEvent(EVT_ITEMPANEL_RCLICK, Subscriber(&CAdapter_Contact::OnItemPanelRClick, this));	
			pItem->FindChildByName2<SImageWnd>(L"face")->SetAttribute(L"skin", ii.data.strImg, FALSE);
		}
		else 
		{
			//暂时不展示hr
			//pItem->FindChildByName(L"hr")->SetVisible(ii.data.nType != 1);	
		}
		pItem->FindChildByName(L"name")->SetWindowText(ii.data.strName);
	}

	bool OnItemPanelClick(EventArgs *e)
	{
		EventItemPanelClick* pEvt = sobj_cast<EventItemPanelClick>(e);
		if (NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if (NULL == pItem) return true;

		int hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if (!ii.data.bGroup)
		{
			m_pListener->ContactItemClick(ii.data.nType, ii.data.strID);
		}

		return true;
	}	

	bool OnItemPanelDBClick(EventArgs* e)
	{
		EventItemPanelDbclick* pEvt = sobj_cast<EventItemPanelDbclick>(e);
		if (NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if (NULL == pItem) return true;

		int hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if (!ii.data.bGroup)
		{
			m_pListener->ContactItemDBClick(ii.data.nType, ii.data.strID);
		}

		return true;
	}

	bool OnItemPanelRClick(EventArgs *e)
	{
		EventItemPanelRclick* pEvt = sobj_cast<EventItemPanelRclick>(e);
		if (NULL == pEvt) return true;

		SItemPanel* pItem = sobj_cast<SItemPanel>(pEvt->sender);
		if (NULL == pItem) return true;

		int hItem = static_cast<SOUI::HTREEITEM>(pItem->GetItemIndex());
		ItemInfo& ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if (!ii.data.bGroup)
		{
			m_pListener->ContactItemRClick(ii.data.nType, ii.data.strID);
		}

		return true;
	}

	virtual int getViewType(SOUI::HTREEITEM hItem) const
	{
		ItemInfo & ii = m_tree.GetItemRef((HSTREEITEM)hItem);
		if (ii.data.bGroup) return 0;
		else return 1;
	}

	virtual int getViewTypeCount() const
	{
		return 2;
	}

private:
	IListener*		m_pListener;
};