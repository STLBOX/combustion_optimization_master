//ON_SOFA.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "CON_SOFA.h"
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
// CON_SOFA dialog


CON_SOFA::CON_SOFA(CWnd* pParent /*=NULL*/)
	: CDialog(CON_SOFA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_SOFA)
	m_CombOptInt_upLimit_sofa123 = dp->pCombOptOP[244];  // 后墙 123
	m_CombOptInt_upLimit_sofa456 = dp->pCombOptOP[245];  // 前墙 456
	m_CombOptInt_downLimit_sofa123 = dp->pCombOptOP[222];  // 绝对下限
	m_CombOptInt_downLimit_sofa456 = dp->pCombOptOP[223];
	m_CombOptInt_dumax_sofa123 = dp->pCombOptOP[19];  // 优化区间上限
	m_CombOptInt_dumax_sofa456 = dp->pCombOptOP[20];
	m_CombOptInt_dumin_sofa123 = dp->pCombOptOP[41];
	m_CombOptInt_dumin_sofa456 = dp->pCombOptOP[42];
	m_CombOptInt_suLimit_sofa123 = dp->pCombOptOP[63];  // 速率
	m_CombOptInt_suLimit_sofa456 = dp->pCombOptOP[64];
	m_DzSofa123 = dp->pCombOptOP[85];
	m_DzSofa456 = dp->pCombOptOP[86];
	//}}AFX_DATA_INIT
}


void CON_SOFA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_SOFA)
	DDX_Text(pDX, IDC_EDIT_upLimit_sofa123, m_CombOptInt_upLimit_sofa123);
	DDX_Text(pDX, IDC_EDIT_upLimit_sofa456, m_CombOptInt_upLimit_sofa456);
	DDX_Text(pDX, IDC_EDIT_downLimit_sofa123, m_CombOptInt_downLimit_sofa123);
	DDX_Text(pDX, IDC_EDIT_downLimit_sofa456, m_CombOptInt_downLimit_sofa456);
	DDX_Text(pDX, IDC_EDIT_dumax_sofa123, m_CombOptInt_dumax_sofa123);
	DDX_Text(pDX, IDC_EDIT_dumax_sofa456, m_CombOptInt_dumax_sofa456);
	DDX_Text(pDX, IDC_EDIT_dumin_sofa123, m_CombOptInt_dumin_sofa123);
	DDX_Text(pDX, IDC_EDIT_dumin_sofa456, m_CombOptInt_dumin_sofa456);
	DDX_Text(pDX, IDC_EDIT_suLimit_sofa123, m_CombOptInt_suLimit_sofa123);
	DDX_Text(pDX, IDC_EDIT_suLimit_sofa456, m_CombOptInt_suLimit_sofa456);
	DDX_Text(pDX, IDC_EDIT_DzSofa123, m_DzSofa123);
	DDX_Text(pDX, IDC_EDIT_DzSofa456, m_DzSofa456);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_SOFA, CDialog)
	//{{AFX_MSG_MAP(CON_SOFA)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_SOFA message handlers

void CON_SOFA::OnOK() 
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
		

		dp->pCombOptOP[244] = m_CombOptInt_upLimit_sofa123;
		dp->pCombOptOP[245] = m_CombOptInt_upLimit_sofa456;
		dp->pCombOptOP[222] = m_CombOptInt_downLimit_sofa123;
		dp->pCombOptOP[223] = m_CombOptInt_downLimit_sofa456;
		dp->pCombOptOP[19] = m_CombOptInt_dumax_sofa123;
		dp->pCombOptOP[20] = m_CombOptInt_dumax_sofa456;
		dp->pCombOptOP[41] = m_CombOptInt_dumin_sofa123;
		dp->pCombOptOP[42] = m_CombOptInt_dumin_sofa456;
		dp->pCombOptOP[63] = m_CombOptInt_suLimit_sofa123;
		dp->pCombOptOP[64] = m_CombOptInt_suLimit_sofa456;
		dp->pCombOptOP[85] = m_DzSofa123;
        dp->pCombOptOP[86] = m_DzSofa456;

		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");

		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}
   
}

void CON_SOFA::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	SendMessage(WM_CLOSE);
}
