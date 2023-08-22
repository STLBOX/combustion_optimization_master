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
//#include "windows.h"  //不一定需要
//#include "stdio.h"  //不一定需要
#include "tlhelp32.h"  //一定需要
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
	CString	m_CONTROLLER_bAdmin;  // 当前权限
	CString	m_bOPCState;  // OPC通讯
	CString	m_bCombOptState;  // 燃烧优化状态
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
	afx_msg void OnMainProExAdmin();  // 四个单机事件
	afx_msg void OnMainProExit();
	afx_msg void OnMainProReStart();
	afx_msg void OnMainProCombOpt();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()


public:
	// 创建读写共享内存，SIM_SX
	HANDLE hReadShareMem;
	HANDLE hWriteShareMem;

	HANDLE hOpenCombOptReadMapFile;  // DCS读数据
	HANDLE hOpenCombOptWriteMapFile;  // 向DCS写数据
	HANDLE hCombOptOPMapFile;  // 仅interface与CombOpt通讯，传输OP数据

	//CMainShareMem* pMainMem;
	double* pCombOptReadData;
	double* pCombOptWriteData;
	double* pCombOptOP;

	// CMainShareMem
	HANDLE hMainMapFile;
    CMainShareMem* pMainMem;
	CString pszProName[3];
	int NumPro;
	// 初始化
	BOOL bWindowShow;
	BOOL bRecordData;  // 是否记录数据
	BOOL bReStart;  // 复位燃烧优化
	BOOL bAllStart;  // 所有进程是否都正常开始,这里几个心跳正常
	// 初始化托盘
	void ToTray();
	void DeleteTray();
    // 初始化日志
	CTime LogTime;
	void LogSystem(ofstream fLogFile, CString LogContent);
	void SetListBoxSPGD();

	BOOL bAdmin;  // 控制权限
	ProcessInf PI[2];  // 管理两个进程

	int WaitTime;  // 等待CombOpt进程启动时间，超过该时间则退出所有进程
	int MaxWaitTime;


	BOOL IsProccessRunning(CString strProccess);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_INTERFACEDLG_H__BF795801_3EFE_4B10_BFDA_CE36096A3997__INCLUDED_)
