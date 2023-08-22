// interfaceDlg.h : header file
//

#if !defined(AFX_INTERFACEDLG_H__BF795801_3EFE_4B10_BFDA_CE36096A3997__INCLUDED_)
#define AFX_INTERFACEDLG_H__BF795801_3EFE_4B10_BFDA_CE36096A3997__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "fstream.h"
#include "Resource.h"
#include "ShareMem.h"
//#include "windows.h"  //��һ����Ҫ
//#include "stdio.h"  //��һ����Ҫ
#include "tlhelp32.h"  //һ����Ҫ
/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg dialog

class CInterfaceDlg : public CDialog
{
// Construction
public:
	CInterfaceDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	//{{AFX_DATA(CInterfaceDlg)
	enum { IDD = IDD_Interface_DIALOG };
		// NOTE: the ClassWizard will add data members here
	CListBox	m_LogList;
	CString	m_CONTROLLER_bAdmin;  // ��ǰȨ��
	CString	m_bOPCState;  // OPCͨѶ
	CString	m_bCombOptState;  // ȼ���Ż�״̬
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CInterfaceDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	virtual LRESULT DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CInterfaceDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnTrayShow(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnProStart(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnMainProExAdmin();  // �ĸ������¼�
	afx_msg void OnMainProExit();
	afx_msg void OnMainProReStart();
	afx_msg void OnMainProCombOpt();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	// ������д�����ڴ棬SIM_SX
	HANDLE hReadShareMem;
	HANDLE hWriteShareMem;

	HANDLE hOpenCombOptReadMapFile;  // DCS������
	HANDLE hOpenCombOptWriteMapFile;  // ��DCSд����
	HANDLE hCombOptOPMapFile;  // ��interface��CombOptͨѶ������OP����

	//CMainShareMem* pMainMem;
	double* pCombOptReadData;
	double* pCombOptWriteData;
	double* pCombOptOP;

	// CMainShareMem
	HANDLE hMainMapFile;
    CMainShareMem* pMainMem;
	CString pszProName[3];
	int NumPro;
	// ��ʼ��
	BOOL bWindowShow;
	BOOL bRecordData;  // �Ƿ��¼����
	BOOL bReStart;  // ��λȼ���Ż�
	BOOL bAllStart;  // ���н����Ƿ�������ʼ,���Ｘ����������
	// ��ʼ������
	void ToTray();
	void DeleteTray();
    // ��ʼ����־
	CTime LogTime;
	void LogSystem(ofstream fLogFile, CString LogContent);
	void SetListBoxSPGD();

	BOOL bAdmin;  // ����Ȩ��
	ProcessInf PI[2];  // ������������

	int WaitTime;  // �ȴ�CombOpt��������ʱ�䣬������ʱ�����˳����н���
	int MaxWaitTime;


	BOOL IsProccessRunning(CString strProccess);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDLG_H__BF795801_3EFE_4B10_BFDA_CE36096A3997__INCLUDED_)
