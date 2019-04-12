#ifndef __ADAPTER_LASTTALK_H__
#define __ADAPTER_LASTTALK_H__

#pragma once
#include <helper/SAdapterBase.h>
#include <vector>

#include "DataCenter.h"


struct ItemDate
{
	int nType;			//现阶段不使用该字段，为了便于拓展保留该字段
	std::string strID;
};

class CAdapter_Lasttalk : public SAdapterBase
{
public:
	struct IListener
	{
		virtual void LasttalkItemClick(int nType, const std::string& strID) = 0;
		virtual void LasttalkItemRClick(int nType, const std::string& strID) = 0;
		virtual void LasttalkItemDelete(int nType, const std::string& strID) = 0;
	};
public:
	CAdapter_Lasttalk(SListView* pOwner, IListener* pListener);
	~CAdapter_Lasttalk(void);

public:
	void AddItem(const int& nType, const std::string& strID);

	void MoveItemToTop(const std::string& strID);
	void EnsureVisable(const std::string& strID);
	void SetCurSel(const std::string& strID);
	int GetItemIndexByID(const std::string& strID);

	void UpdateData(){notifyDataSetChanged();}
protected:
	virtual void getView(int position, SWindow* pItem, pugi::xml_node xmlTemplate);
	virtual int getCount();
	virtual SStringT getColunName(int iCol) const;

	bool OnEventLvSelChangeing(EventLVSelChanging* pEvt);
	bool OnEventItemPanelClick(EventArgs* e);
	bool OnEventItemPanelRClick(EventArgs* e);

private:
	Times stamp_to_standard(int stampTime);
	SStringW OperateTimestamp(const std::string& strTimestamp);

private:
	std::vector<ItemDate*>				m_vecItems;
	SListView*							m_pOwner;

	IListener*							m_pListener;

	MemberFunctionSlot<CAdapter_Lasttalk, EventArgs>			m_evtItemClick;
	MemberFunctionSlot<CAdapter_Lasttalk, EventArgs>			m_evtItemRClick;
};

#endif