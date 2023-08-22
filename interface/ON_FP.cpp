// ON_FP.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "ON_FP.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CON_FP dialog

extern CInterfaceDlg* dp;
// fix: 全局变量
extern ObjCombOpt theComb;

CON_FP::CON_FP(CWnd* pParent /*=NULL*/)
	: CDialog(CON_FP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_FP)
	m_upLimit_Fp = dp->pCombOptOP[212];
	m_downlimit_Fp = dp->pCombOptOP[213];
	m_dumax_Fp = dp->pCombOptOP[207];
	m_dumin_Fp = dp->pCombOptOP[208];
	m_DzFp = dp->pCombOptOP[210];
	m_rt_Fp = dp->pCombOptOP[209];

	//}}AFX_DATA_INIT
}


void CON_FP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_FP)
	DDX_Text(pDX, IDC_EDIT_downLimit_Fp, m_downlimit_Fp);
	DDX_Text(pDX, IDC_EDIT_dumax_Fp, m_dumax_Fp);
	DDX_Text(pDX, IDC_EDIT_dumin_Fp, m_dumin_Fp);
	DDX_Text(pDX, IDC_EDIT_DzFp, m_DzFp);
	DDX_Text(pDX, IDC_EDIT_rt_Fp, m_rt_Fp);
	DDX_Text(pDX, IDC_EDIT_upLimit_Fp, m_upLimit_Fp);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_FP, CDialog)
	//{{AFX_MSG_MAP(CON_FP)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_FP message handlers

void CON_FP::OnOK() 
{
	// TODO: Add extra validation here
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
		
		dp->pCombOptOP[212] = m_upLimit_Fp;
	    dp->pCombOptOP[213] = m_downlimit_Fp;
	    dp->pCombOptOP[207] = m_dumax_Fp;
    	dp->pCombOptOP[208] = m_dumin_Fp;
	    dp->pCombOptOP[210] = m_DzFp;
	    dp->pCombOptOP[209] = m_rt_Fp;

		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");
		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}
	CDialog::OnOK();
}

void CON_FP::OnCancel() 
{
	// TODO: Add extra cleanup here
		// TODO: Add extra cleanup here
	SendMessage(WM_CLOSE);
	CDialog::OnCancel();
}
