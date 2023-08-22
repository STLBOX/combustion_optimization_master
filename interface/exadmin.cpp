// ExAdmin.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "ExAdmin.h"
#include "InterfaceDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CInterfaceDlg* dp;


CExAdmin::CExAdmin(CWnd* pParent /*=NULL*/)
	: CDialog(CExAdmin::IDD, pParent)
{
	//{{AFX_DATA_INIT(CExAdmin)
	m_ExAdmin_szStr = _T("");
	//}}AFX_DATA_INIT
}


void CExAdmin::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CExAdmin)
	DDX_Text(pDX, IDC_ExAdmin_EDIT1, m_ExAdmin_szStr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CExAdmin, CDialog)
	//{{AFX_MSG_MAP(CExAdmin)
	ON_BN_CLICKED(IDC_ExAdmin_OK, OnExAdminOK)
	ON_BN_CLICKED(IDC_ExAdmin_Logout, OnExAdminLogout)
	ON_BN_CLICKED(IDC_ExAdmin_Cancel, OnExAdminCancel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()



BOOL CExAdmin::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->wParam==VK_RETURN)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if((pMsg->wParam==VK_ESCAPE)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if(pMsg->message==WM_RBUTTONDOWN)    //禁止右键
		return true;
	
	return CDialog::PreTranslateMessage(pMsg);
}


void CExAdmin::OnExAdminOK() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_ExAdmin_szStr.Compare(_T("OK")) == 0)
	{
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		dp->LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+dp->LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
	
		dp->bAdmin = TRUE;

		dp->LogSystem(outLog,_T("更改权限成功（Admin）！"));
		outLog.close();
		
		SendMessage(WM_CLOSE);
	}
	else
	{
		MessageBox(_T("输入错误！"),_T("Interface警告："),MB_ICONWARNING);
	}
}

void CExAdmin::OnExAdminLogout() 
{
	// TODO: Add your control notification handler code here
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString LogFile(szPath);
	LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
	dp->LogTime = CTime::GetCurrentTime();
	LogFile = LogFile+dp->LogTime.Format("Log\\%Y%m%dInterface.log");
	ofstream outLog(LogFile,ios::out|ios::app);
	
	dp->bAdmin = FALSE;
	dp->LogSystem(outLog,_T("注销权限成功（Guest）！"));
	outLog.close();
	
	SendMessage(WM_CLOSE);
}

void CExAdmin::OnExAdminCancel() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}
