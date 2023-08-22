#if !defined(AFX_ON_BURNER_H__F2FE37FD_24A5_4B46_8977_75FF9F07D131__INCLUDED_)
#define AFX_ON_BURNER_H__F2FE37FD_24A5_4B46_8977_75FF9F07D131__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_BURNER.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_BURNER dialog

class CON_BURNER : public CDialog
{
// Construction
public:
	CON_BURNER(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_BURNER)
	enum { IDD = IDD_ConstrBurner1 };
	double	m_dl_burner;
	double	m_dumax_burner;
	double	m_dumin_burner;
	double	m_rate_burner;
	double	m_ul_burner;
	double	m_dz_burner;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_BURNER)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_BURNER)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_BURNER_H__F2FE37FD_24A5_4B46_8977_75FF9F07D131__INCLUDED_)
