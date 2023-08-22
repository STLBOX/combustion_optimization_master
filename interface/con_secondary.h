#if !defined(AFX_ON_SECONDARY_H__A043EA33_D694_4872_9BB0_15DAA65A5828__INCLUDED_)
#define AFX_ON_SECONDARY_H__A043EA33_D694_4872_9BB0_15DAA65A5828__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_SECONDARY.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_SECONDARY dialog

class CON_SECONDARY : public CDialog
{
// Construction
public:
	CON_SECONDARY(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_SECONDARY)
	enum { IDD = IDD_ConstrSec };

	double	m_CombOptInt_upLimit_A;
	double	m_CombOptInt_upLimit_B;
	double	m_CombOptInt_upLimit_C;
	double	m_CombOptInt_upLimit_D;
	double	m_CombOptInt_upLimit_E;
	double	m_CombOptInt_upLimit_F;


	double	m_CombOptInt_downLimit_A;
	double	m_CombOptInt_downLimit_B;
	double	m_CombOptInt_downLimit_C;
	double	m_CombOptInt_downLimit_D;
	double	m_CombOptInt_downLimit_E;
	double	m_CombOptInt_downLimit_F;


	double	m_CombOptInt_dumax_A;
	double	m_CombOptInt_dumax_B;
	double	m_CombOptInt_dumax_C;
	double	m_CombOptInt_dumax_D;
	double	m_CombOptInt_dumax_E;
	double	m_CombOptInt_dumax_F;


	double	m_CombOptInt_dumin_A;
	double	m_CombOptInt_dumin_B;
	double	m_CombOptInt_dumin_C;
	double	m_CombOptInt_dumin_D;
	double	m_CombOptInt_dumin_E;
	double	m_CombOptInt_dumin_F;

	double	m_CombOptInt_suLimit_A;
	double	m_CombOptInt_suLimit_B;
	double	m_CombOptInt_suLimit_C;
	double	m_CombOptInt_suLimit_D;
	double	m_CombOptInt_suLimit_E;
	double	m_CombOptInt_suLimit_F;

	double	m_DzSecA;
	double	m_DzSecB;
	double	m_DzSecC;
	double	m_DzSecD;
	double	m_DzSecE;
	double	m_DzSecF;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_SECONDARY)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_SECONDARY)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_SECONDARY_H__A043EA33_D694_4872_9BB0_15DAA65A5828__INCLUDED_)
