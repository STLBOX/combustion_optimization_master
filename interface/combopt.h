#if !defined(AFX_XT_H__B083AFAC_AA08_42DF_B4A6_66EC6CE0B859__INCLUDED_)
#define AFX_XT_H__B083AFAC_AA08_42DF_B4A6_66EC6CE0B859__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CombOpt.h : header file


class CombOpt : public CDialog
{

public:
	double a_Cfh;  // »Ò·Éº¬Ì¼ÄâºÏÏµÊý
	double b_Cfh;
	bool m_flag;
	CombOpt(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CombOpt)
	enum { IDD = IDD_CombOpt_DIALOG };
	double	m_Cfh;
	double	m_Eff;
	double	m_Etem;
	double	m_EtemE;
	double	m_EtemP;
	double	m_FgpTemp;
	double	m_Load;
	double	m_MainStemFlow;
	double	m_MainStemPress;
	double	m_MainStemTemp;
	CString	m_COMState;
	CString	m_ControlState;
	CString	m_DCSHbState;
	CString	m_ProcessState;
	CString	m_SimControlState;
	double	m_EtemCUNum;
	double	m_MCO;
	double	m_MO2;
	double	m_MRtem;
	double	m_NOx;
	double	m_NOxE;
	double	m_NOxP;
	int		m_RtemCUNum;
	double	m_RtemE;
	double	m_RtemP;
	double	m_SfjA;
	double	m_SlbTemp;
	double	m_TotalCoal;
	double	m_TotalWind;
	CString	m_ModUpdateState;
	double	m_YfjA;
	double	m_NOxCUNum;
	CString	m_DCSSwitch;
	double	m_CfhB;
	double	m_Cfhsoft;
	double	m_COCUnum;
	double	m_COE;
	double	m_COP;
	double	m_AO2;
	double	m_BO2;
	double	m_SmaxE;
	int		m_SmaxCUnum;
	double	m_SmaxP;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CombOpt)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CombOpt)
	virtual BOOL OnInitDialog();
	afx_msg void OnCombOptExit();
	afx_msg void OnButtonOptParam();
	afx_msg void OnButtonModelParam();
	afx_msg void OnButtonRecordData();
	afx_msg void OnButtonEndRecordData();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowCtrInf();
	afx_msg void OnStartSimControl();
	afx_msg void OnStartSimTrack();
	afx_msg void OnSimDCSControl();
	afx_msg void OnSimDCSTrack();
	afx_msg void OnSaveModelParam();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CombOpt_H__B083AFAC_AA08_42DF_B4A6_66EC6CE0B859__INCLUDED_)
