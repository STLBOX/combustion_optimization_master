#if !defined(AFX_ON_FP_H__7538FB77_346E_43E6_BFE1_94FEF8FD0F2D__INCLUDED_)
#define AFX_ON_FP_H__7538FB77_346E_43E6_BFE1_94FEF8FD0F2D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_FP.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_FP dialog

class CON_FP : public CDialog
{
// Construction
public:
	CON_FP(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_FP)
	enum { IDD = IDD_ConstrFp };
	double	m_downlimit_Fp;
	double	m_dumax_Fp;
	double	m_dumin_Fp;
	double	m_DzFp;
	double	m_rt_Fp;
	double	m_upLimit_Fp;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_FP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_FP)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_FP_H__7538FB77_346E_43E6_BFE1_94FEF8FD0F2D__INCLUDED_)
