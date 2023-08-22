// interface.h : main header file for the INTERFACE application
//

#if !defined(AFX_INTERFACE_H__D97501C1_752D_4A6E_9F58_0AA0C6936D50__INCLUDED_)
#define AFX_INTERFACE_H__D97501C1_752D_4A6E_9F58_0AA0C6936D50__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "OPTCtrlDLL.h"

/////////////////////////////////////////////////////////////////////////////
// CInterfaceApp:
// See interface.cpp for the implementation of this class
//

class CInterfaceApp : public CWinApp
{
public:
	CInterfaceApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceApp)
	public:
	virtual BOOL InitInstance();
	virtual BOOL ExitInstance();
	//}}AFX_VIRTUAL

// Implementation

	//{{AFX_MSG(CInterfaceApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACE_H__D97501C1_752D_4A6E_9F58_0AA0C6936D50__INCLUDED_)
