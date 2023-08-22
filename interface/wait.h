#if !defined(AFX_WAIT_H__545AADAB_CAC1_434F_A72C_4D89AD3B3475__INCLUDED_)
#define AFX_WAIT_H__545AADAB_CAC1_434F_A72C_4D89AD3B3475__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Wait.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CWait dialog

class CWait : public CDialog
{
// Construction
public:
	CWait(int inModePara = INFINITE, CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CWait)
	enum { IDD = IDD_Wait_DIALOG };
	CString	m_Wait_Msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWait)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CWait)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int ModePara;
	int TimeCount;
//	DWORD dwOPC,dwDMC,dwInitCOM;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WAIT_H__545AADAB_CAC1_434F_A72C_4D89AD3B3475__INCLUDED_)
