// CombOpt_ModTun.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "CombOpt_ModTun.h"
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
// CombOpt_ModTun dialog


CombOpt_ModTun::CombOpt_ModTun(CWnd* pParent /*=NULL*/)
	: CDialog(CombOpt_ModTun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CombOpt_ModTun)
	m_C_CO = dp->pCombOptOP[326];
	m_L_NOx = int(dp->pCombOptOP[177]);
	m_L_Rtem = int(dp->pCombOptOP[200]);
	m_L_Etem = int(dp->pCombOptOP[201]);
	m_L_CO = int(dp->pCombOptOP[175]);
	m_EL_NOx = int(dp->pCombOptOP[197]);  // 累计误差长度
	m_EL_Rtem = int(dp->pCombOptOP[199]);
	m_EL_Etem = int(dp->pCombOptOP[198]);
	m_EL_CO = int(dp->pCombOptOP[197]);  // 一氧化碳
	m_C_NOx = dp->pCombOptOP[308];  // SVM模型参数，这里的CO
	m_C_Rtem = dp->pCombOptOP[320];
	m_C_Etem = dp->pCombOptOP[314];
	m_Delta_CO = dp->pCombOptOP[323];
	m_Delta_Etem = dp->pCombOptOP[311];
	m_Delta_NOx = dp->pCombOptOP[305];
	m_Delta_Rtem = dp->pCombOptOP[317];
	m_PE_CO = dp->pCombOptOP[296];
	m_PE_Etem = dp->pCombOptOP[16];
	m_PE_NOx = dp->pCombOptOP[15];
	m_PE_Rtem = dp->pCombOptOP[17];
	m_SSINC_CO = dp->pCombOptOP[176];
	m_SSINC_Etem = dp->pCombOptOP[204];
	m_SSINC_NOx = dp->pCombOptOP[178];
	m_SSINC_Rtem = dp->pCombOptOP[203];
	m_C_Smax = dp->pCombOptOP[146];
	m_Delta_Smax = dp->pCombOptOP[145];
	m_PE_Smax = dp->pCombOptOP[148];
	//}}AFX_DATA_INIT
}


void CombOpt_ModTun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CombOpt_ModTun)
	DDX_Text(pDX, IDC_EDIT_C_CO, m_C_CO);
	DDX_Text(pDX, IDC_EDIT_L_NOx, m_L_NOx);
	DDX_Text(pDX, IDC_EDIT_L_Rtem, m_L_Rtem);
	DDX_Text(pDX, IDC_EDIT_L_Etem, m_L_Etem);
	DDX_Text(pDX, IDC_EDIT_L_CO, m_L_CO);
	DDX_Text(pDX, IDC_EDIT_EL_NOx, m_EL_NOx);
	DDX_Text(pDX, IDC_EDIT_EL_Rtem, m_EL_Rtem);
	DDX_Text(pDX, IDC_EDIT_EL_Etem, m_EL_Etem);
	DDX_Text(pDX, IDC_EDIT_EL_CO, m_EL_CO);
	DDX_Text(pDX, IDC_EDIT_C_NOx, m_C_NOx);
	DDX_Text(pDX, IDC_EDIT_C_Rtem, m_C_Rtem);
	DDX_Text(pDX, IDC_EDIT_C_Etem, m_C_Etem);
	DDX_Text(pDX, IDC_EDIT_Delta_CO, m_Delta_CO);
	DDX_Text(pDX, IDC_EDIT_Delta_Etem, m_Delta_Etem);
	DDX_Text(pDX, IDC_EDIT_Delta_NOx, m_Delta_NOx);
	DDX_Text(pDX, IDC_EDIT_Delta_Rtem, m_Delta_Rtem);
	DDX_Text(pDX, IDC_EDIT_PE_CO, m_PE_CO);
	DDX_Text(pDX, IDC_EDIT_PE_Etem, m_PE_Etem);
	DDX_Text(pDX, IDC_EDIT_PE_NOx, m_PE_NOx);
	DDX_Text(pDX, IDC_EDIT_PE_Rtem, m_PE_Rtem);
	DDX_Text(pDX, IDC_EDIT_SSINC_CO, m_SSINC_CO);
	DDX_Text(pDX, IDC_EDIT_SSINC_Etem, m_SSINC_Etem);
	DDX_Text(pDX, IDC_EDIT_SSINC_NOx, m_SSINC_NOx);
	DDX_Text(pDX, IDC_EDIT_SSINC_Rtem, m_SSINC_Rtem);
	DDX_Text(pDX, IDC_EDIT_C_Smax, m_C_Smax);
	DDX_Text(pDX, IDC_EDIT_Delta_Smax, m_Delta_Smax);
	DDX_Text(pDX, IDC_EDIT_PE_Smax, m_PE_Smax);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CombOpt_ModTun, CDialog)
	//{{AFX_MSG_MAP(CombOpt_ModTun)
	ON_BN_CLICKED(IDC_SModParam, OnModParam)
	ON_BN_CLICKED(IDC_EModParam, OnExit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CombOpt_ModTun message handlers

void CombOpt_ModTun::OnModParam() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);

	if(MessageBox(_T("确定修改? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		dp->LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+dp->LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
		dp->LogSystem(outLog,_T("修改模型参数..."));

		// 赋值给Op_tag
	    dp->pCombOptOP[177] = m_L_NOx;
		dp->pCombOptOP[200] = m_L_Rtem;
		dp->pCombOptOP[201] = m_L_Etem;
		dp->pCombOptOP[175] = m_L_CO;

		dp->pCombOptOP[197] = m_EL_NOx;
		dp->pCombOptOP[199] = m_EL_Rtem;
		dp->pCombOptOP[198] = m_EL_Etem;
		dp->pCombOptOP[197] = m_EL_CO;   // 累计误差窗口长度

		dp->pCombOptOP[308] = m_C_NOx;  // SVM模型参数 CO 为 Cfh
		dp->pCombOptOP[314] = m_C_Etem;
		dp->pCombOptOP[320] = m_C_Rtem;
		dp->pCombOptOP[326] = m_C_CO;

		dp->pCombOptOP[305] = m_Delta_NOx;
		dp->pCombOptOP[311] = m_Delta_Etem;
		dp->pCombOptOP[317] = m_Delta_Rtem;
		dp->pCombOptOP[323] = m_Delta_CO;

		dp->pCombOptOP[15] = m_PE_NOx;
		dp->pCombOptOP[16] = m_PE_Etem;
		dp->pCombOptOP[17] = m_PE_Rtem;
		dp->pCombOptOP[296] = m_PE_CO;


		dp->pCombOptOP[146] = m_C_Smax;
		dp->pCombOptOP[145] = m_Delta_Smax;
		// theComb.Op_tag[199] = m_EL_Smax;  // 这个值未用到，这里取为Rtem值
		// dp->pCombOptOP[166] = m_L_Smax;
		dp->pCombOptOP[148] = m_PE_Smax;

		dp->pCombOptOP[176] = m_SSINC_CO;
		dp->pCombOptOP[204] = m_SSINC_Etem;
		dp->pCombOptOP[178] = m_SSINC_NOx;
		dp->pCombOptOP[203] = m_SSINC_Rtem;
		//theComb.Op_tag[167] = m_SSINC_Smax;  // 滤波中的变化阈值

		//theComb.Op_tag[329] = m_RateLimit_NOx;
		//theComb.Op_tag[330] = m_RateLimit_Etem;
		//theComb.Op_tag[331] = m_RateLimit_Rtem;
		//theComb.Op_tag[332] = m_RateLimit_CO;

		// 参数存入txt
		theComb.ReSetPara("param//Op.txt");
		// 调函数，保存成txt
		dp->LogSystem(outLog,_T("修改模型参数成功！"));
		outLog.close();
		MessageBox(_T("修改模型参数成功！"),_T("Interface说明："),MB_ICONWARNING);
	}
}

void CombOpt_ModTun::OnExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}
