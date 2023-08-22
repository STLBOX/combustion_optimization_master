// ON_FUEL.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "CON_FUEL.h"
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
// CON_FUEL dialog


CON_FUEL::CON_FUEL(CWnd* pParent /*=NULL*/)
	: CDialog(CON_FUEL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_FUEL)
	m_CombOptInt_upLimit_fuel1 = dp->pCombOptOP[260];  // 绝对上限
	m_CombOptInt_upLimit_fuel2 = dp->pCombOptOP[261];
	m_CombOptInt_upLimit_fuel3 = dp->pCombOptOP[262];
	m_CombOptInt_upLimit_fuel4 = dp->pCombOptOP[263];
	m_CombOptInt_upLimit_fuel5 = dp->pCombOptOP[264];
	m_CombOptInt_upLimit_fuel6 = dp->pCombOptOP[265];
	m_CombOptInt_downLimit_fuel1 = dp->pCombOptOP[238];  // 绝对下限
	m_CombOptInt_downLimit_fuel2 = dp->pCombOptOP[239];
	m_CombOptInt_downLimit_fuel3 = dp->pCombOptOP[240];
	m_CombOptInt_downLimit_fuel4 = dp->pCombOptOP[241];
	m_CombOptInt_downLimit_fuel5 = dp->pCombOptOP[242];
	m_CombOptInt_downLimit_fuel6 = dp->pCombOptOP[243];
	m_CombOptInt_dumax_fuel1 = dp->pCombOptOP[35];  // 优化上限
	m_CombOptInt_dumax_fuel2 = dp->pCombOptOP[36];
	m_CombOptInt_dumax_fuel3 = dp->pCombOptOP[37];
	m_CombOptInt_dumax_fuel4 = dp->pCombOptOP[38];
	m_CombOptInt_dumax_fuel5 = dp->pCombOptOP[39];
	m_CombOptInt_dumax_fuel6 = dp->pCombOptOP[40];
	m_CombOptInt_dumin_fuel1 = dp->pCombOptOP[57];  // 优化下限
	m_CombOptInt_dumin_fuel2 = dp->pCombOptOP[58];
	m_CombOptInt_dumin_fuel3 = dp->pCombOptOP[59];
	m_CombOptInt_dumin_fuel4 = dp->pCombOptOP[60];
	m_CombOptInt_dumin_fuel5 = dp->pCombOptOP[61];
	m_CombOptInt_dumin_fuel6 = dp->pCombOptOP[62];
	m_CombOptInt_dumax_fuel7 = dp->pCombOptOP[79];  // 变化速率约束
	m_CombOptInt_dumax_fuel8 = dp->pCombOptOP[80];
	m_CombOptInt_dumax_fuel9 = dp->pCombOptOP[81];
	m_CombOptInt_dumax_fuel10 = dp->pCombOptOP[82];
	m_CombOptInt_dumax_fuel11 = dp->pCombOptOP[83];
	m_CombOptInt_dumax_fuel12 = dp->pCombOptOP[84];
	m_DzFuelA = dp->pCombOptOP[101];  // 输出死区
	m_DzFuelB = dp->pCombOptOP[102];
	m_DzFuelC = dp->pCombOptOP[103];
	m_DzFuelD = dp->pCombOptOP[104];
	m_DzFuelF = dp->pCombOptOP[105];
	m_DzFuelE = dp->pCombOptOP[106];
	//}}AFX_DATA_INIT
}


void CON_FUEL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_FUEL)
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel1, m_CombOptInt_upLimit_fuel1);
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel2, m_CombOptInt_upLimit_fuel2);
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel3, m_CombOptInt_upLimit_fuel3);
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel4, m_CombOptInt_upLimit_fuel4);
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel5, m_CombOptInt_upLimit_fuel5);
	DDX_Text(pDX, IDC_EDIT_upLimit_fuel6, m_CombOptInt_upLimit_fuel6);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel1, m_CombOptInt_downLimit_fuel1);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel2, m_CombOptInt_downLimit_fuel2);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel3, m_CombOptInt_downLimit_fuel3);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel4, m_CombOptInt_downLimit_fuel4);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel5, m_CombOptInt_downLimit_fuel5);
	DDX_Text(pDX, IDC_EDIT_downLimit_fuel6, m_CombOptInt_downLimit_fuel6);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel1, m_CombOptInt_dumax_fuel1);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel2, m_CombOptInt_dumax_fuel2);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel3, m_CombOptInt_dumax_fuel3);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel4, m_CombOptInt_dumax_fuel4);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel5, m_CombOptInt_dumax_fuel5);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel6, m_CombOptInt_dumax_fuel6);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel1, m_CombOptInt_dumin_fuel1);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel2, m_CombOptInt_dumin_fuel2);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel3, m_CombOptInt_dumin_fuel3);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel4, m_CombOptInt_dumin_fuel4);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel5, m_CombOptInt_dumin_fuel5);
	DDX_Text(pDX, IDC_EDIT_dumin_fuel6, m_CombOptInt_dumin_fuel6);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel7, m_CombOptInt_dumax_fuel7);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel8, m_CombOptInt_dumax_fuel8);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel9, m_CombOptInt_dumax_fuel9);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel10, m_CombOptInt_dumax_fuel10);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel11, m_CombOptInt_dumax_fuel11);
	DDX_Text(pDX, IDC_EDIT_dumax_fuel12, m_CombOptInt_dumax_fuel12);
	DDX_Text(pDX, IDC_EDIT_DzFuelA, m_DzFuelA);
	DDX_Text(pDX, IDC_EDIT_DzFuelB, m_DzFuelB);
	DDX_Text(pDX, IDC_EDIT_DzFuelC, m_DzFuelC);
	DDX_Text(pDX, IDC_EDIT_DzFuelD, m_DzFuelD);
	DDX_Text(pDX, IDC_EDIT_DzFuelF, m_DzFuelF);
	DDX_Text(pDX, IDC_EDIT_DzFuelE, m_DzFuelE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_FUEL, CDialog)
	//{{AFX_MSG_MAP(CON_FUEL)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_FUEL message handlers

void CON_FUEL::OnOK() 
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

		dp->pCombOptOP[260] = m_CombOptInt_upLimit_fuel1;  // 绝对上限
		dp->pCombOptOP[261] = m_CombOptInt_upLimit_fuel2;
		dp->pCombOptOP[262] = m_CombOptInt_upLimit_fuel3;
		dp->pCombOptOP[263] = m_CombOptInt_upLimit_fuel4;
		dp->pCombOptOP[264] = m_CombOptInt_upLimit_fuel5;
		dp->pCombOptOP[265] = m_CombOptInt_upLimit_fuel6;

		dp->pCombOptOP[238] = m_CombOptInt_downLimit_fuel1;  // 绝对下限
		dp->pCombOptOP[239] = m_CombOptInt_downLimit_fuel2;
		dp->pCombOptOP[240] = m_CombOptInt_downLimit_fuel3;
		dp->pCombOptOP[241] = m_CombOptInt_downLimit_fuel4;
		dp->pCombOptOP[242] = m_CombOptInt_downLimit_fuel5;
		dp->pCombOptOP[243] = m_CombOptInt_downLimit_fuel6;

		dp->pCombOptOP[35] = m_CombOptInt_dumax_fuel1;  // 优化上限
		dp->pCombOptOP[36] = m_CombOptInt_dumax_fuel2;
		dp->pCombOptOP[37] = m_CombOptInt_dumax_fuel3;
		dp->pCombOptOP[38] = m_CombOptInt_dumax_fuel4;
		dp->pCombOptOP[39] = m_CombOptInt_dumax_fuel5;
		dp->pCombOptOP[40] = m_CombOptInt_dumax_fuel6;

		dp->pCombOptOP[57] = m_CombOptInt_dumin_fuel1;  // 优化下限
		dp->pCombOptOP[58] = m_CombOptInt_dumin_fuel2;
		dp->pCombOptOP[59] = m_CombOptInt_dumin_fuel3;
		dp->pCombOptOP[60] = m_CombOptInt_dumin_fuel4;
		dp->pCombOptOP[61] = m_CombOptInt_dumin_fuel5;
		dp->pCombOptOP[62] = m_CombOptInt_dumin_fuel6;

		dp->pCombOptOP[79] = m_CombOptInt_dumax_fuel7;  // 速率约束
		dp->pCombOptOP[80] = m_CombOptInt_dumax_fuel8;
		dp->pCombOptOP[81] = m_CombOptInt_dumax_fuel9;
		dp->pCombOptOP[82] = m_CombOptInt_dumax_fuel10;
		dp->pCombOptOP[83] = m_CombOptInt_dumax_fuel11;
		dp->pCombOptOP[84] = m_CombOptInt_dumax_fuel12;

        dp->pCombOptOP[101] = m_DzFuelA;  // 输出死区
	    dp->pCombOptOP[102] = m_DzFuelB;
        dp->pCombOptOP[103] = m_DzFuelC;
	    dp->pCombOptOP[104] = m_DzFuelD;
	    dp->pCombOptOP[105] = m_DzFuelF;
	    dp->pCombOptOP[106] = m_DzFuelE;
		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");

		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}
   
}


void CON_FUEL::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	SendMessage(WM_CLOSE);
}
