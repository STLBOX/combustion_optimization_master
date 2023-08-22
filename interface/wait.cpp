// Wait.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "Wait.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CInterfaceDlg* dp;
extern ObjCombOpt theComb;

/////////////////////////////////////////////////////////////////////////////
// CWait dialog

CWait::CWait(int inModePara, CWnd* pParent /*=NULL*/)
	: CDialog(CWait::IDD, pParent)
{
	//{{AFX_DATA_INIT(CWait)
	m_Wait_Msg = _T("");
	//}}AFX_DATA_INIT
	ModePara = inModePara;
}


void CWait::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CWait)
	DDX_Text(pDX, IDC_Wait_EDIT1, m_Wait_Msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CWait, CDialog)
	//{{AFX_MSG_MAP(CWait)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CWait message handlers

BOOL CWait::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	TimeCount = 0;
	SetTimer(1,200,NULL);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

BOOL CWait::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->wParam==VK_RETURN)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if((pMsg->wParam==VK_ESCAPE)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if(pMsg->message==WM_RBUTTONDOWN)    //禁止右键
		return true;
	if(pMsg->message==EM_SETSEL)
		return true;

	return CDialog::PreTranslateMessage(pMsg);
}

void CWait::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}

void CWait::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	// 防止等待CombOpt进程时间过久
    dp->WaitTime=dp->WaitTime+1;
	if (dp->WaitTime >= dp->MaxWaitTime)
	{
		dp->WaitTime=-1;  // -1表示报错
		SendMessage(WM_CLOSE);
	}

	switch(ModePara)
	{
	case WaitCombOptStart://新修改
		m_Wait_Msg = _T("燃烧优化启动中");

		if(int(dp->pCombOptOP[358])==1)  // 燃烧优化进程正常初始化，并开始track
		{
			dp->WaitTime=0;
			SendMessage(WM_CLOSE);
		}
		else if(int(dp->pCombOptOP[385])==-1)   // 燃烧优化进程初始化错误
		{
			dp->WaitTime=-2;
			SendMessage(WM_CLOSE);
		}
		break;


	case WaitCombOptStop://新修改
		m_Wait_Msg = _T("燃烧优化退出中");

		if(int(dp->pCombOptOP[358])==0)  // 燃烧优化进程正常退出
		{
			dp->WaitTime=0;
			dp->PI[1].pi.hProcess = INVALID_HANDLE_VALUE;
			SendMessage(WM_CLOSE);
		}
		break;


	default:
		SendMessage(WM_CLOSE);
	}

	switch(TimeCount)
	{
	case 0:
		m_Wait_Msg = m_Wait_Msg+_T("");
		break;
	case 1:
		m_Wait_Msg = m_Wait_Msg+_T(".");
		break;
	case 2:
		m_Wait_Msg = m_Wait_Msg+_T("..");
		break;
	case 3:
		m_Wait_Msg = m_Wait_Msg+_T("...");
		TimeCount = 0;
		break;
	}
	UpdateData(FALSE);
	TimeCount++;

	CDialog::OnTimer(nIDEvent);
}
