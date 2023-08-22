#if !defined(AFX_ON_SOFA_H__BF81D730_2FF1_4A43_AA9A_00F0489D86C6__INCLUDED_)
#define AFX_ON_SOFA_H__BF81D730_2FF1_4A43_AA9A_00F0489D86C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_SOFA.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_SOFA dialog

class CON_SOFA : public CDialog
{
// Construction
public:
	CON_SOFA(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_SOFA)
	enum { IDD = IDD_ConstrSofa };
	double	m_CombOpt_dmax_sofa1;
	double	m_CombOpt_dmax_sofa2;
	double	m_CombOpt_dmax_sofa3;
	double	m_CombOpt_dmax_sofa4;
	double	m_CombOpt_dmax_sofa5;
	double	m_CombOpt_dmax_sofa6;
	double	m_CombOpt_dmax_sofa7;
	double	m_CombOpt_dmin_sofa1;
	double	m_CombOpt_dmin_sofa2;
	double	m_CombOpt_dmin_sofa3;
	double	m_CombOpt_dmin_sofa4;
	double	m_CombOpt_dmin_sofa5;
	double	m_CombOpt_dmin_sofa6;
	double	m_CombOpt_dmin_sofa7;
	double	m_CombOpt_downLimit_sofa1;
	double	m_CombOpt_downLimit_sofa2;
	double	m_CombOpt_downLimit_sofa3;
	double	m_CombOpt_downLimit_sofa4;
	double	m_CombOpt_downLimit_sofa5;
	double	m_CombOpt_downLimit_sofa6;
	double	m_CombOpt_downLimit_sofa7;
	double	m_CombOpt_dumax_sofa1;
	double	m_CombOpt_dumax_sofa2;
	double	m_CombOpt_dumax_sofa3;
	double	m_CombOpt_dumax_sofa4;
	double	m_CombOpt_dumax_sofa5;
	double	m_CombOpt_dumax_sofa6;
	double	m_CombOpt_dumax_sofa7;
	double	m_CombOpt_dumin_sofa1;
	double	m_CombOpt_dumin_sofa2;
	double	m_CombOpt_dumin_sofa3;
	double	m_CombOpt_dumin_sofa4;
	double	m_CombOpt_dumin_sofa5;
	double	m_CombOpt_dumin_sofa6;
	double	m_CombOpt_dumin_sofa7;
	double	m_CombOpt_upLimit_sofa1;
	double	m_CombOpt_upLimit_sofa2;
	double	m_CombOpt_upLimit_sofa3;
	double	m_CombOpt_upLimit_sofa4;
	double	m_CombOpt_upLimit_sofa5;
	double	m_CombOpt_upLimit_sofa6;
	double	m_CombOpt_upLimit_sofa7;
	double	m_CombOptInt_upLimit_sofa123;
	double	m_CombOptInt_upLimit_sofa456;
	double	m_CombOptInt_downLimit_sofa123;
	double	m_CombOptInt_downLimit_sofa456;
	double	m_CombOptInt_dumax_sofa123;
	double	m_CombOptInt_dumax_sofa456;
	double	m_CombOptInt_dumin_sofa123;
	double	m_CombOptInt_dumin_sofa456;
	double	m_CombOptInt_suLimit_sofa123;
	double	m_CombOptInt_suLimit_sofa456;
	double	m_DzSofa123;
	double	m_DzSofa456;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_SOFA)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_SOFA)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_SOFA_H__BF81D730_2FF1_4A43_AA9A_00F0489D86C6__INCLUDED_)
