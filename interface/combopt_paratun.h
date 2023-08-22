#if !defined(AFX_COMBOPT_PARATUN_H__F5FEF1C2_52BD_4AE0_BD3E_6722EB68DDCF__INCLUDED_)
#define AFX_COMBOPT_PARATUN_H__F5FEF1C2_52BD_4AE0_BD3E_6722EB68DDCF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ombOpt_ParaTun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CombOpt_ParaTun dialog

class CombOpt_ParaTun : public CDialog
{
// Construction
public:
	CombOpt_ParaTun(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CombOpt_ParaTun)
	enum { IDD = IDD_CombOptParaTun_DIALOG };
	int		m_ControlHorizon;
	double	m_EffW;
	double	m_NOxMax;
	double	m_NOxW;
	double	m_RtemMax;
	double	m_RtemMin;
	double	m_RtemW;
	int		m_ControlT;
	int		m_PredHorizon;
	double	m_qbias;
	double	m_qI;
	double	m_FpW;
	double	m_FuelW;
	double	m_O2W;
	double	m_SecW;
	double	m_SofaW;
	double	m_SmaxW;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CombOpt_ParaTun)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CombOpt_ParaTun)
	afx_msg void OnExit();  
	afx_msg void OnParaTun();
	afx_msg void OnButtonxzflq();
	afx_msg void OnButtonburner();
	afx_msg void OnButtonfuel();
	afx_msg void OnButtonsofa();
	afx_msg void OnButtono2();
	afx_msg void OnButtonsecondary();
	afx_msg void OnButtonsurround();
	afx_msg void OnFp();
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OMBOPT_PARATUN_H__F5FEF1C2_52BD_4AE0_BD3E_6722EB68DDCF__INCLUDED_)
