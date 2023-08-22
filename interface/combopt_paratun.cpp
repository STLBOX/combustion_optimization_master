// ombOpt_ParaTun.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "CombOpt_ParaTun.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"
#include "CON_O2.h"
#include "CON_FUEL.h"
#include "CON_SECONDARY.h"
#include "CON_SOFA.h"
#include "ON_FP.h"
#include "ON_BURNER.h"
//#include "ON_BURNER.h"
//#include "ON_RS.h"
//#include "ON_SOFAANGLE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CInterfaceDlg* dp;
// fix: ȫ�ֱ���
extern ObjCombOpt theComb;
/////////////////////////////////////////////////////////////////////////////
// CombOpt_ParaTun dialog


CombOpt_ParaTun::CombOpt_ParaTun(CWnd* pParent /*=NULL*/)
	: CDialog(CombOpt_ParaTun::IDD, pParent)
{
	//{{AFX_DATA_INIT(CombOpt_ParaTun)
	m_ControlHorizon = int(dp->pCombOptOP[1]);
	m_EffW = dp->pCombOptOP[180];
	m_NOxMax = dp->pCombOptOP[12];
	m_NOxW = dp->pCombOptOP[179];
	m_RtemMax = dp->pCombOptOP[13];
	m_RtemMin = dp->pCombOptOP[14];
	m_RtemW = dp->pCombOptOP[181];
	m_ControlT = int(dp->pCombOptOP[2]);  // ��������
	m_PredHorizon = int(dp->pCombOptOP[0]);
	m_qbias = dp->pCombOptOP[281];
	m_qI = dp->pCombOptOP[299];
	m_FpW = dp->pCombOptOP[214];
	m_FuelW = dp->pCombOptOP[139];
	m_O2W = dp->pCombOptOP[138];
	m_SecW = dp->pCombOptOP[125];
	m_SofaW = dp->pCombOptOP[123];
	m_SmaxW = dp->pCombOptOP[165];
	//}}AFX_DATA_INIT
}


void CombOpt_ParaTun::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	//{{AFX_DATA_MAP(CombOpt_ParaTun)
	DDX_Text(pDX, IDC_EDIT_ControlHorizon, m_ControlHorizon);
	DDX_Text(pDX, IDC_EDIT_EffW, m_EffW);
	DDX_Text(pDX, IDC_EDIT_NOxMax, m_NOxMax);
	DDX_Text(pDX, IDC_EDIT_NOxW, m_NOxW);
	DDX_Text(pDX, IDC_EDIT_RtemMax, m_RtemMax);
	DDX_Text(pDX, IDC_EDIT_RtemMin, m_RtemMin);
	DDX_Text(pDX, IDC_EDIT_RtemW, m_RtemW);
	DDX_Text(pDX, IDC_EDIT_ControlT, m_ControlT);
	DDX_Text(pDX, IDC_EDIT_PredHorizon, m_PredHorizon);
	DDX_Text(pDX, IDC_EDIT_qbias, m_qbias);
	DDX_Text(pDX, IDC_EDIT_qI, m_qI);
	DDX_Text(pDX, IDC_EDIT_FpW, m_FpW);
	DDX_Text(pDX, IDC_EDIT_FuelW, m_FuelW);
	DDX_Text(pDX, IDC_EDIT_O2W, m_O2W);
	DDX_Text(pDX, IDC_EDIT_SecW, m_SecW);
	DDX_Text(pDX, IDC_EDIT_SofaW, m_SofaW);
	DDX_Text(pDX, IDC_EDIT_SmaxW, m_SmaxW);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CombOpt_ParaTun, CDialog)
	//{{AFX_MSG_MAP(CombOpt_ParaTun)
	ON_BN_CLICKED(IDC_EOptParam, OnExit)
	ON_BN_CLICKED(IDC_SOptParam, OnParaTun)
	ON_BN_CLICKED(IDC_xzflq, OnButtonxzflq)
	ON_BN_CLICKED(IDC_burner, OnButtonburner)
    ON_BN_CLICKED(IDC_fuel, OnButtonfuel)
	ON_BN_CLICKED(IDC_sofa, OnButtonsofa)
	ON_BN_CLICKED(IDC_o2, OnButtono2)
	ON_BN_CLICKED(IDC_secondary, OnButtonsecondary)
	ON_BN_CLICKED(IDC_surround, OnButtonsurround)
	ON_BN_CLICKED(IDC_Fp, OnFp)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CombOpt_ParaTun message handlers

void CombOpt_ParaTun::OnExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}

void CombOpt_ParaTun::OnParaTun()  
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);   // ���浽����
	if(MessageBox(_T("ȷ���޸�? "),_T("Interface���棺"),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{

		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		dp->LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+dp->LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
		dp->LogSystem(outLog,_T("�޸��Ż����Ʋ���..."));


		// ��������Tag  ���ݿ�
		dp->pCombOptOP[0] =	m_PredHorizon;
		dp->pCombOptOP[1] = m_ControlHorizon;
		dp->pCombOptOP[2] = m_ControlT;  // ��������

		dp->pCombOptOP[179] = 	m_NOxW;
		dp->pCombOptOP[180] = m_EffW;
		dp->pCombOptOP[181] =  m_RtemW;

		dp->pCombOptOP[281] = m_qbias;
		dp->pCombOptOP[299] = m_qI;

		dp->pCombOptOP[12] = m_NOxMax;
		dp->pCombOptOP[13] = m_RtemMax;
		dp->pCombOptOP[14] = m_RtemMin;

		dp->pCombOptOP[165] = m_SmaxW;  // �ָ�������Ȩֵ
		//theComb.Op_tag[163] = m_SmaxMax;  // �ͷ�����
		//theComb.Op_tag[164] = m_SmaxMin;

		//theComb.Op_tag[160] = m_FangleW; // ͬһ���Ȩֵ��ͬ
		dp->pCombOptOP[214] = m_FpW;
		dp->pCombOptOP[123] = m_SofaW;
		dp->pCombOptOP[124] = m_SofaW;
		for(int i=0;i<=5;i++)
		{
			dp->pCombOptOP[125+i] = m_SecW;
		}
		dp->pCombOptOP[138] = m_O2W ;

		for(i=0;i<=5;i++)
		{
			dp->pCombOptOP[139+i] = m_FuelW;
		}

		// ��������txt
		theComb.ReSetPara("param//Op.txt");

		dp->LogSystem(outLog,_T("�޸Ŀ��Ʋ����ɹ���"));
		outLog.close();

		MessageBox(_T("�޸Ŀ��Ʋ����ɹ���"),_T("Interface˵����"),MB_ICONWARNING);
	}
}

BOOL CombOpt_ParaTun::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if((pMsg->wParam==VK_RETURN)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if((pMsg->wParam==VK_ESCAPE)&&(pMsg->message==WM_KEYDOWN)) 
		return true; 
	if(pMsg->message==WM_RBUTTONDOWN)    //��ֹ�Ҽ�
		return true;	
	return CDialog::PreTranslateMessage(pMsg);
}


void CombOpt_ParaTun::OnButtonfuel()    //��ú��Լ������
{
	// TODO: Add your control notification handler code here
	CON_FUEL theFUEL;
	theFUEL.DoModal();

}


void CombOpt_ParaTun::OnButtonsurround()    //Լ������
{
	// TODO: Add your control notification handler code here
	//		CON_SOFAANGLE theSOFAANGLE;
	//		theSOFAANGLE.DoModal();

}

void CombOpt_ParaTun::OnButtonsecondary()    //Լ������
{
	// TODO: Add your control notification handler code here
	CON_SECONDARY theSECONDARY;
	theSECONDARY.DoModal();

}

void CombOpt_ParaTun::OnButtonsofa()    //Լ������
{
     //	TODO: Add your control notification handler code here
	CON_SOFA theSOFA;
	theSOFA.DoModal();

}

void CombOpt_ParaTun::OnButtono2()    //Լ������
{
	// TODO: Add your control notification handler code here
	CON_O2 theO2;
	theO2.DoModal();

}

void CombOpt_ParaTun::OnButtonxzflq()   //��ת������
{
	// TODO: Add your control notification handler code here
	//		CON_RS theRS;
	//		theRS.DoModal();

}

void CombOpt_ParaTun::OnButtonburner()   //ȼ�����ڽ�
{
	// TODO: Add your control notification handler code here
	// CON_BURNER theBURNER;
	// theBURNER.DoModal();
}

void CombOpt_ParaTun::OnFp() 
{
	// TODO: Add your control notification handler code here
	CON_FP theFp;
	theFp.DoModal();	
}
