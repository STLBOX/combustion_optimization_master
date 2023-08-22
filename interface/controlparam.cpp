// ControlParam.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "InterfaceDlg.h"
#include "ControlParam.h"
#include "ObjCombOpt.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CInterfaceDlg* dp;
extern ObjCombOpt theComb;
/////////////////////////////////////////////////////////////////////////////
// ControlParam dialog


ControlParam::ControlParam(CWnd* pParent /*=NULL*/)
	: CDialog(ControlParam::IDD, pParent)
{
	//{{AFX_DATA_INIT(ControlParam)
	m_OACoal = Round( dp->pCombOptWriteData[2],3 );
	m_OBCoal = Round( dp->pCombOptWriteData[3],3 );
	m_OCCoal = Round( dp->pCombOptWriteData[4],3 );
	m_ODCoal = Round( dp->pCombOptWriteData[5],3 );
	m_OECoal = Round( dp->pCombOptWriteData[6],3 );
	m_OFCoal = Round( dp->pCombOptWriteData[7],3 );

	m_OO2 = Round( dp->pCombOptWriteData[24],3 );
	m_OP1 = Round( dp->pCombOptWriteData[25],3 );  // 一次风压

	m_OBleft = Round( dp->pCombOptWriteData[20],3 );
	m_OBright = Round( dp->pCombOptWriteData[21],3 );
	m_OFleft = Round( dp->pCombOptWriteData[22],3 );
	m_OFright = Round( dp->pCombOptWriteData[23],3 );

	m_OsecAA = Round( dp->pCombOptWriteData[8],3 );  // A
	m_OsecAB = Round( dp->pCombOptWriteData[9],3 );  // A
	m_OsecFA = Round( dp->pCombOptWriteData[12],3 );  // F
	m_OsecFB = Round( dp->pCombOptWriteData[13],3 );  // F
	m_OsecEA = Round( dp->pCombOptWriteData[10],3 );  // E
	m_OsecEB = Round( dp->pCombOptWriteData[11],3 );  // E
	m_OsecBA = Round( dp->pCombOptWriteData[14],3 );
	m_OsecBB = Round( dp->pCombOptWriteData[15],3 );
	m_OsecCA = Round( dp->pCombOptWriteData[16],3 );
	m_OsecCB = Round( dp->pCombOptWriteData[17],3 );
	m_OsecDA = Round( dp->pCombOptWriteData[18],3 );
	m_OsecDB = Round( dp->pCombOptWriteData[19],3 );

	m_RACoal = Round( dp->pCombOptReadData[64],3 );  // 给煤机控制指令 f(x)+bias
	m_RBCoal = Round( dp->pCombOptReadData[65],3 );
	m_RCCoal = Round( dp->pCombOptReadData[66],3 );
	m_RDCoal = Round( dp->pCombOptReadData[67],3 );
	m_RECoal = Round( dp->pCombOptReadData[68],3 );
	m_RFCoal = Round( dp->pCombOptReadData[69],3 );

	m_RO2 = Round( dp->pCombOptReadData[62],3 );
	m_RP1 = Round( dp->pCombOptReadData[7],3 );

	m_RSecAA = Round( dp->pCombOptReadData[23],3 );
	m_RSecAB = Round( dp->pCombOptReadData[24],3 );
	m_RSecFA = Round( dp->pCombOptReadData[27],3 );  // F
	m_RSecFB = Round( dp->pCombOptReadData[28],3 );  // F
	m_RSecEA = Round( dp->pCombOptReadData[25],3 );  // E
	m_RSecEB = Round( dp->pCombOptReadData[26],3 );  // E
	m_RSecBA = Round( dp->pCombOptReadData[29],3 );
	m_RSecBB = Round( dp->pCombOptReadData[30],3 );
	m_RSecCA = Round( dp->pCombOptReadData[31],3 );
	m_RSecCB = Round( dp->pCombOptReadData[32],3 );
	m_RSecDA = Round( dp->pCombOptReadData[33],3 );
	m_RSecDB = Round( dp->pCombOptReadData[34],3 );

	m_RBleft = Round( dp->pCombOptReadData[35],3 );
	m_RBright = Round( dp->pCombOptReadData[36],3 );
	m_RFleft = Round( dp->pCombOptReadData[37],3 );
	m_RFright = Round( dp->pCombOptReadData[38],3 );


	m_Oburn1 = 0.0;
	m_Oburn2 = 0.0;
	m_Oburn3 = 0.0;
	m_Rburn1 = 0.0;
	m_Rburn2 = 0.0;
	m_Rburn3 = 0.0;
	//}}AFX_DATA_INIT
}


void ControlParam::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ControlParam)
	DDX_Text(pDX, IDC_EDIT_OACoal, m_OACoal);
	DDX_Text(pDX, IDC_EDIT_OBCoal, m_OBCoal);
	DDX_Text(pDX, IDC_EDIT_OCCoal, m_OCCoal);
	DDX_Text(pDX, IDC_EDIT_ODCoal, m_ODCoal);
	DDX_Text(pDX, IDC_EDIT_OECoal, m_OECoal);
	DDX_Text(pDX, IDC_EDIT_OFCoal, m_OFCoal);
	DDX_Text(pDX, IDC_EDIT_OO2, m_OO2);
	DDX_Text(pDX, IDC_EDIT_RCCoal, m_RCCoal);
	DDX_Text(pDX, IDC_EDIT_RDCoal, m_RDCoal);
	DDX_Text(pDX, IDC_EDIT_RECoal, m_RECoal);
	DDX_Text(pDX, IDC_EDIT_RFCoal, m_RFCoal);
	DDX_Text(pDX, IDC_EDIT_RO2, m_RO2);
	DDX_Text(pDX, IDC_EDIT_OP1, m_OP1);
	DDX_Text(pDX, IDC_EDIT_RP1, m_RP1);
	DDX_Text(pDX, IDC_EDIT_OBleft, m_OBleft);
	DDX_Text(pDX, IDC_EDIT_OBright, m_OBright);
	DDX_Text(pDX, IDC_EDIT_OFleft, m_OFleft);
	DDX_Text(pDX, IDC_EDIT_OFright, m_OFright);
	DDX_Text(pDX, IDC_EDIT_OSecAA, m_OsecAA);
	DDX_Text(pDX, IDC_EDIT_OSecAB, m_OsecAB);
	DDX_Text(pDX, IDC_EDIT_OSecBA, m_OsecBA);
	DDX_Text(pDX, IDC_EDIT_OSecBB, m_OsecBB);
	DDX_Text(pDX, IDC_EDIT_OSecCA, m_OsecCA);
	DDX_Text(pDX, IDC_EDIT_OSecCB, m_OsecCB);
	DDX_Text(pDX, IDC_EDIT_OSecDA, m_OsecDA);
	DDX_Text(pDX, IDC_EDIT_OSecDB, m_OsecDB);
	DDX_Text(pDX, IDC_EDIT_OSecEA, m_OsecEA);
	DDX_Text(pDX, IDC_EDIT_OSecEB, m_OsecEB);
	DDX_Text(pDX, IDC_EDIT_OSecFA, m_OsecFA);
	DDX_Text(pDX, IDC_EDIT_OSecFB, m_OsecFB);
	DDX_Text(pDX, IDC_EDIT_RACoal, m_RACoal);
	DDX_Text(pDX, IDC_EDIT_RBCoal, m_RBCoal);
	DDX_Text(pDX, IDC_EDIT_RBleft, m_RBleft);
	DDX_Text(pDX, IDC_EDIT_RBright, m_RBright);
	DDX_Text(pDX, IDC_EDIT_RFleft, m_RFleft);
	DDX_Text(pDX, IDC_EDIT_RFright, m_RFright);
	DDX_Text(pDX, IDC_EDIT_RSecAA, m_RSecAA);
	DDX_Text(pDX, IDC_EDIT_RSecAB, m_RSecAB);
	DDX_Text(pDX, IDC_EDIT_RSecBA, m_RSecBA);
	DDX_Text(pDX, IDC_EDIT_RSecBB, m_RSecBB);
	DDX_Text(pDX, IDC_EDIT_RSecCA, m_RSecCA);
	DDX_Text(pDX, IDC_EDIT_RSecCB, m_RSecCB);
	DDX_Text(pDX, IDC_EDIT_RSecDA, m_RSecDA);
	DDX_Text(pDX, IDC_EDIT_RSecDB, m_RSecDB);
	DDX_Text(pDX, IDC_EDIT_RSecEA, m_RSecEA);
	DDX_Text(pDX, IDC_EDIT_RSecEB, m_RSecEB);
	DDX_Text(pDX, IDC_EDIT_RSecFA, m_RSecFA);
	DDX_Text(pDX, IDC_EDIT_RSecFB, m_RSecFB);
	DDX_Text(pDX, IDC_EDIT_Oburn1, m_Oburn1);
	DDX_Text(pDX, IDC_EDIT_Oburn2, m_Oburn2);
	DDX_Text(pDX, IDC_EDIT_Oburn3, m_Oburn3);
	DDX_Text(pDX, IDC_EDIT_Rburn1, m_Rburn1);
	DDX_Text(pDX, IDC_EDIT_Rburn2, m_Rburn2);
	DDX_Text(pDX, IDC_EDIT_Rburn3, m_Rburn3);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ControlParam, CDialog)
	//{{AFX_MSG_MAP(ControlParam)
	ON_WM_CLOSE()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_Exit, OnExit)
	ON_BN_CLICKED(IDC_ClearOptInc, OnClearOptInc)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ControlParam message handlers


BOOL ControlParam::OnInitDialog() 
{
	CDialog::OnInitDialog();
	ReSetOptInc = FALSE;
	ReSetOptIncO2 = FALSE;
	ReSetOptIncSec = FALSE;
	ReSetOptIncSofa = FALSE;
	ReSetOptIncCoal = FALSE;
	SetTimer(1,10000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


BOOL ControlParam::PreTranslateMessage(MSG* pMsg) 
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

void ControlParam::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}

void ControlParam::OnTimer(UINT nIDEvent) 
{
	switch (nIDEvent)
	{
		case 1:
			{

				// TODO: Add your message handler 
				while(((int)dp->pCombOptWriteData[0] !=0))
				{
					Sleep(10);
				}
				dp->pCombOptWriteData[0] = 1;  // 上锁
				m_OACoal = Round( dp->pCombOptWriteData[2],3 );
				m_OBCoal = Round( dp->pCombOptWriteData[3],3 );
				m_OCCoal = Round( dp->pCombOptWriteData[4],3 );
				m_ODCoal = Round( dp->pCombOptWriteData[5],3 );
				m_OECoal = Round( dp->pCombOptWriteData[6],3 );
				m_OFCoal = Round( dp->pCombOptWriteData[7],3 );

				m_OsecAA = Round( dp->pCombOptWriteData[8],3 );  // A
				m_OsecAB = Round( dp->pCombOptWriteData[9],3 );  // A
				m_OsecFA = Round( dp->pCombOptWriteData[12],3 );  // F
				m_OsecFB = Round( dp->pCombOptWriteData[13],3 );  // F
				m_OsecEA = Round( dp->pCombOptWriteData[10],3 );  // E
				m_OsecEB = Round( dp->pCombOptWriteData[11],3 );  // E
				m_OsecBA = Round( dp->pCombOptWriteData[14],3 );
				m_OsecBB = Round( dp->pCombOptWriteData[15],3 );
				m_OsecCA = Round( dp->pCombOptWriteData[16],3 );
				m_OsecCB = Round( dp->pCombOptWriteData[17],3 );
				m_OsecDA = Round( dp->pCombOptWriteData[18],3 );
				m_OsecDB = Round( dp->pCombOptWriteData[19],3 );

				m_OO2 = Round( dp->pCombOptWriteData[24],3 );
				m_OP1 = Round( dp->pCombOptWriteData[25],3 );  // 一次风压

				m_OBleft = Round( dp->pCombOptWriteData[20],3 );
				m_OBright = Round( dp->pCombOptWriteData[21],3 );
				m_OFleft = Round( dp->pCombOptWriteData[22],3 );
				m_OFright = Round( dp->pCombOptWriteData[23],3 );
				dp->pCombOptWriteData[0] = 0;  // 解锁


				while((dp->pCombOptReadData[0] !=0))
				{
					Sleep(10);
				}
				dp->pCombOptReadData[0] = 1;  // 上锁
				m_RACoal = Round( dp->pCombOptReadData[64],3 );  // 给煤机控制指令 f(x)+bias
				m_RBCoal = Round( dp->pCombOptReadData[65],3 );
				m_RCCoal = Round( dp->pCombOptReadData[66],3 );
				m_RDCoal = Round( dp->pCombOptReadData[67],3 );
				m_RECoal = Round( dp->pCombOptReadData[68],3 );
				m_RFCoal = Round( dp->pCombOptReadData[69],3 );

				m_RO2 = Round( dp->pCombOptReadData[62],3 );
				m_RP1 = Round( dp->pCombOptReadData[7],3 );

				m_RSecAA = Round( dp->pCombOptReadData[23],3 );
				m_RSecAB = Round( dp->pCombOptReadData[24],3 );
				m_RSecFA = Round( dp->pCombOptReadData[27],3 );  // F
				m_RSecFB = Round( dp->pCombOptReadData[28],3 );  // F
				m_RSecEA = Round( dp->pCombOptReadData[25],3 );  // E
				m_RSecEB = Round( dp->pCombOptReadData[26],3 );  // E
				m_RSecBA = Round( dp->pCombOptReadData[29],3 );
				m_RSecBB = Round( dp->pCombOptReadData[30],3 );
				m_RSecCA = Round( dp->pCombOptReadData[31],3 );
				m_RSecCB = Round( dp->pCombOptReadData[32],3 );
				m_RSecDA = Round( dp->pCombOptReadData[33],3 );
				m_RSecDB = Round( dp->pCombOptReadData[34],3 );
				m_RBleft = Round( dp->pCombOptReadData[35],3 );
				m_RBright = Round( dp->pCombOptReadData[36],3 );
				m_RFleft = Round( dp->pCombOptReadData[37],3 );
				m_RFright = Round( dp->pCombOptReadData[38],3 );
				dp->pCombOptReadData[0] = 0;  // 解锁

				UpdateData(FALSE);
				break;
			}
	}

	CDialog::OnTimer(nIDEvent);
}

void ControlParam::OnExit() 
{
	// TODO: Add your control notification handler code here
	if (ReSetOptInc)
	{
		MessageBox(_T("请等待重置完成！"),_T("Interface警告："),MB_ICONWARNING);
	}
	else
	{
		CDialog::OnCancel();
		SendMessage(WM_CLOSE);
	}
}

void ControlParam::OnClearOptInc() 
{
	// TODO: Add your control notification handler code here
	if (ReSetOptInc==TRUE)
	{
		MessageBox(_T("正在重置优化增量！"),_T("Interface警告："),MB_ICONWARNING);
	}
	else if (MessageBox(_T("确定重置优化增量? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		//ReSetOptInc=TRUE;
	}
}
