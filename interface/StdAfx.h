// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(AFX_STDAFX_H__A06B3E85_160A_4AC3_8874_FCE06BBF45A7__INCLUDED_)
#define AFX_STDAFX_H__A06B3E85_160A_4AC3_8874_FCE06BBF45A7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

// 自定义消息
#define WM_TrayShow          (WM_USER+101)  // 最小化到托盘
#define IDM_TrayShowWindow   (WM_USER+102)  // 托盘命令

#define WM_ProStart			 (WM_USER+100) //启动程序	


// 管理进行用
#define ProControl_Stop			0
#define ProControl_Start		1
#define ProControl_Pause		2
#define ProState_Stop			0
#define ProState_Start			1
#define ProState_Pause			2
#define ProState_Error			3

class ProcessInf
{
public:
	int iState;
	int iControl;
	int iCount;//
	int SampleT;
	BOOL bWindowShow;
	BOOL bProStart;
	CString pProName;
	PROCESS_INFORMATION pi;
	STARTUPINFO si;
	BOOL bExitProcess;
};


//  Wait窗口参数
#define WaitALLProStop		0
#define WaitOPCStop			1
#define WaitDMCStop			2
#define WaitOPCPause		3
#define WaitDMCPause		4
#define WaitALLProStart		5
#define WaitOPCStart		6
#define WaitDMCStart		7
#define WaitDMCSetPara		8

#define WaitRHStop			9
#define WaitRHPause	    	10
#define WaitRHStart	    	11
#define WaitRHSetPara		12

#define WaitCombOptStop			13
#define WaitCombOptPause	    14
#define WaitCombOptStart	    15
#define WaitCombOptSetPara		16

#define WaitNOXStop			17
#define WaitNOXPause	    18
#define WaitNOXStart	    19
#define WaitNOXSetPara		20

//--------------四舍五入
#include "math.h"
double Round(double Num,int i);
double Sign(double Num);
double Abs(double Num);
double Max(double x,double y);
//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STDAFX_H__A06B3E85_160A_4AC3_8874_FCE06BBF45A7__INCLUDED_)
