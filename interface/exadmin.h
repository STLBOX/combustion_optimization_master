#if !defined(AFX_EXADMIN_H__453A1669_443A_4513_82CC_C2384709744E__INCLUDED_)
#define AFX_EXADMIN_H__453A1669_443A_4513_82CC_C2384709744E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExAdmin.h : header file



class CExAdmin : public CDialog
{

public:
	CExAdmin(CWnd* pParent = NULL);  

// Dialog Data
	//{{AFX_DATA(CExAdmin)
	enum { IDD = IDD_ExAdmin_DIALOG };
	CString	m_ExAdmin_szStr;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExAdmin)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


protected:

	// Generated message map functions
	//{{AFX_MSG(CExAdmin)
	afx_msg void OnExAdminOK();
	afx_msg void OnExAdminLogout();
	afx_msg void OnExAdminCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXADMIN_H__453A1669_443A_4513_82CC_C2384709744E__INCLUDED_)
