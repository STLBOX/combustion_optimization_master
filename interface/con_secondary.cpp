// ON_SECONDARY.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "CON_SECONDARY.h"
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
// CON_SECONDARY dialog


CON_SECONDARY::CON_SECONDARY(CWnd* pParent /*=NULL*/)
	: CDialog(CON_SECONDARY::IDD, pParent)
{
	//{{AFX_DATA_INIT(CON_SECONDARY)

	m_CombOptInt_upLimit_A = dp->pCombOptOP[246];  // 最大开度
	m_CombOptInt_upLimit_F = dp->pCombOptOP[247];
	m_CombOptInt_upLimit_E = dp->pCombOptOP[248];
	m_CombOptInt_upLimit_B = dp->pCombOptOP[249];
	m_CombOptInt_upLimit_C = dp->pCombOptOP[250];
	m_CombOptInt_upLimit_D = dp->pCombOptOP[251];

	m_CombOptInt_downLimit_A = dp->pCombOptOP[224];  // 最小开度
	m_CombOptInt_downLimit_F = dp->pCombOptOP[225];
	m_CombOptInt_downLimit_E = dp->pCombOptOP[226];	
	m_CombOptInt_downLimit_B = dp->pCombOptOP[227];
	m_CombOptInt_downLimit_C = dp->pCombOptOP[228];
	m_CombOptInt_downLimit_D = dp->pCombOptOP[229];

	m_CombOptInt_dumax_A = dp->pCombOptOP[21];  // 增量上限
	m_CombOptInt_dumax_F = dp->pCombOptOP[22];
	m_CombOptInt_dumax_E = dp->pCombOptOP[23];
	m_CombOptInt_dumax_B = dp->pCombOptOP[24];
	m_CombOptInt_dumax_C = dp->pCombOptOP[25];
	m_CombOptInt_dumax_D = dp->pCombOptOP[26];

	m_CombOptInt_dumin_A = dp->pCombOptOP[43];  // 增量下限
	m_CombOptInt_dumin_F = dp->pCombOptOP[44];
	m_CombOptInt_dumin_E = dp->pCombOptOP[45];
	m_CombOptInt_dumin_B = dp->pCombOptOP[46];
	m_CombOptInt_dumin_C = dp->pCombOptOP[47];
	m_CombOptInt_dumin_D = dp->pCombOptOP[48];

	m_CombOptInt_suLimit_A = dp->pCombOptOP[65];  // 速度
	m_CombOptInt_suLimit_F = dp->pCombOptOP[66];
	m_CombOptInt_suLimit_E = dp->pCombOptOP[67];
	m_CombOptInt_suLimit_B = dp->pCombOptOP[68];
	m_CombOptInt_suLimit_C = dp->pCombOptOP[69];
	m_CombOptInt_suLimit_D = dp->pCombOptOP[70];


	m_DzSecA = dp->pCombOptOP[87];  // 死区
	m_DzSecF = dp->pCombOptOP[88];
	m_DzSecE = dp->pCombOptOP[89];
	m_DzSecB = dp->pCombOptOP[90];
	m_DzSecC = dp->pCombOptOP[91];
	m_DzSecD = dp->pCombOptOP[92];

	//}}AFX_DATA_INIT
}


void CON_SECONDARY::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CON_SECONDARY)

	DDX_Text(pDX, IDC_EDIT_upLimit_A, m_CombOptInt_upLimit_A);
	DDX_Text(pDX, IDC_EDIT_upLimit_B, m_CombOptInt_upLimit_B);
	DDX_Text(pDX, IDC_EDIT_upLimit_C, m_CombOptInt_upLimit_C);
	DDX_Text(pDX, IDC_EDIT_upLimit_D, m_CombOptInt_upLimit_D);
	DDX_Text(pDX, IDC_EDIT_upLimit_E, m_CombOptInt_upLimit_E);
	DDX_Text(pDX, IDC_EDIT_upLimit_F, m_CombOptInt_upLimit_F);


	DDX_Text(pDX, IDC_EDIT_downLimit_A, m_CombOptInt_downLimit_A);
	DDX_Text(pDX, IDC_EDIT_downLimit_B, m_CombOptInt_downLimit_B);
	DDX_Text(pDX, IDC_EDIT_downLimit_C, m_CombOptInt_downLimit_C);
	DDX_Text(pDX, IDC_EDIT_downLimit_D, m_CombOptInt_downLimit_D);
	DDX_Text(pDX, IDC_EDIT_downLimit_E, m_CombOptInt_downLimit_E);
	DDX_Text(pDX, IDC_EDIT_downLimit_F, m_CombOptInt_downLimit_F);


	DDX_Text(pDX, IDC_EDIT_dumax_A, m_CombOptInt_dumax_A);
	DDX_Text(pDX, IDC_EDIT_dumax_B, m_CombOptInt_dumax_B);
	DDX_Text(pDX, IDC_EDIT_dumax_C, m_CombOptInt_dumax_C);
	DDX_Text(pDX, IDC_EDIT_dumax_D, m_CombOptInt_dumax_D);
	DDX_Text(pDX, IDC_EDIT_dumax_E, m_CombOptInt_dumax_E);
	DDX_Text(pDX, IDC_EDIT_dumax_F, m_CombOptInt_dumax_F);

	DDX_Text(pDX, IDC_EDIT_dumin_A, m_CombOptInt_dumin_A);
	DDX_Text(pDX, IDC_EDIT_dumin_B, m_CombOptInt_dumin_B);
	DDX_Text(pDX, IDC_EDIT_dumin_C, m_CombOptInt_dumin_C);
	DDX_Text(pDX, IDC_EDIT_dumin_D, m_CombOptInt_dumin_D);
	DDX_Text(pDX, IDC_EDIT_dumin_E, m_CombOptInt_dumin_E);
	DDX_Text(pDX, IDC_EDIT_dumin_F, m_CombOptInt_dumin_F);


	DDX_Text(pDX, IDC_EDIT_suLimit_A, m_CombOptInt_suLimit_A);
	DDX_Text(pDX, IDC_EDIT_suLimit_B, m_CombOptInt_suLimit_B);
	DDX_Text(pDX, IDC_EDIT_suLimit_C, m_CombOptInt_suLimit_C);
	DDX_Text(pDX, IDC_EDIT_suLimit_D, m_CombOptInt_suLimit_D);
	DDX_Text(pDX, IDC_EDIT_suLimit_E, m_CombOptInt_suLimit_E);
	DDX_Text(pDX, IDC_EDIT_suLimit_F, m_CombOptInt_suLimit_F);

	DDX_Text(pDX, IDC_EDIT_DzSecA, m_DzSecA);
	DDX_Text(pDX, IDC_EDIT_DzSecB, m_DzSecB);
	DDX_Text(pDX, IDC_EDIT_DzSecC, m_DzSecC);
	DDX_Text(pDX, IDC_EDIT_DzSecD, m_DzSecD);
	DDX_Text(pDX, IDC_EDIT_DzSecE, m_DzSecE);
	DDX_Text(pDX, IDC_EDIT_DzSecF, m_DzSecF);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CON_SECONDARY, CDialog)
	//{{AFX_MSG_MAP(CON_SECONDARY)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CON_SECONDARY message handlers

void CON_SECONDARY::OnOK() 
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
		

		dp->pCombOptOP[246] = m_CombOptInt_upLimit_A;
		dp->pCombOptOP[247] = m_CombOptInt_upLimit_F;
		dp->pCombOptOP[248] = m_CombOptInt_upLimit_E;
		dp->pCombOptOP[249] = m_CombOptInt_upLimit_B;
		dp->pCombOptOP[250] = m_CombOptInt_upLimit_C;
		dp->pCombOptOP[251] = m_CombOptInt_upLimit_D;


		dp->pCombOptOP[224] = m_CombOptInt_downLimit_A;
		dp->pCombOptOP[225] = m_CombOptInt_downLimit_F;
		dp->pCombOptOP[226] = m_CombOptInt_downLimit_E;
		dp->pCombOptOP[227] = m_CombOptInt_downLimit_B;
		dp->pCombOptOP[228] = m_CombOptInt_downLimit_C;
		dp->pCombOptOP[229] = m_CombOptInt_downLimit_D;


		dp->pCombOptOP[21] = m_CombOptInt_dumax_A;
		dp->pCombOptOP[22] = m_CombOptInt_dumax_F;
		dp->pCombOptOP[23] = m_CombOptInt_dumax_E;
		dp->pCombOptOP[24] = m_CombOptInt_dumax_B;
		dp->pCombOptOP[25] = m_CombOptInt_dumax_C;
		dp->pCombOptOP[26] = m_CombOptInt_dumax_D;

	
		dp->pCombOptOP[43] = m_CombOptInt_dumin_A;
		dp->pCombOptOP[44] = m_CombOptInt_dumin_F;
		dp->pCombOptOP[45] = m_CombOptInt_dumin_E;
		dp->pCombOptOP[46] = m_CombOptInt_dumin_B;
		dp->pCombOptOP[47] = m_CombOptInt_dumin_C;
		dp->pCombOptOP[48] = m_CombOptInt_dumin_D;


		dp->pCombOptOP[65] = m_CombOptInt_suLimit_A;
		dp->pCombOptOP[66] = m_CombOptInt_suLimit_F;
		dp->pCombOptOP[67] = m_CombOptInt_suLimit_E;
		dp->pCombOptOP[68] = m_CombOptInt_suLimit_B;
		dp->pCombOptOP[69] = m_CombOptInt_suLimit_C;
		dp->pCombOptOP[70] = m_CombOptInt_suLimit_D;


		dp->pCombOptOP[87] = m_DzSecA;
		dp->pCombOptOP[88] = m_DzSecF;
		dp->pCombOptOP[89] = m_DzSecE;	
		dp->pCombOptOP[90] = m_DzSecB;
		dp->pCombOptOP[91] = m_DzSecC;
		dp->pCombOptOP[92] = m_DzSecD;
	
		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");

		dp->LogSystem(outLog,_T("修改控制参数成功！"));
		outLog.close();
		MessageBox(_T("修改控制参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}

}

void CON_SECONDARY::OnCancel() 
{
	// TODO: Add extra cleanup here
	
	CDialog::OnCancel();
	SendMessage(WM_CLOSE);
}