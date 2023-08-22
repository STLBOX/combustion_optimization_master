#if !defined(AFX_ON_FUEL_H__480E81EC_C538_403A_90E7_000FBB2514A8__INCLUDED_)
#define AFX_ON_FUEL_H__480E81EC_C538_403A_90E7_000FBB2514A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ON_FUEL.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CON_FUEL dialog

class CON_FUEL : public CDialog
{
// Construction
public:
	CON_FUEL(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CON_FUEL)
	enum { IDD = IDD_ConstrFuel };
	double	m_CombOpt_dmax_fuel1;
	double	m_CombOpt_dmax_fuel2;
	double	m_CombOpt_dmax_fuel3;
	double	m_CombOpt_dmax_fuel4;
	double	m_CombOpt_dmax_fuel5;
	double	m_CombOpt_dmax_fuel6;
	double	m_CombOpt_dmin_fuel1;
	double	m_CombOpt_dmin_fuel2;
	double	m_CombOpt_dmin_fuel3;
	double	m_CombOpt_dmin_fuel4;
	double	m_CombOpt_dmin_fuel5;
	double	m_CombOpt_dmin_fuel6;
	double	m_CombOpt_downLimit_fuel1;
	double	m_CombOpt_downLimit_fuel2;
	double	m_CombOpt_downLimit_fuel3;
	double	m_CombOpt_downLimit_fuel4;
	double	m_CombOpt_downLimit_fuel5;
	double	m_CombOpt_downLimit_fuel6;
	double	m_CombOpt_dumax_fuel1;
	double	m_CombOpt_dumax_fuel2;
	double	m_CombOpt_dumax_fuel3;
	double	m_CombOpt_dumax_fuel4;
	double	m_CombOpt_dumax_fuel5;
	double	m_CombOpt_dumax_fuel6;
	double	m_CombOpt_dumin_fuel1;
	double	m_CombOpt_dumin_fuel2;
	double	m_CombOpt_dumin_fuel3;
	double	m_CombOpt_dumin_fuel4;
	double	m_CombOpt_dumin_fuel5;
	double	m_CombOpt_dumin_fuel6;
	double	m_CombOpt_upLimit_fuel1;
	double	m_CombOpt_upLimit_fuel2;
	double	m_CombOpt_upLimit_fuel3;
	double	m_CombOpt_upLimit_fuel4;
	double	m_CombOpt_upLimit_fuel5;
	double	m_CombOpt_upLimit_fuel6;
	double	m_CombOptInt_upLimit_fuel1;
	double	m_CombOptInt_upLimit_fuel2;
	double	m_CombOptInt_upLimit_fuel3;
	double	m_CombOptInt_upLimit_fuel4;
	double	m_CombOptInt_upLimit_fuel5;
	double	m_CombOptInt_upLimit_fuel6;
	double	m_CombOptInt_downLimit_fuel1;
	double	m_CombOptInt_downLimit_fuel2;
	double	m_CombOptInt_downLimit_fuel3;
	double	m_CombOptInt_downLimit_fuel4;
	double	m_CombOptInt_downLimit_fuel5;
	double	m_CombOptInt_downLimit_fuel6;
	double	m_CombOptInt_dumax_fuel1;
	double	m_CombOptInt_dumax_fuel2;
	double	m_CombOptInt_dumax_fuel3;
	double	m_CombOptInt_dumax_fuel4;
	double	m_CombOptInt_dumax_fuel5;
	double	m_CombOptInt_dumax_fuel6;
	double	m_CombOptInt_dumin_fuel1;
	double	m_CombOptInt_dumin_fuel2;
	double	m_CombOptInt_dumin_fuel3;
	double	m_CombOptInt_dumin_fuel4;
	double	m_CombOptInt_dumin_fuel5;
	double	m_CombOptInt_dumin_fuel6;
	double	m_CombOptInt_dumax_fuel7;
	double	m_CombOptInt_dumax_fuel8;
	double	m_CombOptInt_dumax_fuel9;
	double	m_CombOptInt_dumax_fuel10;
	double	m_CombOptInt_dumax_fuel11;
	double	m_CombOptInt_dumax_fuel12;
	double	m_DzFuelA;
	double	m_DzFuelB;
	double	m_DzFuelC;
	double	m_DzFuelD;
	double	m_DzFuelF;
	double	m_DzFuelE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CON_FUEL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CON_FUEL)
	virtual void OnOK();
	virtual void OnCancel();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ON_FUEL_H__480E81EC_C538_403A_90E7_000FBB2514A8__INCLUDED_)
