#if !defined(AFX_COMBOPT_MODTUN_H__8D193ACB_E236_46D2_8914_615ED7D9C9F7__INCLUDED_)
#define AFX_COMBOPT_MODTUN_H__8D193ACB_E236_46D2_8914_615ED7D9C9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CombOpt_ModTun.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CombOpt_ModTun dialog

class CombOpt_ModTun : public CDialog
{
// Construction
public:
	CombOpt_ModTun(CWnd* pParent = NULL);   // standard constructor

	// Dialog Data
	//{{AFX_DATA(CombOpt_ModTun)
	enum { IDD = IDD_CombModParaTun_DIALOG };
	double	m_C_CO;
	int		m_L_NOx;
	int		m_L_Rtem;
	int		m_L_Etem;
	int		m_L_CO;
	int		m_EL_NOx;
	int		m_EL_Rtem;
	int		m_EL_Etem;
	int		m_EL_CO;
	double	m_C_NOx;
	double	m_C_Rtem;
	double	m_C_Etem;
	double	m_Delta_CO;
	double	m_Delta_Etem;
	double	m_Delta_NOx;
	double	m_Delta_Rtem;
	double	m_PE_CO;
	double	m_PE_Etem;
	double	m_PE_NOx;
	double	m_PE_Rtem;
	double	m_SSINC_CO;
	double	m_SSINC_Etem;
	double	m_SSINC_NOx;
	double	m_SSINC_Rtem;
	double	m_C_Smax;
	double	m_Delta_Smax;
	double	m_PE_Smax;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CombOpt_ModTun)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CombOpt_ModTun)
	afx_msg void OnModParam();
	afx_msg void OnExit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COMBOPT_MODTUN_H__8D193ACB_E236_46D2_8914_615ED7D9C9F7__INCLUDED_)
