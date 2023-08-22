#if !defined(AFX_ON_O2_H__0A48138D_8C5A_49A8_9E82_4D38123E4BC6__INCLUDED_)
#define AFX_ON_O2_H__0A48138D_8C5A_49A8_9E82_4D38123E4BC6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_O2.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_O2 dialog

class CON_O2 : public CDialog
{
// Construction
public:
	CON_O2(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_O2)
	enum { IDD = IDD_ConstrO2 };
	double	m_CombOpt_dmax_o2;
	double	m_CombOpt_upLimit_o2;
	double	m_CombOpt_downLimit_o2;
	double	m_CombOpt_dmin_o2;
	double	m_CombOpt_dumax_o2;
	double	m_CombOpt_dumin_o2;
	double	m_CombOptInt_upLimit_O;
	double	m_CombOptInt_downLimit_O;
	double	m_CombOptInt_dumax_O;
	double	m_CombOptInt_dumin_O;
	double	m_CombOptInt_dumax_O_2;
	double	m_DzO2;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_O2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_O2)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_O2_H__0A48138D_8C5A_49A8_9E82_4D38123E4BC6__INCLUDED_)
