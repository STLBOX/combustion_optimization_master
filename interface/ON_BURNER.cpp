// ON_BURNER.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "ON_BURNER.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CON_BURNER dialog

extern CInterfaceDlg* dp;
extern ObjCombOpt theComb;


CON_BURNER::CON_BURNER(CWnd* pParent /*=NULL*/)
	: CDialog(CON_BURNER::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_BURNER)
	m_ul_burner = dp->pCombOptOP[158];
	m_dl_burner = dp->pCombOptOP[158];

	m_dumax_burner = dp->pCombOptOP[153];
	m_dumin_burner = dp->pCombOptOP[154];
	m_rate_burner = dp->pCombOptOP[155];
	m_dz_burner = dp->pCombOptOP[156];
	//}}AFX_DATA_INIT
}


void CON_BURNER::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_BURNER)
	DDX_Text(pDX, IDC_EDIT_downLimit_burner, m_dl_burner);
	DDX_Text(pDX, IDC_EDIT_dumax_burner, m_dumax_burner);
	DDX_Text(pDX, IDC_EDIT_dumin_burner, m_dumin_burner);
	DDX_Text(pDX, IDC_EDIT_rate_burner, m_rate_burner);
	DDX_Text(pDX, IDC_EDIT_upLimit_burner, m_ul_burner);
	DDX_Text(pDX, IDC_EDIT_dz_burner, m_dz_burner);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_BURNER, CDialog)
	//{{AFX_MSG_MAP(CON_BURNER)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_BURNER message handlers

void CON_BURNER::OnOK() 
{
	// TODO: Add extra validation here
	
	CDialog::OnOK();
	if(MessageBox(_T("确定修改? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		UpdateData(TRUE);
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		dp->LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+dp->LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
		dp->LogSystem(outLog,_T("修改优化控制参数..."));

		dp->pCombOptOP[158] = m_ul_burner;
		dp->pCombOptOP[159] = m_dl_burner;
		dp->pCombOptOP[153] = m_dumax_burner;
		dp->pCombOptOP[154] = m_dumin_burner;
	    dp->pCombOptOP[155] = m_rate_burner;
		dp->pCombOptOP[156] = m_dz_burner;

		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");
		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}
	CDialog::OnOK();
}

void CON_BURNER::OnCancel() 
{
	// TODO: Add extra cleanup here
	SendMessage(WM_CLOSE);
	CDialog::OnCancel();
	CDialog::OnCancel();
}
