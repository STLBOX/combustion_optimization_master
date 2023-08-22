// ON_O2.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "CON_O2.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
extern CInterfaceDlg* dp;
// fix: 全局变量
extern ObjCombOpt theComb;
//

/////////////////////////////////////////////////////////////////////////////
// CON_O2 dialog


CON_O2::CON_O2(CWnd* pParent /*=NULL*/)
	: CDialog(CON_O2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_O2)
	m_CombOptInt_upLimit_O = dp->pCombOptOP[259];
	m_CombOptInt_downLimit_O = dp->pCombOptOP[237];
	m_CombOptInt_dumax_O = dp->pCombOptOP[34];
	m_CombOptInt_dumin_O = dp->pCombOptOP[56];
	m_CombOptInt_dumax_O_2 = dp->pCombOptOP[78];
	m_DzO2 = dp->pCombOptOP[100];
	//}}AFX_DATA_INIT
}


void CON_O2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_O2)
	DDX_Text(pDX, IDC_EDIT_upLimit_O, m_CombOptInt_upLimit_O);
	DDX_Text(pDX, IDC_EDIT_downLimit_O, m_CombOptInt_downLimit_O);
	DDX_Text(pDX, IDC_EDIT_dumax_O, m_CombOptInt_dumax_O);
	DDX_Text(pDX, IDC_EDIT_dumin_O, m_CombOptInt_dumin_O);
	DDX_Text(pDX, IDC_EDIT_dumax_O_2, m_CombOptInt_dumax_O_2);
	DDX_Text(pDX, IDC_EDIT_DzO2, m_DzO2);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_O2, CDialog)
	//{{AFX_MSG_MAP(CON_O2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_O2 message handlers

void CON_O2::OnOK() 
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
		
		dp->pCombOptOP[259] = m_CombOptInt_upLimit_O;
		dp->pCombOptOP[237] = m_CombOptInt_downLimit_O;
		dp->pCombOptOP[34] = m_CombOptInt_dumax_O;
		dp->pCombOptOP[56] = m_CombOptInt_dumin_O;
		dp->pCombOptOP[78] = m_CombOptInt_dumax_O_2;
        dp->pCombOptOP[100] = m_DzO2;

		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");
		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}

}

void CON_O2::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	SendMessage(WM_CLOSE);
}
