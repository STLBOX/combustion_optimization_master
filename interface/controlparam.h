#if !defined(AFX_CONTROLPARAM_H__39F426F4_1F2D_4288_8120_7477B9CD01C5__INCLUDED_)
#define AFX_CONTROLPARAM_H__39F426F4_1F2D_4288_8120_7477B9CD01C5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ControlParam.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ControlParam dialog

class ControlParam : public CDialog
{
// Construction
public:
	ControlParam(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(ControlParam)
	enum { IDD = IDD_ControlParam };
	double	m_OACoal;
	double	m_OBCoal;
	double	m_OCCoal;
	double	m_ODCoal;
	double	m_OECoal;
	double	m_OFCoal;
	double	m_OO2;
	double	m_RCCoal;
	double	m_RDCoal;
	double	m_RECoal;
	double	m_RFCoal;
	double	m_RO2;
	double	m_OP1;
	double	m_RP1;
	double	m_OBleft;
	double	m_OBright;
	double	m_OFleft;
	double	m_OFright;
	double	m_OsecAA;
	double	m_OsecAB;
	double	m_OsecBA;
	double	m_OsecBB;
	double	m_OsecCA;
	double	m_OsecCB;
	double	m_OsecDA;
	double	m_OsecDB;
	double	m_OsecEA;
	double	m_OsecEB;
	double	m_OsecFA;
	double	m_OsecFB;
	double	m_RACoal;
	double	m_RBCoal;
	double	m_RBleft;
	double	m_RBright;
	double	m_RFleft;
	double	m_RFright;
	double	m_RSecAA;
	double	m_RSecAB;
	double	m_RSecBA;
	double	m_RSecBB;
	double	m_RSecCA;
	double	m_RSecCB;
	double	m_RSecDA;
	double	m_RSecDB;
	double	m_RSecEA;
	double	m_RSecEB;
	double	m_RSecFA;
	double	m_RSecFB;
	double	m_Oburn1;
	double	m_Oburn2;
	double	m_Oburn3;
	double	m_Rburn1;
	double	m_Rburn2;
	double	m_Rburn3;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ControlParam)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ControlParam)
	virtual BOOL OnInitDialog();
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnExit();
	afx_msg void OnClearOptInc();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	bool ReSetOptInc; 
	bool ReSetOptIncO2; 
	bool ReSetOptIncSec; 
	bool ReSetOptIncSofa; 
	bool ReSetOptIncCoal; 
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONTROLPARAM_H__39F426F4_1F2D_4288_8120_7477B9CD01C5__INCLUDED_)
