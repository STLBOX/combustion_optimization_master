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
	ON_MESSAGE(WM_TrayShow,OnTrayShow)  // ��ʼ��
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
    //  ���ùرհ�ť
    ASSERT(pSysMenu != NULL);
	pSysMenu->EnableMenuItem(SC_CLOSE,MF_DISABLED);

	// �ж�ĳ�����Ƿ���������
    CString ThisAPP = _T("CombOpt.exe");
    BOOL IsRunning = IsProccessRunning(ThisAPP);
	if (IsRunning)
	{
		MessageBox(_T("������һ������"),_T("AdvControl���棺"),MB_ICONWARNING);
		ExitProcess(0);
		return TRUE; 
	}

	// �����ڴ�����ָ��
	hReadShareMem = NULL;
	hWriteShareMem = NULL;
	hOpenCombOptReadMapFile = NULL;
	hOpenCombOptWriteMapFile = NULL;
	hCombOptOPMapFile = NULL;
	pCombOptReadData = NULL;
	pCombOptWriteData = NULL;
	pCombOptOP = NULL;

//	WindowShow = TRUE;
	bAllStart = TRUE;  // ����ʱ��δ�޸��߼�������Ϊtrue SIM_TEST
	bAdmin = FALSE;
	bReStart = FALSE;

//  mainsharemem
	NumPro = 3;
	pszProName[0] = "Interface.exe";
	pszProName[1] = "Interface.exe";
	pszProName[2] = "ProCombOpt.exe";

	dp = (CInterfaceDlg*) this;
    PI[0].pProName= _T("ProOPC.exe");  // д��pszProName�д洢����������Ϣ
	memset(&(PI[0].si),0,sizeof(STARTUPINFO));
	PI[0].si.cb = sizeof(STARTUPINFO);
	PI[0].iCount = 0;

	PI[1].pProName=_T("CombOpt.exe");
	memset(&(PI[1].si),0,sizeof(STARTUPINFO));
	PI[1].si.cb = sizeof(STARTUPINFO);
	PI[1].iCount = 0;

	WaitTime = 0; 
	MaxWaitTime = 500;  // 0.2sˢ��ʱ�䣬��ȴ�40s
    // ��������
	ToTray();
    // ����
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
	// ��������ͼ��
	NOTIFYICONDATA Nid;
    Nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA);
    Nid.hWnd = m_hWnd;
    Nid.uID = IDR_MAINFRAME;
    Nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP;
    Nid.uCallbackMessage = WM_TrayShow; // �Զ������̲˵���Ϣ
    Nid.hIcon = LoadIcon(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDR_MAINFRAME));
    strcpy(Nid.szTip, _T("�Ż�����"));
    Shell_NotifyIcon(NIM_ADD, &Nid); // �����������ͼ��
	//ShowWindow(SW_HIDE);
}

void CInterfaceDlg::DeleteTray()
{
	// ɾ������ͼ��
	NOTIFYICONDATA Nid;
	Nid.cbSize = (DWORD)sizeof(NOTIFYICONDATA); 
	Nid.hWnd = m_hWnd; 
	Nid.uID = IDR_MAINFRAME;
	Nid.uFlags = NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	Nid.uCallbackMessage = WM_TrayShow;//�Զ������Ϣ����
	Nid.hIcon = LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	strcpy(Nid.szTip,_T("�Ż�����")); //��Ϣ��ʾ��Ϊ"�ƻ���������"
	Shell_NotifyIcon(NIM_DELETE,&Nid); //��������ɾ��ͼ��
}


LRESULT CInterfaceDlg::OnTrayShow(WPARAM wParam, LPARAM lParam)
{
	//TODO: Add your message handle code
	if(wParam != IDR_MAINFRAME) // �ж�ͼ��ID�Ƿ����
        return 1;
    switch(lParam)
    {
	case WM_RBUTTONUP: 
        {// ������Ҽ�
            CPoint point;
            GetCursorPos(&point);
            CMenu menu;
            menu.CreatePopupMenu();
            menu.AppendMenu(MF_STRING, IDM_TrayShowWindow, _T("��ʾ����"));
            SetForegroundWindow();  // ����˵�ʧȥ���㲻��ʧ��BUG
            menu.TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);
            menu.DestroyMenu(); 
        }
        break;
    case WM_LBUTTONDBLCLK: // ˫��������
		bWindowShow = TRUE;
        ShowWindow(SW_SHOW);
        break;
    }
    return 0;
}


// ����������������
LRESULT CInterfaceDlg::OnProStart(WPARAM wParam, LPARAM lParam)
{
	TCHAR szPath[MAX_PATH];
	GetModuleFileName(NULL, szPath, MAX_PATH);
	CString LogFile(szPath);
	LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
	LogTime = CTime::GetCurrentTime();
	LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
	ofstream outLog(LogFile,ios::out|ios::app);
	LogSystem(outLog,_T("--------��������--------"));

	 // ���������ڴ棨�ⲿ����ͨѶ����ɣ���XTReadShareMem��XTWriteShareMem  SIM_SX
	hReadShareMem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,READ_NUM*sizeof(double),_T("XTReadShareMem"));
	if(hReadShareMem == NULL)
	{
	    LogSystem(outLog,_T("����ReadShareMem�����ڴ�ʧ�ܣ�"));
		SendMessage(WM_CLOSE);
		return 6;
	}

	hWriteShareMem = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,WRITE_NUM*sizeof(double),_T("XTWriteShareMem"));
	if(hWriteShareMem == NULL)
	{
	    LogSystem(outLog,_T("����WriteShareMem�����ڴ�ʧ�ܣ�"));
		SendMessage(WM_CLOSE);
		return 6;
	}


	// ��OPC�������ڴ� pCombOptReadData
	hOpenCombOptReadMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTReadShareMem")); 	
	if(hOpenCombOptReadMapFile == NULL)
	{
		LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ʧ�ܣ�"));
		SendMessage(WM_CLOSE);
		return 5;
	}
	pCombOptReadData = (double*)MapViewOfFile(hOpenCombOptReadMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptReadData == NULL)
	{
		LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ӳ���ļ�ʧ�� ��"));
		SendMessage(WM_CLOSE);
		return 6;
    }
	LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ɹ���"));


	// ��OPCд�����ڴ� pCombOptWriteData
	hOpenCombOptWriteMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTWriteShareMem")); 
	if(hOpenCombOptWriteMapFile == NULL)
	{
		LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ʧ�ܣ�"));
		SendMessage(WM_CLOSE);
		return 5;
	}
	pCombOptWriteData = (double*)MapViewOfFile(hOpenCombOptWriteMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptWriteData == NULL)
	{
		LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ӳ���ļ�ʧ�� ��"));
		SendMessage(WM_CLOSE);
		return 6;
    }
	LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ɹ���"));


	// ����OP�����ڴ棬�������ģ�Ͳ�����һЩ��ʾ������  Comb_OpN 371
	hCombOptOPMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,Comb_OpN*sizeof(double),_T("OPShareMem")); //����Comb�����ڴ�
	if(hWriteShareMem == NULL)
	{
	    LogSystem(outLog,_T("����OP�����ڴ�ʧ�ܣ�"));
		SendMessage(WM_CLOSE);
		return 6;
	}
	// ��OP�����ڴ�
	pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	if (pCombOptOP == NULL)
	{
		LogSystem(outLog,_T("��OP�����ڴ�ӳ���ļ�ʧ�� ��"));
		SendMessage(WM_CLOSE);
	}
	LogSystem(outLog,_T("��OP�����ڴ�ɹ���"));


	// ����MainshareMem,����OPC��ʹ�õ�
	hMainMapFile = CreateFileMapping(INVALID_HANDLE_VALUE,NULL,PAGE_READWRITE,0,(NumPro+1)*sizeof(CMainShareMem),_T("MyMainShareMem"));
	if(hMainMapFile)
	{
		pMainMem = (CMainShareMem*)MapViewOfFile(hMainMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
	}
	if(hMainMapFile == NULL||pMainMem == NULL)
	{
		LogSystem(outLog,_T("����MainPro�����ڴ�ʧ�ܣ�"));
		MessageBox(_T("����MainPro�����ڴ�ʧ�ܣ�"),_T("���棺"),MB_ICONWARNING);
		SendMessage(WM_CLOSE);
		return 2;
	}


	else
	{
		LogSystem(outLog,_T("����MainPro�����ڴ�ɹ���"));
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
    // ����interfaceǰ ��Ҫ����ͨѶ����CombOpt
	// �ж� OPC�Ƿ���
    BOOL IsRunning = IsProccessRunning(PI[0].pProName);
	if (!IsRunning)
	{
		if(!CreateProcess((LPSTR)(LPCTSTR)(PI[0].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[0].si),&(PI[0].pi)))
		{
			PI[0].bProStart = false;
			LogSystem(outLog,_T("����ͨѶ����ʧ�ܣ�"));
			m_bOPCState = _T("�쳣");
		}
		else
		{
			PI[0].bProStart = true;
			LogSystem(outLog,_T("����ͨѶ����ɹ���"));
			m_bOPCState = _T("����");
		}
	}
	else
	{
		LogSystem(outLog,_T("����ͨѶ����ɹ���"));
		m_bOPCState = _T("����");
	}
    UpdateData(FALSE);

	if (PI[0].bProStart == FALSE)  // ʧ��ֱ��return
	{   
		outLog.close();
		SendMessage(WM_CLOSE);
		return 0;
	}
	// theComb.MapToTag();  // ����Tag��IO_tag Op_tag ֱ��ʹ��
    // theComb.Init_Op_tag("param//Op.txt");  // �����ݿ���Op������ʼ������ֹ����ֵ��Ӱ��״̬��ʾ

	Sleep(5000);  // �ȴ������ڴ洴����ϣ����

    LogSystem(outLog,_T("--------����ȼ���Ż�--------"));
	// ����ȼ���Ż����� theComb.Op_tag[358]���ȴ�ֱ����ֵ��Ϊ1�������ֵ�Ѿ�Ϊ1��˵���Ѿ�����һ��ȼ���Ż����̣����ǲ�����
	if(!CreateProcess((LPSTR)(LPCTSTR)(PI[1].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
		{
			PI[1].bProStart = FALSE;
			LogSystem(outLog,_T("����ȼ���Ż�����ʧ�ܣ�"));
		}
	else
		{	
			PI[1].bProStart = TRUE;
			LogSystem(outLog,_T("����ȼ���Ż����̣�"));
		}
	if (PI[1].bProStart == FALSE)  // ʧ��ֱ��return
	{   
		outLog.close();
		SendMessage(WM_CLOSE);
		return 0;
	}

	// Sleep(8000); // �ȴ�8s�ȴ�ȼ���Ż����̴����ù����ڴ�

    if (PI[1].bProStart == TRUE)  // ���̿�ʼ�����ڴ�ִ�У��������ж��Ƿ�ɹ�
	{
		CWait theWait(WaitCombOptStart);
		theWait.DoModal();
		if (WaitTime==0)
		{
			LogSystem(outLog,_T("ȼ���Ż����������ɹ���"));	
			PI[1].bProStart = TRUE;
			m_bCombOptState = _T("����");
			bAllStart=TRUE; 
			UpdateData(FALSE);
		}
		else if (WaitTime==-1)
		{
			LogSystem(outLog,_T("�ȴ�ʱ�������ȼ���Ż�����ʧ�ܣ�"));
			PI[1].bProStart = FALSE;
			m_bCombOptState = _T("�쳣");
			UpdateData(FALSE);
		}
		else
		{
			LogSystem(outLog,_T("ȼ���Ż�����ʧ�ܣ�"));
			PI[1].bProStart = FALSE;
			m_bCombOptState = _T("�쳣");
			UpdateData(FALSE);
		}
	}
		
	outLog.close();
	SetTimer(2,20000,NULL);  // �򿪶�ʱ�������н��̼��
	return 0;
}


void CInterfaceDlg::OnTimer(UINT nIDEvent) 
{	
    switch(nIDEvent)
	{
		case 1 :
		{
			// ���Ż�������Ϊ0������Ǹ�λ״̬
			if (bReStart)
			{  	
				for (int i=0;i<=5;i++)  // ��ú��
				{
					pCombOptWriteData[2+i] = 0;
				}

				for ( i=0;i<=15;i++)  // ���η�andȼ����
				{	
					pCombOptWriteData[8+i] = 0;
				}
				pCombOptWriteData[24] = 0 ;
				pCombOptWriteData[25] = 0 ;
			    bReStart = false;
			}
			
			// Ontimer �н�ִ��һ�� ��ʼ����ɺ�ر�Ontimer1
			if (int(pCombOptOP[358])==2)
			{
				m_LogList.InsertString(m_LogList.GetCount(),LogTime.Format("%H:%M:%S ")+_T("ȼ���Ż���ʼ����ɣ�"));
				SetListBoxSPGD();
				m_LogList.SetCurSel(m_LogList.GetCount() - 1);
				KillTimer(1);  // ��ʼ����ɺ󣬹ر�
				bReStart = FALSE;
			}
            break;
		}
		
		case 2:  // ���ڽ��̼�أ����CombOpt��OptCtrl
		{
			//  �ȼ���Ƿ���Ҫ�������ݿ⣬���ݿ��������Ϊ1s
			//  bool DataBaseNormal=TRUE;
			BOOL IsRunning = IsProccessRunning(PI[0].pProName);  // �ж�
			if (!IsRunning)
			{
				KillTimer(2);  // ��ͣ��ʱ��
				TCHAR szPath[MAX_PATH];
				GetModuleFileName(NULL, szPath, MAX_PATH);
				CString LogFile(szPath);
				LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
				LogTime = CTime::GetCurrentTime();
				LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
				ofstream outLog(LogFile,ios::out|ios::app);
				LogSystem(outLog,_T("OPCͨѶ�쳣�رգ�"));

				if(CreateProcess((LPSTR)(LPCTSTR)PI[0].pProName,NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[0].si),&(PI[0].pi)))
				{	
					PI[0].bProStart = TRUE;
					LogSystem(outLog,_T("����OPC�ɹ���"));
					PI[0].iCount = 0;

					Sleep(8000); 
					// ��OPC�������ڴ� pCombOptReadData
					hOpenCombOptReadMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTReadShareMem")); 	
					if(hOpenCombOptReadMapFile == NULL)
					{
						LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ʧ�ܣ�"));
						SendMessage(WM_CLOSE);
					}
					pCombOptReadData = (double*)MapViewOfFile(hOpenCombOptReadMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
					if (pCombOptReadData == NULL)
					{
						LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ӳ���ļ�ʧ�� ��"));
						SendMessage(WM_CLOSE);
					}
					LogSystem(outLog,_T("interface��ProCombOpt(READ)�����ڴ�ɹ���"));

					// ��OPCд�����ڴ� pCombOptWriteData
					hOpenCombOptWriteMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("XTWriteShareMem")); 
					if(hOpenCombOptWriteMapFile == NULL)
					{
						LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ʧ�ܣ�"));
						SendMessage(WM_CLOSE);
					}
					pCombOptWriteData = (double*)MapViewOfFile(hOpenCombOptWriteMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
					if (pCombOptWriteData == NULL)
					{
						LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ӳ���ļ�ʧ�� ��"));
						SendMessage(WM_CLOSE);
					}
					LogSystem(outLog,_T("interface��ProCombOpt(WRITE)�����ڴ�ɹ���"));

					/// DataBaseNormal = TRUE;
				}
				else
				{
					// DataBaseNormal = FALSE;  // ����ʧ��
					PI[0].bProStart = FALSE;
					LogSystem(outLog,_T("����OPCʧ�ܣ�"));
					PI[0].iCount++;
				}

				if (PI[0].iCount >= 2)  // ��������2��ʧ�ܣ�ɱ����ʱ������������
				{
					KillTimer(2);
					break;
				}
				SetTimer(2,20000,NULL);  // �ؿ���ʱ��
				outLog.close();	
			}

			//  ���CombOpt�˳�����ô����CombOpt
			int HeartBeatk1;
			HeartBeatk1 = int(pCombOptWriteData[100]);
			Sleep(4100);  // ˯��4.1s ��ʱ����Ӧ��Ϊ0
			if (int(pCombOptWriteData[100]) == HeartBeatk1)  // ��������ǰ�����
			{   
				BOOL IsRunning = IsProccessRunning(PI[1].pProName);  // �ٴ��ж�
				if (!IsRunning)
				{	
					KillTimer(2);  // ��ͣ��ʱ��
					TCHAR szPath[MAX_PATH];
					GetModuleFileName(NULL, szPath, MAX_PATH);
					CString LogFile(szPath);
					LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
					LogTime = CTime::GetCurrentTime();
					LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
					ofstream outLog(LogFile,ios::out|ios::app);
					LogSystem(outLog,_T("ȼ���Ż����˳���"));
					// ����ȼ���Ż�
					if(CreateProcess((LPSTR)(LPCTSTR)PI[1].pProName,NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
					{	
						PI[1].bProStart = TRUE;
						LogSystem(outLog,_T("����ȼ���Ż���"));
						PI[1].iCount = 0;
						/*
						// Sleep(8000);
						// ��OP�����ڴ�  pCombOptOP
						hCombOptOPMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("OPShareMem"));//��CombOpt�����ڴ�
						if(hCombOptOPMapFile == NULL)
						{
							LogSystem(outLog,_T("��OP�����ڴ�ʧ�ܣ�"));
							SendMessage(WM_CLOSE);
						}
						
						pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
						if (pCombOptOP == NULL)
						{
							LogSystem(outLog,_T("��OP�����ڴ�ӳ���ļ�ʧ�� ��"));
							SendMessage(WM_CLOSE);
						}
						LogSystem(outLog,_T("��OP�����ڴ�ɹ���"));
						*/

					}
					else
					{
						PI[1].bProStart = TRUE;
						LogSystem(outLog,_T("����ȼ���Ż�ʧ�ܣ�"));
					}

                    // theComb.Init_Op_tag("param/Op.txt");  // ��ֹWait�д����ж�
					// ���̿�ʼ�����ڴ�ִ�У��������ж��Ƿ�ɹ�
					if (PI[1].bProStart == TRUE) 
					{
						CWait theWait(WaitCombOptStart);
						theWait.DoModal();
						if (WaitTime==0)
						{
							LogSystem(outLog,_T("ȼ���Ż����������ɹ���"));	
							PI[1].bProStart = TRUE;
							m_bCombOptState = _T("����");
							bAllStart=TRUE; 
							UpdateData(FALSE);
							PI[1].iCount = 0;
						}
						else if (WaitTime==-1)
						{
							LogSystem(outLog,_T("�ȴ�ʱ�������ȼ���Ż�����ʧ�ܣ�"));
							PI[1].bProStart = FALSE;
							m_bCombOptState = _T("�쳣");
							UpdateData(FALSE);
							PI[1].iCount++;
						}
						else
						{
							LogSystem(outLog,_T("ȼ���Ż�����ʧ�ܣ�"));
							PI[1].bProStart = FALSE;
							m_bCombOptState = _T("�쳣");
							UpdateData(FALSE);
							PI[1].iCount++;
						}
					}
					else
					{
						PI[1].bProStart = FALSE;
						m_bCombOptState = _T("�쳣");
						UpdateData(FALSE);
						PI[1].iCount++;
					}
					if (PI[1].iCount >= 2)  // ��������2��ʧ�ܣ�ɱ����ʱ������������
					{
						KillTimer(2);
						break;
					}
					SetTimer(2,20000,NULL);  // �ؿ���ʱ��
					outLog.close();	
				}  // KillTimer
			
			}  // 

			//  ������ʾ
		 	if(m_LogList.GetCount() > 50)
			{
				int tCount = m_LogList.GetCount() - 50;
				for(int i = 0;i < tCount; i++)
				{
					m_LogList.DeleteString(0);
				}
				m_LogList.SetCurSel(m_LogList.GetCount() - 1);
			}

			// ��CombOpt����״̬���
			if (int(pCombOptOP[358])>=1)
			{
				m_bCombOptState = _T("����");
			}
			else if (int(pCombOptOP[358])==-1)
			{
				m_bCombOptState = _T("�쳣");
				bAllStart=FALSE; 
			}
			else
			{
				m_bCombOptState = _T("");
			}

			// ��CombOpt����״̬���
			if (int(pCombOptOP[363])==0)
			{
				m_bOPCState = _T("����");
			}
			else if (int(pCombOptOP[363])==-1)
			{
				m_bOPCState = _T("�쳣");
				bAllStart=FALSE; 
				KillTimer(2);
				// ɱ��CombOpt �� ͨ��
				m_bCombOptState = _T("�˳�");
			    TerminateProcess(PI[1].pi.hProcess,1); // ǿ�ƹر�CombOpt
				WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
				CloseHandle(PI[1].pi.hThread);
				CloseHandle(PI[1].pi.hProcess);

				TerminateProcess(PI[0].pi.hProcess,1); // ǿ�ƹر�OPTCtrlCon
				WaitForSingleObject(PI[0].pi.hProcess,INFINITE);
				CloseHandle(PI[0].pi.hThread);
				CloseHandle(PI[0].pi.hProcess);
				Sleep(3000);
				SetTimer(2,20000,NULL);  // �ؿ���ʱ��
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


//---------------��־
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
	//����ˮƽ����
	CString str;								//����б��ÿһ����ַ���
	CSize sz;									//����ַ����ĳ��ȣ���ź���GetTextExtent�ķ���ֵ
	int dx = 0;									//������ĳ���
	TEXTMETRIC tm;								//����ṹ���������Ҫ�ǻ�õ�ǰ�������ַ���ƽ������
	CDC* pDC = m_LogList.GetDC();
	
	CFont* pFont = m_LogList.GetFont();			//����б�������õ�����
	CFont* pOldFont = pDC->SelectObject(pFont);
	
	pDC->GetTextMetrics(&tm);					//�õ��ַ���ƽ������
	
	for (int i = 0; i < m_LogList.GetCount(); i++)
	{
		m_LogList.GetText(i, str);
		sz = pDC->GetTextExtent(str);
		sz.cx += tm.tmAveCharWidth;				//��һ��������˼���������ƽ�����ȣ��ᵼ�����һ���ַ����ü���
		if (sz.cx > dx)
			dx = sz.cx;							//ֻȡ����ĳ���
	}
	
	pDC->SelectObject(pOldFont);
	m_LogList.ReleaseDC(pDC);
	
	m_LogList.SetHorizontalExtent(dx);			//����ˮƽ�������Ŀ��
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


void CInterfaceDlg::OnMainProExAdmin()  // ����Ȩ��
{
	// TODO: Add your control notification handler code here
	CExAdmin theExAdmin;
	theExAdmin.DoModal();
	if (bAdmin)  // ����Ȩ�޳ɹ�
	{
		m_CONTROLLER_bAdmin = _T("Admin");
		UpdateData(false);
	}
	else
	{	m_CONTROLLER_bAdmin = _T("Guest");
		UpdateData(false);
	}
}


//  ����λ��������ȼ���Ż������ҽ��Ż���������Ϊ0
void CInterfaceDlg::OnMainProReStart() 
{
	if (bAdmin)
	{
		if(MessageBox(_T("ȷ������λ? "),_T("Interface���棺"),MB_ICONQUESTION|MB_YESNO)==IDYES)
		{

			TCHAR szPath[MAX_PATH];
			GetModuleFileName(NULL, szPath, MAX_PATH);
			CString LogFile(szPath);
			LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
			LogTime = CTime::GetCurrentTime();
			LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
			ofstream outLog(LogFile,ios::out|ios::app);

			LogSystem(outLog,_T("--------ȼ���Ż���λ--------"));

			m_bCombOptState = _T("��λ");
			UpdateData(FALSE);
			TerminateProcess(PI[1].pi.hProcess,1); // ǿ�ƹر�
			WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
			CloseHandle(PI[1].pi.hThread);
			CloseHandle(PI[1].pi.hProcess);

			// ����ȼ���Ż�
			// theComb.Init_Op_tag("param//Op.txt"); // ��ʼ��״̬�Լ�ģ�Ͳ���
			// bReStart = TRUE;
			// SetTimer(1,1000,NULL);  // ����Timer1�����潫�Ż���������Ϊ0
			// ����ȼ���Ż����� theComb.Op_tag[358]���ȴ�ֱ����ֵ��Ϊ1�������ֵ�Ѿ�Ϊ1��˵���Ѿ�����һ��ȼ���Ż����̣����ǲ�����
			if(!CreateProcess((LPSTR)(LPCTSTR)(PI[1].pProName),NULL,NULL,NULL,FALSE,HIGH_PRIORITY_CLASS,NULL,NULL,&(PI[1].si),&(PI[1].pi)))
				{
					PI[1].bProStart = FALSE;
					LogSystem(outLog,_T("����ȼ���Ż�����ʧ�ܣ�"));
				}
			else
				{	PI[1].bProStart = TRUE;
					LogSystem(outLog,_T("����ȼ���Ż����̣�"));
				}
			/*		
			Sleep(8000);
			// ��OP�����ڴ�  pCombOptOP
			hCombOptOPMapFile = OpenFileMapping(FILE_MAP_READ|FILE_MAP_WRITE,FALSE,_T("OPShareMem"));//��CombOpt�����ڴ�
			if(hCombOptOPMapFile == NULL)
			{
				LogSystem(outLog,_T("��OP�����ڴ�ʧ�ܣ�"));
				SendMessage(WM_CLOSE);
			}
			
			pCombOptOP = (double*)MapViewOfFile(hCombOptOPMapFile,FILE_MAP_READ|FILE_MAP_WRITE,0,0,0);
			if (pCombOptOP == NULL)
			{
				LogSystem(outLog,_T("��OP�����ڴ�ӳ���ļ�ʧ�� ��"));
				SendMessage(WM_CLOSE);
			}
			LogSystem(outLog,_T("��OP�����ڴ�ɹ���"));
			*/

			if (PI[1].bProStart == TRUE)  // ���̿�ʼ�����ڴ�ִ�У��������ж��Ƿ�ɹ�
			{
				CWait theWait(WaitCombOptStart);
				theWait.DoModal();
				if (WaitTime==0)
				{
					LogSystem(outLog,_T("ȼ���Ż����������ɹ���"));	
					PI[1].bProStart = TRUE;
					m_bCombOptState = _T("����");
					bAllStart=TRUE; 
					UpdateData(FALSE);
				}
				else if (WaitTime==-1)
				{
					LogSystem(outLog,_T("�ȴ�ʱ�������ȼ���Ż�����ʧ�ܣ�"));
					PI[1].bProStart = FALSE;
					m_bCombOptState = _T("�쳣");
					UpdateData(FALSE);
				}
				else
				{
					LogSystem(outLog,_T("ȼ���Ż�����ʧ�ܣ�"));
					PI[1].bProStart = FALSE;
					m_bCombOptState = _T("�쳣");
					UpdateData(FALSE);
				}
			}
			outLog.close();
		}
	}
	else
	{
		MessageBox(_T("û��Ȩ�ޣ�"),_T("Interface���棺"),MB_ICONWARNING);
	}
}




void CInterfaceDlg::OnMainProCombOpt()  // ȼ���Ż�
{
	// TODO: Add your control notification handler code here
	if(bAdmin)
	{
		CombOpt theCombOpt;
	    theCombOpt.DoModal();

	}
	else
	{
		MessageBox(_T("û��Ȩ�ޣ�"),_T("Interface���棺"),MB_ICONWARNING);
	}
}


void CInterfaceDlg::OnMainProExit() 
{

	// TODO: Add your control notification handler code here
	if(MessageBox(_T("ȷ���˳�? "),_T("Interface���棺"),MB_ICONQUESTION|MB_YESNO)==IDYES)
	{
		KillTimer(1);
		KillTimer(2);  // ��ؽ���
		// TODO: Add your message handler code here and/or call default
		TCHAR szPath[MAX_PATH];
		GetModuleFileName(NULL, szPath, MAX_PATH);
		CString LogFile(szPath);
		LogFile = LogFile.Left(LogFile.ReverseFind(_T('\\')) + 1);
		LogTime = CTime::GetCurrentTime();
		LogFile = LogFile+LogTime.Format("Log\\%Y%m%dInterface.log");
		ofstream outLog(LogFile,ios::out|ios::app);
		LogSystem(outLog,_T("CombOpt�����˳���..."));	

		// �˳�ȼ���Ż�����
		if(PI[1].pi.hProcess != INVALID_HANDLE_VALUE)
		{
			// ǿ��ɱ���������
			//TerminateProcess(PI[1].pi.hProcess,1);
			//WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
			//CloseHandle(PI[1].pi.hThread);
			//CloseHandle(PI[1].pi.hProcess);
			//PI[1].pi.hThread = INVALID_HANDLE_VALUE;
			//PI[1].pi.hProcess = INVALID_HANDLE_VALUE;
			m_bCombOptState = _T("�˳�");
			UpdateData(FALSE);
			dp->pCombOptOP[358]=-1;  // ��ȫ�˳���������һ�μ���
			CWait theWait(WaitCombOptStop);
			theWait.DoModal();
			if (WaitTime==-1)
			{
				LogSystem(outLog,_T("�ȴ�ʱ�������ȼ���Ż��˳�ʧ�ܣ�"));
				m_bCombOptState = _T("�쳣");
				UpdateData(FALSE);
				LogSystem(outLog,_T("ǿ��ɱ��ȼ���Ż����̣�"));
				TerminateProcess(PI[1].pi.hProcess,1);
				WaitForSingleObject(PI[1].pi.hProcess,INFINITE);
				CloseHandle(PI[1].pi.hThread);
				CloseHandle(PI[1].pi.hProcess);
			}
		}
		LogSystem(outLog,_T("ȼ���Ż������˳��ɹ���"));

		// �˳�ͨѶ����
		TerminateProcess(PI[0].pi.hProcess,1);
		WaitForSingleObject(PI[0].pi.hProcess,INFINITE);
		CloseHandle(PI[0].pi.hThread);
		CloseHandle(PI[0].pi.hProcess);
		LogSystem(outLog,_T("OPCͨѶ�����˳��ɹ���"));
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
	KillTimer(2);  // ��ؽ���
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


// �ж�ĳ�����Ƿ���������
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
                    //MessageBox(_T("������һ������"),_T("AdvControl���棺"),MB_ICONWARNING);
                    break;
                }
            }

            while (Process32Next(toolHelp32Snapshot, &processEntry32));
        }
        CloseHandle(toolHelp32Snapshot);
    }
    return BRunning;
}
