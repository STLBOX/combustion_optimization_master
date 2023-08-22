// interfaceDlg.cpp : implementation file
//

#include "stdafx.h"
#include "interface.h"
#include "interfaceDlg.h"
#include "ObjCombOpt.h"
#include "CombOpt.h"  
#include "ExAdmin.h" 
#include "Wait.h" 

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


CInterfaceDlg* dp;
ObjCombOpt theComb;
/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg dialog

CInterfaceDlg::CInterfaceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CInterfaceDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CInterfaceDlg)
		// NOTE: the ClassWizard will add member initialization here
	m_CONTROLLER_bAdmin = _T("Guest");
	m_bOPCState = _T("");
	m_bCombOptState = _T("");
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CInterfaceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CInterfaceDlg)
	DDX_Control(pDX, IDC_LogList, m_LogList);
	DDX_Text(pDX, IDC_CONTROLLER_EDIT6, m_CONTROLLER_bAdmin);
	DDX_Text(pDX, IDC_CONTROLLER_EDIT7, m_bOPCState);
	DDX_Text(pDX, IDC_CONTROLLER_EDIT10, m_bCombOptState);
	// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CInterfaceDlg, CDialog)
	//{{AFX_MSG_MAP(CInterfaceDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_TrayShow,OnTrayShow)  // 初始化
	ON_COMMAND(IDM_TrayShowWindow,OnTrayShow)
	ON_MESSAGE(WM_ProStart,OnProStart)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_MainProExAdmin, OnMainProExAdmin)
	ON_BN_CLICKED(IDC_MainProExit, OnMainProExit)
	ON_BN_CLICKED(IDC_MainProReStart, OnMainProReStart)
	ON_BN_CLICKED(IDC_MainProExit2, OnMainProCombOpt)
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CInterfaceDlg message handlers

BOOL CInterfaceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
    //  禁用关闭按钮
    ASSERT(pSysMenu != NULL);
	pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);

	// 判断某程序是否正在运行
    CString ThisAPP = _T("CombOpt.exe");
    BOOL IsRunning = IsProccessRunning(ThisAPP);
	if (IsRunning)
	{
		MessageBox(_T("已启动一个程序！"),_T("AdvControl警告："),MB_ICONWARNING);
		ExitProcess(0);
		return TRUE; 
	}

	// 共享内存句柄和指针
	hReadShareMem = NULL;
	hWriteShareMem = NULL;
	hOpenCombOptReadMapFile = NULL;
	hOpenCombOptWriteMapFile = NULL;
	hCombOptOPMapFile = NULL;
	pCombOptReadData = NULL;
	pCombOptWriteData = NULL;
	pCombOptOP = NULL;

//	WindowShow = TRUE;
	bAllStart = TRUE;  // 测试时，未修改逻辑，设置为true SIM_TEST
	bAdmin = FALSE;
	bReStart = FALSE;

//  mainsharemem
	NumPro = 3;
	pszProName[0] = "Interface.exe";
	pszProName[1] = "Interface.exe";
	pszProName[2] = "ProCombOpt.exe";

	dp = (CInterfaceDlg*) this;
    PI[0].pProName= _T("ProOPC.exe");  // 写死pszProName中存储两个进程信息
	memset(&(PI[0].si),0,sizeof(STARTUPINFO));
	PI[0].si.cb = sizeof(STARTUPINFO);
	PI[0].iCount = 0;

	PI[1].pProName=_T("CombOpt.exe");
	memset(&(PI[1].si),0,sizeof(STARTUPINFO));
	PI[1].si.cb = sizeof(STARTUPINFO);
	PI[1].iCount = 0;

	WaitTime = 0; 
	MaxWaitTime = 500;  // 0.2s刷新时间，最长等待40s
    // 创建托盘
	ToTray();
    // 启动
	PostMessage(WM_ProStart);
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CInterfaceDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else if (nID == SC_CLOSE)
	{
		bAdmin = FALSE;
		bWindowShow = FALSE;
		ShowWindow(SW_HIDE);
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CInterfaceDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CInterfaceDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}


void CInterfaceDlg::ToTray()
{
	// 设置托盘图标
	NOTIFYICONDATA Nid;
    Nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    Nid.hWnd = m_hWnd;
    Nid.uID = IDR_MAINFRAME;
    Nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
    Nid.uCallbackMessage = WM_TrayShow; // 自定义托盘菜单消息
    Nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
    strcpy(Nid.szTip, _T("优化控制"));
    Shell_NotifyIcon(NIM_ADD, &Nid); // 在托盘区添加图标
	//ShowWindow(SW_HIDE);
}

void CInterfaceDlg::DeleteTray()
{
	// 删除托盘图标
	NOTIFYICONDATA Nid;
	Nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA); 
	Nid.hWnd = m_hWnd; 
	Nid.uID = IDR_MAINFRAME;
	Nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	Nid.uCallbackMessage = WM_TrayShow;//自定义的消息名称
	Nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy(Nid.szTip,_T("优化控制")); //信息提示条为"计划任务提醒"
	Shell_NotifyIcon(NIM_DELETE,&Nid); //在托盘区删除图标
}


LRESULT CInterfaceDlg::OnTrayShow(WPARAM wParam, LPARAM lParam)
{
	//TODO: Add your message handle code
	if(wParam != IDR_MAINFRAME) // 判断图标ID是否相符
        return 1;
    switch(lParam)
    {
	case WM_RBUTTONUP: 
        {// 按鼠标右键
            CPoint point;
            GetCursorPos(&point);
            CMenu menu;
            menu.CreatePopupMenu();
            menu.AppendMenu(MF_STRING, IDM_TrayShowWindow, _T("显示界面"));
            SetForegroundWindow();  // 解决菜单失去焦点不消失的BUG
            menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
            menu.DestroyMenu(); 
        }
        break;
    case WM_LBUTTONDBLCLK: // 双击鼠标左键
		bWindowShow = TRUE;
        ShowWindow(SW_SHOW);
        break;
    }
    return 0;
}


// 开启另外两个进程
LRESULT CInterfaceDlg::OnProStart(WPARAM wParam, LPARAM lParam)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString LogFile(szPath);
	LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
	LogTime = CTime::GetCurrentTime();
	LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
	ofstream outLog(LogFile,ios::out|ios::app);
	LogSystem(outLog,_T("--------程序启动--------"));

	 // 创建共享内存（这部分在通讯中完成），XTReadShareMem和XTWriteShareMem  SIM_SX
	hReadShareMem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,READ_NUM*sizeof(double),_T("XTReadShareMem"));
	if(hReadShareMem == NULL)
	{
	    LogSystem(outLog,_T("创建ReadShareMem共享内存失败！"));
		SendMessage(WM_CLOSE);
		return 6;
	}

	hWriteShareMem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,WRITE_NUM*sizeof(double),_T("XTWriteShareMem"));
	if(hWriteShareMem == NULL)
	{
	    LogSystem(outLog,_T("创建WriteShareMem共享内存失败！"));
		SendMessage(WM_CLOSE);
		return 6;
	}


	// 打开OPC读共享内存 pCombOptReadData
	hOpenCombOptReadMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTReadShareMem")); 	
	if(hOpenCombOptReadMapFile == NULL)
	{
		LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存失败！"));
		SendMessage(WM_CLOSE);
		return 5;
	}
	pCombOptReadData = (double*)MapViewOfFile(hOpenCombOptReadMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptReadData == NULL)
	{
		LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存映射文件失败 ！"));
		SendMessage(WM_CLOSE);
		return 6;
    }
	LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存成功！"));


	// 打开OPC写共享内存 pCombOptWriteData
	hOpenCombOptWriteMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTWriteShareMem")); 
	if(hOpenCombOptWriteMapFile == NULL)
	{
		LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存失败！"));
		SendMessage(WM_CLOSE);
		return 5;
	}
	pCombOptWriteData = (double*)MapViewOfFile(hOpenCombOptWriteMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptWriteData == NULL)
	{
		LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存映射文件失败 ！"));
		SendMessage(WM_CLOSE);
		return 6;
    }
	LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存成功！"));


	// 创建OP共享内存，里面包含模型参数和一些显示用数据  Comb_OpN 371
	hCombOptOPMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,Comb_OpN*sizeof(double),_T("OPShareMem")); //创建Comb共享内存
	if(hWriteShareMem == NULL)
	{
	    LogSystem(outLog,_T("创建OP共享内存失败！"));
		SendMessage(WM_CLOSE);
		return 6;
	}
	// 打开OP共享内存
	pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptOP == NULL)
	{
		LogSystem(outLog,_T("打开OP共享内存映射文件失败 ！"));
		SendMessage(WM_CLOSE);
	}
	LogSystem(outLog,_T("打开OP共享内存成功！"));


	// 创建MainshareMem,可能OPC会使用到
	hMainMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,(NumPro+1)*sizeof(CMainShareMem),_T("MyMainShareMem"));
	if(hMainMapFile)
	{
		pMainMem = (CMainShareMem*)MapViewOfFile(hMainMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	}
	if(hMainMapFile == NULL||pMainMem == NULL)
	{
		LogSystem(outLog,_T("创建MainPro共享内存失败！"));
		MessageBox(_T("创建MainPro共享内存失败！"),_T("警告："),MB_ICONWARNING);
		SendMessage(WM_CLOSE);
		return 2;
	}


	else
	{
		LogSystem(outLog,_T("创建MainPro共享内存成功！"));
		for(int i = 0; i < NumPro; i++)
		{
			pMainMem[i].iState = ProState_Stop;
			pMainMem[i].iControl = ProControl_Stop;
			pMainMem[i].iCount = 0;
			pMainMem[i].SampleT = 0;
			pMainMem[i].bWindowShow = FALSE;
			pMainMem[i].bProStart = FALSE;
			strncpy(pMainMem[i].szProName,pszProName[i],min(sizeof(pMainMem[i].szProName),pszProName[i].GetLength()));
			pMainMem[i].szProName[pszProName[i].GetLength()] = '\0';
			pMainMem[i].pi.hProcess = INVALID_HANDLE_VALUE;
			pMainMem[i].pi.hThread = INVALID_HANDLE_VALUE;
			pMainMem[i].bExitProcess = FALSE;
		}
		pMainMem[NumPro].iState = ProState_Stop;
		pMainMem[NumPro].iControl = ProControl_Stop;
		pMainMem[NumPro].iCount = 0;
		pMainMem[NumPro].SampleT = 0;
		pMainMem[NumPro].bWindowShow = FALSE;
		pMainMem[NumPro].bProStart = FALSE;
		strncpy(pMainMem[NumPro].szProName,_T("NULL\0"),sizeof(pMainMem[i].szProName));
		pMainMem[NumPro].pi.hProcess = INVALID_HANDLE_VALUE;
		pMainMem[NumPro].pi.hThread = INVALID_HANDLE_VALUE;
		pMainMem[NumPro].bExitProcess = FALSE;
	}


	SetTimer(1,1000,NULL);
    // 启动interface前 需要启动通讯程序及CombOpt
	// 判断 OPC是否开启
    BOOL IsRunning = IsProccessRunning(PI[0].pProName);
	if (!IsRunning)
	{
		if(!CreateProcess((LPSTR)(LPCTSTR)(PI[0].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[0].si),&(PI[0].pi)))
		{
			PI[0].bProStart = false;
			LogSystem(outLog,_T("启动通讯程序失败！"));
			m_bOPCState = _T("异常");
		}
		else
		{
			PI[0].bProStart = true;
			LogSystem(outLog,_T("启动通讯程序成功！"));
			m_bOPCState = _T("正常");
		}
	}
	else
	{
		LogSystem(outLog,_T("启动通讯程序成功！"));
		m_bOPCState = _T("正常");
	}
    UpdateData(FALSE);

	if (PI[0].bProStart == FALSE)  // 失败直接return
	{   
		outLog.close();
		SendMessage(WM_CLOSE);
		return 0;
	}
	// theComb.MapToTag();  // 关联Tag，IO_tag Op_tag 直接使用
    // theComb.Init_Op_tag("param//Op.txt");  // 对数据库中Op参数初始化，防止存在值，影响状态显示

	Sleep(5000);  // 等待共享内存创建完毕，如果

    LogSystem(outLog,_T("--------启动燃烧优化--------"));
	// 启动燃烧优化进程 theComb.Op_tag[358]，等待直到该值变为1，如果该值已经为1，说明已经启动一个燃烧优化进程（这是不合理）
	if(!CreateProcess((LPSTR)(LPCTSTR)(PI[1].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
		{
			PI[1].bProStart = FALSE;
			LogSystem(outLog,_T("启动燃烧优化进程失败！"));
		}
	else
		{	
			PI[1].bProStart = TRUE;
			LogSystem(outLog,_T("启动燃烧优化进程！"));
		}
	if (PI[1].bProStart == FALSE)  // 失败直接return
	{   
		outLog.close();
		SendMessage(WM_CLOSE);
		return 0;
	}

	// Sleep(8000); // 等待8s等待燃烧优化进程创建好共享内存

    if (PI[1].bProStart == TRUE)  // 进程开始载入内存执行，接下来判断是否成功
	{
		CWait theWait(WaitCombOptStart);
		theWait.DoModal();
		if (WaitTime==0)
		{
			LogSystem(outLog,_T("燃烧优化进程启动成功！"));	
			PI[1].bProStart = TRUE;
			m_bCombOptState = _T("正常");
			bAllStart=TRUE; 
			UpdateData(FALSE);
		}
		else if (WaitTime==-1)
		{
			LogSystem(outLog,_T("等待时间过长，燃烧优化启动失败！"));
			PI[1].bProStart = FALSE;
			m_bCombOptState = _T("异常");
			UpdateData(FALSE);
		}
		else
		{
			LogSystem(outLog,_T("燃烧优化启动失败！"));
			PI[1].bProStart = FALSE;
			m_bCombOptState = _T("异常");
			UpdateData(FALSE);
		}
	}
		
	outLog.close();
	SetTimer(2,20000,NULL);  // 打开定时器，进行进程监控
	return 0;
}


void CInterfaceDlg::OnTimer(UINT nIDEvent) 
{	
    switch(nIDEvent)
	{
		case 1 :
		{
			// 将优化增量置为0，如果是复位状态
			if (bReStart)
			{  	
				for (int i=0;i<=5;i++)  // 给煤机
				{
					pCombOptWriteData[2+i] = 0;
				}

				for ( i=0;i<=15;i++)  // 二次风and燃尽风
				{	
					pCombOptWriteData[8+i] = 0;
				}
				pCombOptWriteData[24] = 0 ;
				pCombOptWriteData[25] = 0 ;
			    bReStart = false;
			}
			
			// Ontimer 中仅执行一次 初始化完成后关闭Ontimer1
			if (int(pCombOptOP[358])==2)
			{
				m_LogList.InsertString(m_LogList.GetCount(),LogTime.Format("%H:%M:%S ")+_T("燃烧优化初始化完成！"));
				SetListBoxSPGD();
				m_LogList.SetCurSel(m_LogList.GetCount() - 1);
				KillTimer(1);  // 初始化完成后，关闭
				bReStart = FALSE;
			}
            break;
		}
		
		case 2:  // 用于进程监控，监控CombOpt与OptCtrl
		{
			//  先检测是否需要重启数据库，数据库读数周期为1s
			//  bool DataBaseNormal=TRUE;
			BOOL IsRunning = IsProccessRunning(PI[0].pProName);  // 判断
			if (!IsRunning)
			{
				KillTimer(2);  // 暂停计时器
				TCHAR szPath[MAX_PATH];
				GetModuleFileName(NULL, szPath, MAX_PATH);
				CString LogFile(szPath);
				LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
				LogTime = CTime::GetCurrentTime();
				LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
				ofstream outLog(LogFile,ios::out|ios::app);
				LogSystem(outLog,_T("OPC通讯异常关闭！"));

				if(CreateProcess((LPSTR)(LPCTSTR)PI[0].pProName,NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[0].si),&(PI[0].pi)))
				{	
					PI[0].bProStart = TRUE;
					LogSystem(outLog,_T("重启OPC成功！"));
					PI[0].iCount = 0;

					Sleep(8000); 
					// 打开OPC读共享内存 pCombOptReadData
					hOpenCombOptReadMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTReadShareMem")); 	
					if(hOpenCombOptReadMapFile == NULL)
					{
						LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存失败！"));
						SendMessage(WM_CLOSE);
					}
					pCombOptReadData = (double*)MapViewOfFile(hOpenCombOptReadMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
					if (pCombOptReadData == NULL)
					{
						LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存映射文件失败 ！"));
						SendMessage(WM_CLOSE);
					}
					LogSystem(outLog,_T("interface打开ProCombOpt(READ)共享内存成功！"));

					// 打开OPC写共享内存 pCombOptWriteData
					hOpenCombOptWriteMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTWriteShareMem")); 
					if(hOpenCombOptWriteMapFile == NULL)
					{
						LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存失败！"));
						SendMessage(WM_CLOSE);
					}
					pCombOptWriteData = (double*)MapViewOfFile(hOpenCombOptWriteMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
					if (pCombOptWriteData == NULL)
					{
						LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存映射文件失败 ！"));
						SendMessage(WM_CLOSE);
					}
					LogSystem(outLog,_T("interface打开ProCombOpt(WRITE)共享内存成功！"));

					/// DataBaseNormal = TRUE;
				}
				else
				{
					// DataBaseNormal = FALSE;  // 重启失败
					PI[0].bProStart = FALSE;
					LogSystem(outLog,_T("重启OPC失败！"));
					PI[0].iCount++;
				}

				if (PI[0].iCount >= 2)  // 连续重启2次失败，杀死定时器，不再重启
				{
					KillTimer(2);
					break;
				}
				SetTimer(2,20000,NULL);  // 重开计时器
				outLog.close();	
			}

			//  如果CombOpt退出，那么重启CombOpt
			int HeartBeatk1;
			HeartBeatk1 = int(pCombOptWriteData[100]);
			Sleep(4100);  // 睡眠4.1s 此时心跳应该为0
			if (int(pCombOptWriteData[100]) == HeartBeatk1)  // 心跳错误，前后相等
			{   
				BOOL IsRunning = IsProccessRunning(PI[1].pProName);  // 再次判断
				if (!IsRunning)
				{	
					KillTimer(2);  // 暂停计时器
					TCHAR szPath[MAX_PATH];
					GetModuleFileName(NULL, szPath, MAX_PATH);
					CString LogFile(szPath);
					LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
					LogTime = CTime::GetCurrentTime();
					LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
					ofstream outLog(LogFile,ios::out|ios::app);
					LogSystem(outLog,_T("燃烧优化已退出！"));
					// 重启燃烧优化
					if(CreateProcess((LPSTR)(LPCTSTR)PI[1].pProName,NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
					{	
						PI[1].bProStart = TRUE;
						LogSystem(outLog,_T("重启燃烧优化！"));
						PI[1].iCount = 0;
						/*
						// Sleep(8000);
						// 打开OP共享内存  pCombOptOP
						hCombOptOPMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("OPShareMem"));//打开CombOpt共享内存
						if(hCombOptOPMapFile == NULL)
						{
							LogSystem(outLog,_T("打开OP共享内存失败！"));
							SendMessage(WM_CLOSE);
						}
						
						pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
						if (pCombOptOP == NULL)
						{
							LogSystem(outLog,_T("打开OP共享内存映射文件失败 ！"));
							SendMessage(WM_CLOSE);
						}
						LogSystem(outLog,_T("打开OP共享内存成功！"));
						*/

					}
					else
					{
						PI[1].bProStart = TRUE;
						LogSystem(outLog,_T("重启燃烧优化失败！"));
					}

                    // theComb.Init_Op_tag("param/Op.txt");  // 防止Wait中错误判断
					// 进程开始载入内存执行，接下来判断是否成功
					if (PI[1].bProStart == TRUE) 
					{
						CWait theWait(WaitCombOptStart);
						theWait.DoModal();
						if (WaitTime==0)
						{
							LogSystem(outLog,_T("燃烧优化进程重启成功！"));	
							PI[1].bProStart = TRUE;
							m_bCombOptState = _T("正常");
							bAllStart=TRUE; 
							UpdateData(FALSE);
							PI[1].iCount = 0;
						}
						else if (WaitTime==-1)
						{
							LogSystem(outLog,_T("等待时间过长，燃烧优化重启失败！"));
							PI[1].bProStart = FALSE;
							m_bCombOptState = _T("异常");
							UpdateData(FALSE);
							PI[1].iCount++;
						}
						else
						{
							LogSystem(outLog,_T("燃烧优化重启失败！"));
							PI[1].bProStart = FALSE;
							m_bCombOptState = _T("异常");
							UpdateData(FALSE);
							PI[1].iCount++;
						}
					}
					else
					{
						PI[1].bProStart = FALSE;
						m_bCombOptState = _T("异常");
						UpdateData(FALSE);
						PI[1].iCount++;
					}
					if (PI[1].iCount >= 2)  // 连续重启2次失败，杀死定时器，不再重启
					{
						KillTimer(2);
						break;
					}
					SetTimer(2,20000,NULL);  // 重开计时器
					outLog.close();	
				}  // KillTimer
			
			}  // 

			//  界面显示
		 	if(m_LogList.GetCount() > 50)
			{
				int tCount = m_LogList.GetCount() - 50;
				for(int i = 0;i < tCount; i++)
				{
					m_LogList.DeleteString(0);
				}
				m_LogList.SetCurSel(m_LogList.GetCount() - 1);
			}

			// 对CombOpt反馈状态检测
			if (int(pCombOptOP[358])>=1)
			{
				m_bCombOptState = _T("正常");
			}
			else if (int(pCombOptOP[358])==-1)
			{
				m_bCombOptState = _T("异常");
				bAllStart=FALSE; 
			}
			else
			{
				m_bCombOptState = _T("");
			}

			// 对CombOpt反馈状态检测
			if (int(pCombOptOP[363])==0)
			{
				m_bOPCState = _T("正常");
			}
			else if (int(pCombOptOP[363])==-1)
			{
				m_bOPCState = _T("异常");
				bAllStart=FALSE; 
				KillTimer(2);
				// 杀死CombOpt 和 通信
				m_bCombOptState = _T("退出");
			    TerminateProcess(PI[1].pi.hProcess,1); // 强制关闭CombOpt
				WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
				CloseHandle(PI[1].pi.hThread);
				CloseHandle(PI[1].pi.hProcess);

				TerminateProcess(PI[0].pi.hProcess,1); // 强制关闭OPTCtrlCon
				WaitForSingleObject(PI[0].pi.hProcess,INFINITE);
				CloseHandle(PI[0].pi.hThread);
				CloseHandle(PI[0].pi.hProcess);
				Sleep(3000);
				SetTimer(2,20000,NULL);  // 重开计时器
			}
			else
			{
				m_bOPCState = _T("");
			}
			UpdateData(FALSE);
			break;
		}
	}
	CDialog::OnTimer(nIDEvent);
}


//---------------日志
void CInterfaceDlg::LogSystem(ofstream fLogFile, CString LogContent)
{
	LogTime = CTime::GetCurrentTime();
	fLogFile<<LogTime.Format("%Y-%m-%d %H:%M:%S ")<<LogContent<<endl;
	m_LogList.InsertString(m_LogList.GetCount(),LogTime.Format("%H:%M:%S ")+LogContent);
	SetListBoxSPGD();
	m_LogList.SetCurSel(m_LogList.GetCount() - 1);
}

void CInterfaceDlg::SetListBoxSPGD()
{
	//设置水平滚动
	CString str;								//存放列表框每一项的字符串
	CSize sz;									//存放字符串的长度，存放函数GetTextExtent的返回值
	int dx = 0;									//存放最大的长度
	TEXTMETRIC tm;								//这个结构用在这里，主要是获得当前字体中字符的平均长度
	CDC* pDC = m_LogList.GetDC();
	
	CFont* pFont = m_LogList.GetFont();			//获得列表框中所用的字体
	CFont* pOldFont = pDC->SelectObject(pFont);
	
	pDC->GetTextMetrics(&tm);					//得到字符的平均长度
	
	for (int i = 0; i < m_LogList.GetCount(); i++)
	{
		m_LogList.GetText(i, str);
		sz = pDC->GetTextExtent(str);
		sz.cx += tm.tmAveCharWidth;				//这一步很有意思，如果不加平均长度，会导致最后一个字符被裁剪掉
		if (sz.cx > dx)
			dx = sz.cx;							//只取更大的长度
	}
	
	pDC->SelectObject(pOldFont);
	m_LogList.ReleaseDC(pDC);
	
	m_LogList.SetHorizontalExtent(dx);			//设置水平滚动条的宽度
}


LRESULT CInterfaceDlg::DefWindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	// TODO: Add your specialized code here and/or call the base class
	if(message == 133)
	{
		if(bWindowShow == FALSE)
		{
			ShowWindow(SW_HIDE);
		}
		else
		{
			ShowWindow(SW_SHOW);
		}
	}
	
	return CDialog::DefWindowProc(message, wParam, lParam);
}


void CInterfaceDlg::OnMainProExAdmin()  // 更改权限
{
	// TODO: Add your control notification handler code here
	CExAdmin theExAdmin;
	theExAdmin.DoModal();
	if (bAdmin)  // 更改权限成功
	{
		m_CONTROLLER_bAdmin = _T("Admin");
		UpdateData(false);
	}
	else
	{	m_CONTROLLER_bAdmin = _T("Guest");
		UpdateData(false);
	}
}


//  程序复位，仅重启燃烧优化，并且将优化增缓慢变为0
void CInterfaceDlg::OnMainProReStart() 
{
	if (bAdmin)
	{
		if(MessageBox(_T("确定程序复位? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{

			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			CString LogFile(szPath);
			LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
			LogTime = CTime::GetCurrentTime();
			LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
			ofstream outLog(LogFile,ios::out|ios::app);

			LogSystem(outLog,_T("--------燃烧优化复位--------"));

			m_bCombOptState = _T("复位");
			UpdateData(FALSE);
			TerminateProcess(PI[1].pi.hProcess,1); // 强制关闭
			WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
			CloseHandle(PI[1].pi.hThread);
			CloseHandle(PI[1].pi.hProcess);

			// 重启燃烧优化
			// theComb.Init_Op_tag("param//Op.txt"); // 初始化状态以及模型参数
			// bReStart = TRUE;
			// SetTimer(1,1000,NULL);  // 开启Timer1，里面将优化增量重置为0
			// 启动燃烧优化进程 theComb.Op_tag[358]，等待直到该值变为1，如果该值已经为1，说明已经启动一个燃烧优化进程（这是不合理）
			if(!CreateProcess((LPSTR)(LPCTSTR)(PI[1].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
				{
					PI[1].bProStart = FALSE;
					LogSystem(outLog,_T("启动燃烧优化进程失败！"));
				}
			else
				{	PI[1].bProStart = TRUE;
					LogSystem(outLog,_T("启动燃烧优化进程！"));
				}
			/*		
			Sleep(8000);
			// 打开OP共享内存  pCombOptOP
			hCombOptOPMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("OPShareMem"));//打开CombOpt共享内存
			if(hCombOptOPMapFile == NULL)
			{
				LogSystem(outLog,_T("打开OP共享内存失败！"));
				SendMessage(WM_CLOSE);
			}
			
			pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
			if (pCombOptOP == NULL)
			{
				LogSystem(outLog,_T("打开OP共享内存映射文件失败 ！"));
				SendMessage(WM_CLOSE);
			}
			LogSystem(outLog,_T("打开OP共享内存成功！"));
			*/

			if (PI[1].bProStart == TRUE)  // 进程开始载入内存执行，接下来判断是否成功
			{
				CWait theWait(WaitCombOptStart);
				theWait.DoModal();
				if (WaitTime==0)
				{
					LogSystem(outLog,_T("燃烧优化进程启动成功！"));	
					PI[1].bProStart = TRUE;
					m_bCombOptState = _T("正常");
					bAllStart=TRUE; 
					UpdateData(FALSE);
				}
				else if (WaitTime==-1)
				{
					LogSystem(outLog,_T("等待时间过长，燃烧优化启动失败！"));
					PI[1].bProStart = FALSE;
					m_bCombOptState = _T("异常");
					UpdateData(FALSE);
				}
				else
				{
					LogSystem(outLog,_T("燃烧优化启动失败！"));
					PI[1].bProStart = FALSE;
					m_bCombOptState = _T("异常");
					UpdateData(FALSE);
				}
			}
			outLog.close();
		}
	}
	else
	{
		MessageBox(_T("没有权限！"),_T("Interface警告："),MB_ICONWARNING);
	}
}




void CInterfaceDlg::OnMainProCombOpt()  // 燃烧优化
{
	// TODO: Add your control notification handler code here
	if(bAdmin)
	{
		CombOpt theCombOpt;
	    theCombOpt.DoModal();

	}
	else
	{
		MessageBox(_T("没有权限！"),_T("Interface警告："),MB_ICONWARNING);
	}
}


void CInterfaceDlg::OnMainProExit() 
{

	// TODO: Add your control notification handler code here
	if(MessageBox(_T("确定退出? "),_T("Interface警告："),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		KillTimer(1);
		KillTimer(2);  // 监控进程
		// TODO: Add your message handler code here and/or call default
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
		LogSystem(outLog,_T("CombOpt程序退出中..."));	

		// 退出燃烧优化进程
		if(PI[1].pi.hProcess != INVALID_HANDLE_VALUE)
		{
			// 强制杀死进程语句
			//TerminateProcess(PI[1].pi.hProcess,1);
			//WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
			//CloseHandle(PI[1].pi.hThread);
			//CloseHandle(PI[1].pi.hProcess);
			//PI[1].pi.hThread = INVALID_HANDLE_VALUE;
			//PI[1].pi.hProcess = INVALID_HANDLE_VALUE;
			m_bCombOptState = _T("退出");
			UpdateData(FALSE);
			dp->pCombOptOP[358]=-1;  // 安全退出，完成最近一次计算
			CWait theWait(WaitCombOptStop);
			theWait.DoModal();
			if (WaitTime==-1)
			{
				LogSystem(outLog,_T("等待时间过长，燃烧优化退出失败！"));
				m_bCombOptState = _T("异常");
				UpdateData(FALSE);
				LogSystem(outLog,_T("强制杀死燃烧优化进程！"));
				TerminateProcess(PI[1].pi.hProcess,1);
				WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
				CloseHandle(PI[1].pi.hThread);
				CloseHandle(PI[1].pi.hProcess);
			}
		}
		LogSystem(outLog,_T("燃烧优化程序退出成功！"));

		// 退出通讯程序
		TerminateProcess(PI[0].pi.hProcess,1);
		WaitForSingleObject(PI[0].pi.hProcess,INFINITE);
		CloseHandle(PI[0].pi.hThread);
		CloseHandle(PI[0].pi.hProcess);
		LogSystem(outLog,_T("OPC通讯程序退出成功！"));
		outLog.close();
		SendMessage(WM_CLOSE);
	}

}

void CInterfaceDlg::OnClose() 
{
	// SIM_SX
	if (hReadShareMem)
	{
		CloseHandle(hReadShareMem);
		CloseHandle(hWriteShareMem);
	}

	KillTimer(1);
	KillTimer(2);  // 监控进程
	DeleteTray();
	CDialog::OnClose();

	if(pCombOptReadData)
	{
		UnmapViewOfFile(pCombOptReadData);
	}
	if(hOpenCombOptReadMapFile)
	{
		CloseHandle(hOpenCombOptReadMapFile);
	}
	
	if(pCombOptWriteData)
	{
		UnmapViewOfFile(pCombOptWriteData);
	}
	if(hOpenCombOptWriteMapFile)
	{
		CloseHandle(hOpenCombOptWriteMapFile);
	}
	if(pCombOptOP)
	{
		UnmapViewOfFile(pCombOptOP);
	}
	if(hCombOptOPMapFile)
	{
		CloseHandle(hCombOptOPMapFile);
	}
}


// 判断某进程是否正在运行
BOOL CInterfaceDlg::IsProccessRunning(CString strProccess) {
    BOOL BRunning = FALSE;
    PROCESSENTRY32 processEntry32;
    HANDLE toolHelp32Snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
    if (((int)toolHelp32Snapshot) != -1)
    {
        processEntry32.dwSize = sizeof(processEntry32);
        if (Process32First(toolHelp32Snapshot, &processEntry32))
        {
            do
            {

                CString str(L"");
                str = processEntry32.szExeFile;
                if (str == strProccess)
                {
                    BRunning = TRUE;
                    //MessageBox(_T("已启动一个程序！"),_T("AdvControl警告："),MB_ICONWARNING);
                    break;
                }
            }

            while (Process32Next(toolHelp32Snapshot, &processEntry32));
        }
        CloseHandle(toolHelp32Snapshot);
    }
    return BRunning;
}
