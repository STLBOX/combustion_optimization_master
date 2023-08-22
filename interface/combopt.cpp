// CombOpt.cpp : implementation file
//

#include "stdafx.h"
#include "Interface.h"
#include "InterfaceDlg.h"
#include "ObjCombOpt.h"
#include "CombOpt.h"
#include "CombOpt_ModTun.h"
#include "CombOpt_ParaTun.h"
#include "ControlParam.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern CInterfaceDlg* dp;
extern ObjCombOpt theComb;

/////////////////////////////////////////////////////////////////////////////
// CombOpt dialog


CombOpt::CombOpt(CWnd* pParent /*=NULL*/)
	: CDialog(CombOpt::IDD, pParent)
{
	//{{AFX_DATA_INIT(CombOpt)
	m_Cfh = Round( dp->pCombOptReadData[82],3 );  // Cfh A
	m_Eff = Round( dp->pCombOptWriteData[26],2 );  // 锅炉效率
	m_Etem = Round( (dp->pCombOptReadData[56]+dp->pCombOptReadData[57])/2,3 );  // Etem
	m_EtemE = Round( dp->pCombOptOP[355],3 );
	m_EtemP = Round( dp->pCombOptOP[349],3 );
	m_FgpTemp = 0;  // 分隔屏最高温度，采用主蒸汽温度替代
	m_Load = Round( dp->pCombOptReadData[2],3 );
	m_MainStemFlow = Round( dp->pCombOptReadData[6],3 );  // 主蒸汽流量
	m_MainStemPress = Round( dp->pCombOptReadData[75],3 );  // 主蒸汽压力
	m_MainStemTemp = Round( dp->pCombOptReadData[70],3 );  // 主蒸汽温度
	m_COMState = _T("");
	m_ControlState = _T("");
	m_DCSHbState = _T("");
	m_ProcessState = _T("");
	m_SimControlState = _T("");
	m_EtemCUNum = int(dp->pCombOptOP[352]);
	m_MCO = Round( dp->pCombOptReadData[58],3 );  // CO
	m_MO2 = Round( dp->pCombOptReadData[55],3 );  // 省煤器出口O2
	m_MRtem = Round( (dp->pCombOptReadData[73]+dp->pCombOptReadData[74])/2 ,3 );  // Rtem
	m_NOx = Round( dp->pCombOptReadData[4],3 );  // NOx
	m_NOxE = Round( dp->pCombOptOP[354],3 );
	m_NOxP = Round( dp->pCombOptOP[348],3 );
	m_RtemCUNum = int(dp->pCombOptOP[353]);
	m_RtemE = Round( dp->pCombOptOP[356],3 );
	m_RtemP = Round( dp->pCombOptOP[350],3 );
	m_SfjA = Round( dp->pCombOptReadData[60],3 );  // 送风机电流
	m_SlbTemp = 0;  // 水冷壁
	m_TotalCoal = Round( dp->pCombOptReadData[3],3 );
	m_ModUpdateState = _T("");
	m_YfjA = Round( dp->pCombOptReadData[61],3 );  // 引风机电流
	m_NOxCUNum = int(dp->pCombOptOP[351]);
	m_DCSSwitch = _T("");
	m_CfhB = Round( dp->pCombOptReadData[83],3 );  // Cfh B
	m_Cfhsoft = Round( Max( (dp->pCombOptOP[367])*dp->pCombOptOP[216] + dp->pCombOptOP[215], 0.3), 3);  // CO
	m_COCUnum = int(dp->pCombOptOP[365]);
	m_COE = Round( dp->pCombOptOP[366],3 );
	m_COP = Round( dp->pCombOptOP[364],3 );

	m_AO2 = Round( dp->pCombOptReadData[97],3 );
	m_BO2 = Round( dp->pCombOptReadData[98],3 );

	m_SmaxE = Round( dp->pCombOptOP[370],3 );
	m_SmaxCUnum = int(dp->pCombOptOP[369]);
	m_SmaxP = Round( dp->pCombOptOP[368],3 );
	//}}AFX_DATA_INIT
}


void CombOpt::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CombOpt)
	DDX_Text(pDX, IDC_EDIT_Cfh, m_Cfh);
	DDX_Text(pDX, IDC_EDIT_Eff, m_Eff);
	DDX_Text(pDX, IDC_EDIT_Etem, m_Etem);
	DDX_Text(pDX, IDC_EDIT_EtemE, m_EtemE);
	DDX_Text(pDX, IDC_EDIT_EtemP, m_EtemP);
	DDX_Text(pDX, IDC_EDIT_FgpTemp, m_FgpTemp);
	DDX_Text(pDX, IDC_EDIT_Load, m_Load);
	DDX_Text(pDX, IDC_EDIT_MainSteamFlow, m_MainStemFlow);
	DDX_Text(pDX, IDC_EDIT_MainSteamPress, m_MainStemPress);
	DDX_Text(pDX, IDC_EDIT_MainSteamTemp, m_MainStemTemp);
	DDX_Text(pDX, IDC_EDIT_COMState, m_COMState);
	DDX_Text(pDX, IDC_EDIT_ControlState, m_ControlState);
	DDX_Text(pDX, IDC_EDIT_DCSHbState, m_DCSHbState);
	DDX_Text(pDX, IDC_EDIT_ProcessState, m_ProcessState);
	DDX_Text(pDX, IDC_EDIT_SimControlState, m_SimControlState);
	DDX_Text(pDX, IDC_EDIT_EtemCUnum, m_EtemCUNum);
	DDX_Text(pDX, IDC_EDIT_MCO, m_MCO);
	DDX_Text(pDX, IDC_EDIT_MO2, m_MO2);
	DDX_Text(pDX, IDC_EDIT_MRtem, m_MRtem);
	DDX_Text(pDX, IDC_EDIT_NOx, m_NOx);
	DDX_Text(pDX, IDC_EDIT_NOxE, m_NOxE);
	DDX_Text(pDX, IDC_EDIT_NOxP, m_NOxP);
	DDX_Text(pDX, IDC_EDIT_RtemCUnum, m_RtemCUNum);
	DDX_Text(pDX, IDC_EDIT_RtemE, m_RtemE);
	DDX_Text(pDX, IDC_EDIT_RtemP, m_RtemP);
	DDX_Text(pDX, IDC_EDIT_SfjA, m_SfjA);
	DDX_Text(pDX, IDC_EDIT_SlbTemp, m_SlbTemp);
	DDX_Text(pDX, IDC_EDIT_TotalCoal, m_TotalCoal);
	DDX_Text(pDX, IDC_EDIT_ModUpdateState, m_ModUpdateState);
	DDX_Text(pDX, IDC_EDIT_YfjA, m_YfjA);
	DDX_Text(pDX, IDC_EDIT_NOxCUnum, m_NOxCUNum);
	DDX_Text(pDX, IDC_EDIT_DCSSwitch, m_DCSSwitch);
	DDX_Text(pDX, IDC_EDIT_CfhB, m_CfhB);
	DDX_Text(pDX, IDC_EDIT_Cfhsoft, m_Cfhsoft);
	DDX_Text(pDX, IDC_EDIT_COCUnum, m_COCUnum);
	DDX_Text(pDX, IDC_EDIT_COE, m_COE);
	DDX_Text(pDX, IDC_EDIT_COP, m_COP);
	DDX_Text(pDX, IDC_EDIT_AO2, m_AO2);
	DDX_Text(pDX, IDC_EDIT_BO2, m_BO2);
	DDX_Text(pDX, IDC_EDIT_SmaxE, m_SmaxE);
	DDX_Text(pDX, IDC_EDIT_SmaxCUnum, m_SmaxCUnum);
	DDX_Text(pDX, IDC_EDIT_SmaxP, m_SmaxP);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CombOpt, CDialog)    /////            /////////           //////////      ///////////                         /
	//{{AFX_MSG_MAP(CombOpt)
	ON_BN_CLICKED(IDC_Exit, OnCombOptExit)
	ON_BN_CLICKED(IDC_ModOptParam, OnButtonOptParam)
	ON_BN_CLICKED(IDC_ModModelParam, OnButtonModelParam)
	ON_BN_CLICKED(IDC_StartRecordData, OnButtonRecordData)
	ON_BN_CLICKED(IDC_EndRecordData, OnButtonEndRecordData)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ShowCtrInf, OnShowCtrInf)
	ON_BN_CLICKED(IDC_StartSimControl, OnStartSimControl)
	ON_BN_CLICKED(IDC_StartSimTrack, OnStartSimTrack)
//	ON_BN_CLICKED(IDC_SimDCSControl, OnSimDCSControl)
//	ON_BN_CLICKED(IDC_SimDCSTrack, OnSimDCSTrack)
	ON_BN_CLICKED(IDC_SaveModelParam, OnSaveModelParam)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CombOpt message handlers


void CombOpt::OnCombOptExit() 
{
	// TODO: Add your control notification handler code here
	SendMessage(WM_CLOSE);
}

void CombOpt::OnButtonOptParam()
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
			CombOpt_ParaTun theCombOpt_ParaTun;
			theCombOpt_ParaTun.DoModal();
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}

}

void CombOpt::OnButtonModelParam() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
			CombOpt_ModTun theCombOptOP;
			theCombOptOP.DoModal();
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}

}


BOOL CombOpt::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_flag=false;
	a_Cfh = dp->pCombOptOP[216];
	b_Cfh = dp->pCombOptOP[215];

	// TODO: Add extra initialization here
	SetTimer(1,2000,NULL);
	return false;  // return TRUE unless you set the focus to a control	       
}

void CombOpt::OnTimer(UINT nIDEvent) 
{
	if(dp->bAllStart)
	{
		// 系统状态
		// Comb进程状态
		if (int(dp->pCombOptOP[358])>=1)
			m_ProcessState = _T("正常");
		else if(int(dp->pCombOptOP[358])==-1)
			m_ProcessState = _T("错误");
		else
			m_ProcessState = _T("");
			
	    // 模型状态
		if (int(dp->pCombOptOP[359])==1)
			m_ControlState = _T("控制");
		else if(int(dp->pCombOptOP[359])==2)
			m_ControlState = _T("跟踪");
		else
			m_ControlState = _T("");

		// DCS心跳
		if (int(dp->pCombOptReadData[237])==0)
			m_DCSHbState = _T("正常");
		else
			m_DCSHbState = _T("错误");

		// COM
		if (int(dp->pCombOptOP[357])>=1)
			m_COMState = _T("正常");
		else 
			m_COMState = _T("错误");

		// 模拟投入仿真投入
		if (int(dp->pCombOptOP[292])==0)
			m_SimControlState  = _T("未投入");
		else
			m_SimControlState  = _T("投入");

		// 寻优结果
		if (int(dp->pCombOptOP[360])==1)
			m_ModUpdateState = _T("优化解");
		else if (int(dp->pCombOptOP[360])==-1)
			m_ModUpdateState = _T("无解");
		else 
			m_ModUpdateState = _T("");

		
		// DCS开关
		if (int(dp->pCombOptReadData[200])==1)
			m_DCSSwitch = _T("投入");
		else
			m_DCSSwitch = _T("切除");


		while((dp->pCombOptReadData[0] !=0))
		{
			Sleep(10);
		}
		dp->pCombOptReadData[0] = 1;  // 上锁
		// 状态参数
		m_Cfh = Round( dp->pCombOptReadData[82],3 );
		m_CfhB = Round( dp->pCombOptReadData[83],3 );
		m_Eff = Round( dp->pCombOptWriteData[26],2 );
		m_Etem = Round( (dp->pCombOptReadData[56]+dp->pCombOptReadData[57])/2,3 );
	    m_FgpTemp = 0;   // 分隔屏
     	m_Load = Round( dp->pCombOptReadData[2],3 );
		m_MainStemFlow = Round( dp->pCombOptReadData[56],3 );
		m_MainStemPress = Round( dp->pCombOptReadData[75],3 );
		m_MainStemTemp = Round( dp->pCombOptReadData[70],3);

		m_MCO = Round( dp->pCombOptReadData[58],3 );
		m_MO2 = Round( dp->pCombOptReadData[55],3 );  // 省煤器出口
		m_NOx = Round( dp->pCombOptReadData[4],3 );

		m_MRtem = Round( (dp->pCombOptReadData[73]+dp->pCombOptReadData[74])/2 ,3 );
		m_SfjA = Round( dp->pCombOptReadData[60],3 );  // 送风机电流
		m_YfjA = Round( dp->pCombOptReadData[61],3 );  // 引风机电流
		m_SlbTemp = 0;  // 水冷壁
		m_TotalCoal = Round( dp->pCombOptReadData[3],3 );
		dp->pCombOptReadData[0] = 0;  // 解锁


		m_NOxP = Round( dp->pCombOptOP[348],3 );
		m_NOxCUNum = int(dp->pCombOptOP[351]);
		m_NOxE = Round( dp->pCombOptOP[354],3 );

		m_EtemP = Round( dp->pCombOptOP[349],3 );
		m_EtemCUNum = int(dp->pCombOptOP[352]);
		m_EtemP = Round( dp->pCombOptOP[349],3 );

		m_RtemCUNum = int(dp->pCombOptOP[353]);
		m_RtemE = Round( dp->pCombOptOP[356],3 );
		m_RtemP = Round( dp->pCombOptOP[350],3 );

		m_COCUnum = int(dp->pCombOptOP[365]);
		m_COE = Round( dp->pCombOptOP[366],3 );
		m_COP = Round( dp->pCombOptOP[364],3 );

		m_SmaxE = Round( dp->pCombOptOP[370],3 );
		m_SmaxCUnum = int(dp->pCombOptOP[369]);
		m_SmaxP = Round( dp->pCombOptOP[368],3 );

		m_AO2 = Round( dp->pCombOptReadData[97],3 );
		m_BO2 = Round( dp->pCombOptReadData[98],3 );

		m_Cfhsoft = Round( Max( (dp->pCombOptOP[367])*a_Cfh + b_Cfh, 0.3), 3);

//	    m_MODSolveTime = Round( double(theComb.Op_tag[204])/1000,3 );
//	    m_ModUpdateTime = Round( double(theComb.Op_tag[203])/1000,3 );

		UpdateData(FALSE);
	}
	CDialog::OnTimer(nIDEvent);
}

BOOL CombOpt::PreTranslateMessage(MSG* pMsg) 
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


void CombOpt::OnButtonRecordData() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if (int(dp->pCombOptOP[362])==1)
		{
			MessageBox(_T("已开始记录运行数据！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else if (MessageBox(_T("确定记录数据? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
				dp->pCombOptOP[362] = 1;
		}
	}
}

void CombOpt::OnButtonEndRecordData() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if (int(dp->pCombOptOP[362])==0)
		{
			MessageBox(_T("已终止记录运行数据！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else if (MessageBox(_T("确定终止记录数据? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
				dp->pCombOptOP[362] = 0;
		}
	}
}

void CombOpt::OnShowCtrInf() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		ControlParam theControlParam;
		theControlParam.DoModal();
	} 
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
	
}

void CombOpt::OnStartSimControl() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if (int(dp->pCombOptReadData[200])==1)
		{
			MessageBox(_T("DCS已投入！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else
		{
			if(int(dp->pCombOptOP[292])==1)
			{
				MessageBox(_T("模拟投入已开启！"),_T("Interface警告："),MB_ICONWARNING);
			}
			else if (MessageBox(_T("确定修改? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				dp->pCombOptOP[292] = 1;
			}
		}
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
	
}

void CombOpt::OnStartSimTrack() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if(int(dp->pCombOptOP[292])==0)
		{
			MessageBox(_T("模拟投入已关闭！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else if (MessageBox(_T("确定修改? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			dp->pCombOptOP[292] = 0;
		}
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
	
}

void CombOpt::OnSimDCSControl() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if (int(dp->pCombOptOP[292])==1)    // 关闭模拟投运
		{
			MessageBox(_T("请关闭模拟投入！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else
		{
			if(int(dp->pCombOptReadData[200])==1)
			{
				MessageBox(_T("DCS已投入！"),_T("Interface警告："),MB_ICONWARNING);
			}
			else if (MessageBox(_T("确定模拟DCS投入? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
			{
				dp->pCombOptReadData[200] = 1;
			}
		}
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
}

void CombOpt::OnSimDCSTrack() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
		if(int(dp->pCombOptReadData[200])==0)
		{
			MessageBox(_T("DCS已切出！"),_T("Interface警告："),MB_ICONWARNING);
		}
		else if (MessageBox(_T("确定模拟DCS切出? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			dp->pCombOptReadData[200] = 0;
		}
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
}

void CombOpt::OnSaveModelParam() 
{
	// TODO: Add your control notification handler code here
	if(dp->bAllStart)
	{
	    if (MessageBox(_T("确定覆盖模型数据? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{
			dp->pCombOptOP[361] = 1;
		}
	}
	else
	{
		MessageBox(_T("控制程序未启动！"),_T("Interface警告："),MB_ICONWARNING);
	}
}

void CombOpt::OnClose() 
{
	// TODO: Add your message handler code here and/or call default
	KillTimer(1);
	CDialog::OnClose();
}
