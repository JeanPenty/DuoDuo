// MainDlg.cpp : implementation of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MainDlg.h"	
	
CMainDlg::CMainDlg() : SHostWnd(_T("LAYOUT:XML_MAINWND"))
{
	m_bLayoutInited = FALSE;

	m_pAdapterLasttalk = NULL;
	m_pAdapterContact = NULL;

	//启动UDP接收
	CUDPRecver::getSingleton().StartUDPRecv();

	//发送广播消息，当前设备出场了
	CUDPSender::getSingleton().SendBroadcast(CDataCenter::getSingleton().m_LocalInfo.m_strName.c_str(),
		CDataCenter::getSingleton().m_LocalInfo.m_strClientID.c_str(), CDataCenter::getSingleton().m_LocalInfo.m_nPort);
}

CMainDlg::~CMainDlg()
{
}

int CMainDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	SetMsgHandled(FALSE);
	return 0;
}

BOOL CMainDlg::OnInitDialog(HWND hWnd, LPARAM lParam)
{
	m_bLayoutInited = TRUE;
// 	SShellNotifyIcon *notify = FindChildByID2<SShellNotifyIcon>(110);
// 	notify->ShowNotify(L"Hello SOUI",L"这可能是一个提示");


	//设置当前窗口可接收拖拽文件
	::DragAcceptFiles(m_hWnd, TRUE);
	::RegisterDragDrop(m_hWnd, GetDropTarget());

	//设置消息按钮被选中
	SImageButton* pBtnMessage = FindChildByName2<SImageButton>(L"btn_message");
	SImageButton* pBtnContact = FindChildByName2<SImageButton>(L"btn_contact");
	SASSERT(pBtnMessage);
	SASSERT(pBtnContact);
	pBtnMessage->SetCheck(TRUE);
	pBtnContact->SetCheck(FALSE);

	//最近会话相关
	SListView* plvLasttalk = FindChildByName2<SListView>(L"lv_lasttalk");
	SASSERT(plvLasttalk);
	plvLasttalk->EnableScrollBar(SSB_HORZ, FALSE);
	//设置Adapter
	m_pAdapterLasttalk = new CAdapter_Lasttalk(plvLasttalk, this);
	plvLasttalk->SetAdapter(m_pAdapterLasttalk);
	m_pAdapterLasttalk->Release();

	//搜索结果相关
	SListView* plvSearchResult = FindChildByName2<SListView>(L"lv_search");
	SASSERT(plvSearchResult);
	plvSearchResult->EnableScrollBar(SSB_HORZ, FALSE);
	//设置Adapter(待实现)

	//联系人列表相关
	STreeView* ptvContact = FindChildByName2<STreeView>(L"tv_contact");
	SASSERT(ptvContact);
	ptvContact->EnableScrollBar(SSB_HORZ, FALSE);
	//设置Adapter
	m_pAdapterContact = new CAdapter_Contact(this);
	ptvContact->SetAdapter(m_pAdapterContact);
	m_pAdapterContact->Release();


	InitLasttalkList();
	return 0;
}
//TODO:消息映射
void CMainDlg::OnClose()
{
	CSimpleWnd::DestroyWindow();
}

void CMainDlg::OnMaximize()
{
	SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
}
void CMainDlg::OnRestore()
{
	SendMessage(WM_SYSCOMMAND, SC_RESTORE);
}
void CMainDlg::OnMinimize()
{
	SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CMainDlg::OnSize(UINT nType, CSize size)
{
	SetMsgHandled(FALSE);
	if (!m_bLayoutInited) return;
	
	SWindow *pBtnMax = FindChildByName(L"btn_max");
	SWindow *pBtnRestore = FindChildByName(L"btn_restore");
	if(!pBtnMax || !pBtnRestore) return;
	
	if (nType == SIZE_MAXIMIZED)
	{
		pBtnRestore->SetVisible(TRUE);
		pBtnMax->SetVisible(FALSE);
	}
	else if (nType == SIZE_RESTORED)
	{
		pBtnRestore->SetVisible(FALSE);
		pBtnMax->SetVisible(TRUE);
	}
}


//演示如何响应菜单事件
void CMainDlg::OnCommand(UINT uNotifyCode, int nID, HWND wndCtl)
{
	if (uNotifyCode == 0)
	{
		switch (nID)
		{
		case 6:
			PostMessage(WM_CLOSE);
			break;
		default:
			break;
		}
	}
}

void CMainDlg::OnBnClickMessage()
{
	SImageButton* pBtnMessage = FindChildByName2<SImageButton>(L"btn_message");
	SImageButton* pBtnContact = FindChildByName2<SImageButton>(L"btn_contact");
	SASSERT(pBtnMessage);
	SASSERT(pBtnContact);

	pBtnMessage->SetCheck(TRUE);
	pBtnContact->SetCheck(FALSE);

	STabCtrl* pLeftListTab = FindChildByName2<STabCtrl>(L"left_tab");
	SASSERT(pLeftListTab);
	if (CDataCenter::getSingleton().m_mapLasttalks.empty())
		pLeftListTab->SetCurSel(L"lasttalk_null_page", TRUE);
	else
		pLeftListTab->SetCurSel(L"lasttalk_page", TRUE);
}

void CMainDlg::OnBnClickContact()
{
	SImageButton* pBtnMessage = FindChildByName2<SImageButton>(L"btn_message");
	SImageButton* pBtnContact = FindChildByName2<SImageButton>(L"btn_contact");
	SASSERT(pBtnMessage);
	SASSERT(pBtnContact);

	pBtnMessage->SetCheck(FALSE);
	pBtnContact->SetCheck(TRUE);

	STabCtrl* pLeftListTab = FindChildByName2<STabCtrl>(L"left_tab");
	SASSERT(pLeftListTab);
	pLeftListTab->SetCurSel(L"contact_page", TRUE);

	//GetRoot()->Invalidate();
}

void CMainDlg::OnBnClickSearchCancel()
{
	SEdit *pEdit = FindChildByName2<SEdit>(L"search_edit");
	SASSERT(pEdit);
	pEdit->SetWindowText(L"");
}

bool CMainDlg::OnEditSearchSetFocus(EventArgs* pEvt)
{
	return true;
}

bool CMainDlg::OnEditSearchKillFocus(EventArgs* pEvt)
{
	return true;
}

bool CMainDlg::OnEditSearchChanged(EventArgs *e)
{
	EventRENotify *e2 = sobj_cast<EventRENotify>(e);
	if(e2->iNotify != EN_CHANGE) 
		return false;

	SEdit *pEdit = sobj_cast<SEdit>(e->sender);
	SStringW sstrInput = pEdit->GetWindowText();
	std::wstring wstrInput = sstrInput;

	return true;
}

void CMainDlg::LasttalkItemClick(int nType, const std::string& strID)
{
	//
}

void CMainDlg::LasttalkItemRClick(int nType, const std::string& strID)
{
	//
}

void CMainDlg::LasttalkItemDelete(int nType, const std::string& strID)
{
	//
}

void CMainDlg::ContactItemClick(int nType, const std::string& strID)
{
	//
}

void CMainDlg::ContactItemRClick(int nType, const std::string& strID)
{
	//
}

void CMainDlg::ContactItemDBClick(int nType, const std::string& strID)
{
	//
}

void CMainDlg::InitLasttalkList()
{
	STabCtrl* pLeftListTab = FindChildByName2<STabCtrl>(L"left_tab");
	SASSERT(pLeftListTab);
	if (CDataCenter::getSingleton().m_mapLasttalks.empty()){
		pLeftListTab->SetCurSel(L"lasttalk_null_page", TRUE);
	}
	else
	{
		//add lasttalk
	}
}

void CMainDlg::OnBindPortFailed(EventArgs* e)
{
	EventBindPortFailed* pEvt = sobj_cast<EventBindPortFailed>(e);
	if (pEvt)
	{
		//提示绑定端口号失败！
		//退出进程
	}
}

void CMainDlg::OnFindDevice(EventArgs *e)
{
	EventFindDevice* pEvt = sobj_cast<EventFindDevice>(e);
	if (pEvt)
	{
		/*	2019-04-09 modify by yangjinpeng
		* 1、新设备上线发送的广播消息
		* 2、将该设备加入到通讯录中
		* 3、向该设备回一个自己信息
		*/

		//add contact
		m_pAdapterContact->AddContact(2, pEvt->m_strClientID);

		//broadcast_request
		CUDPSender::getSingleton().SendBroadcastRequest(pEvt->m_strIP, 
			CDataCenter::getSingleton().m_LocalInfo.m_strName.c_str(),
			CDataCenter::getSingleton().m_LocalInfo.m_strClientID.c_str(), 
			pEvt->m_nPort);
	}
}

void CMainDlg::OnBroadcastRequest(EventArgs* e)
{
	EventBroadcastRequest* pEvt = sobj_cast<EventBroadcastRequest>(e);
	if (pEvt)
	{
		//add contact
		m_pAdapterContact->AddContact(2, pEvt->m_strClientID);
	}
}

void CMainDlg::OnSendText(EventArgs* e)
{
	EventSendText* pEvt = sobj_cast<EventSendText>(e);
	if (pEvt)
	{
		//
	}
}

void CMainDlg::OnSendImage(EventArgs* e)
{
	EventSendImage* pEvt = sobj_cast<EventSendImage>(e);
	if (pEvt)
	{
		//
	}
}

void CMainDlg::OnSendFile(EventArgs* e)
{
	EventSendFile* pEvt = sobj_cast<EventSendFile>(e);
	if (pEvt)
	{
		//
	}
}

void CMainDlg::OnSendAudio(EventArgs* e)
{
	EventSendAudio* pEvt = sobj_cast<EventSendAudio>(e);
	if (pEvt)
	{
		//
	}
}

void CMainDlg::OnSendVideo(EventArgs* e)
{
	EventSendVideo* pEvt = sobj_cast<EventSendVideo>(e);
	if (pEvt)
	{
		//
	}
}