
// DlgMain.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgMain.h"
#include "afxdialogex.h"
#include "ModbusHelp.h"
#include "SQLiteHelp.h"
#include "ParamHelp.h"
#include "WorkFunc.h"
#include "WorkPool.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CDlgMain 对话框




CDlgMain::CDlgMain(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgMain::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CDlgMain::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_TAB1, m_wndTab);
	DDX_Control(pDX, IDC_LIST_LOG, m_listLog);
}

BEGIN_MESSAGE_MAP(CDlgMain, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_MESSAGE(WM_CX_LOG, &CDlgMain::OnLog)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB1, &CDlgMain::OnTcnSelchangeTab1)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_BTN_RUN, &CDlgMain::OnBnClickedBtnRun)
	ON_BN_CLICKED(IDC_BTN_STOP, &CDlgMain::OnBnClickedBtnStop)
END_MESSAGE_MAP()


// CDlgMain 消息处理程序

BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	InitLogList();

	InitSys();

	CreateChildWnd();
	OnSwitchWnd(0, WND_MONITOR);

	
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CDlgMain::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CDlgMain::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CDlgMain::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void	CDlgMain::Run()
{
	BOOL bRtn = FALSE;
	int nStep = CWorkFunc::m_nWorkStep;

	switch (nStep)
	{
	case 0:
		bRtn = CWorkFunc::Idel();
		break;
	case 10:		// 自动运行参数初始化	
		bRtn = CWorkFunc::Start();
		CWorkFunc::m_nWorkStep = bRtn ? 20:600;		
		break;
	case 20:		// 自动运行条件检测		
		bRtn = CWorkFunc::ReadyWork();	
		CWorkFunc::m_nWorkStep = bRtn ? 30 : 600;
		break;
	case 30:		// 等待间隔时间	
		bRtn = CWorkFunc::WaitWork();	
		CWorkFunc::m_nWorkStep = bRtn ? 40 : 600;
		break;
	case 40:		// 读取数据
		bRtn = CWorkFunc::ReadData();
		CWorkFunc::m_nWorkStep = bRtn ? 50 : 600;
		break;
	case 50:		// 更新温湿度图
		bRtn = CWorkFunc::UpdateView();
		bRtn ? (CWorkFunc::m_nWorkStep = 30) : (CWorkFunc::m_nWorkStep = 0);
		break;
	case 600:		// 报警
		bRtn = CWorkFunc::Alarm();
		bRtn ? (CWorkFunc::m_nWorkStep = 0) : (CWorkFunc::m_nWorkStep = 0);
		break;
	default:
		break;
	}
}

BOOL	CDlgMain::InitSys()			// 初始化所有资源
{
	BOOL bRtn = FALSE;

	LOG(_T("加载系统参数"));
	CHParam->Refresh();

	CString strDbPath = CHGetExeDirPath() + _T("database.db");
	bRtn = CHSQLite->Open(strDbPath);
	if (!bRtn)
	{
		LOG_ERR(_T("打开数据库失败"));
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	bRtn = CHModbus->Init(CHParam->m_nPort, CHParam->m_nBaud, CHParam->m_nParity, CHParam->m_nDataBits, CHParam->m_nStopBits);				// 串口初始化
	if (!bRtn)
	{
		LOG_ERR(_T("串口初始化失败"));		
		return FALSE;
	}
	CHModbus->m_bInit = TRUE;
	LOG(_T("串口初始化完成"));
	return TRUE;
}


BOOL CDlgMain::CloseSys()
{
	BOOL bRtn = FALSE;

	CHSQLite->Close();
	//////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////

	return TRUE;
}


BOOL CDlgMain::InitLogList()
{

	m_ImageList.Create(16, 16, ILC_COLOR24 | ILC_MASK, 4, 4);
	m_ImageList.Add(LoadIcon(NULL, IDI_INFORMATION));
	m_ImageList.Add(LoadIcon(NULL, IDI_WARNING));
	m_ImageList.Add(LoadIcon(NULL, IDI_ERROR));
	m_ImageList.Add(LoadIcon(NULL, IDI_ERROR));
	m_ImageList.Add(LoadIcon(NULL, IDI_EXCLAMATION));

	struct ListInitData
	{
		TCHAR szTitle[64];
		int iWidth;
	};

	ListInitData InitData[] =
	{
		{ _T("序号"), 90 },
		{ _T("时间戳"), 165 },
		{ _T("内容"), 1200 }
	};

	m_listLog.SetImageList(&m_ImageList, LVSIL_SMALL);
	m_listLog.SetExtendedStyle(m_listLog.GetExtendedStyle() | LVS_EX_FULLROWSELECT);
	for (int i = 0; i<sizeof(InitData) / sizeof(ListInitData); i++)
		m_listLog.InsertColumn(i, InitData[i].szTitle, LVCFMT_LEFT, InitData[i].iWidth);

	CxLog::Instance().SetWnd(m_hWnd);

	return TRUE;
}


LRESULT CDlgMain::OnLog(WPARAM wParam, LPARAM lParam)
{
	static DWORD uCount = 0;
	uCount++;
	CxLog::Item * pItem = (CxLog::Item *)lParam;
	ASSERT(pItem);

	if (!pItem)
		return 0UL;

	CString Str;
	Str.Format(_T("%08d"), uCount);
	m_listLog.InsertItem(0, Str, pItem->_eType);
	m_listLog.SetItemText(0, 1, pItem->_szTime);
	m_listLog.SetItemText(0, 2, pItem->_szDesc);
	delete pItem;

	if (m_listLog.GetItemCount() > 15000)
		m_listLog.DeleteItem(m_listLog.GetItemCount() - 1);

	return 1UL;
}

void CDlgMain::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	
}


BOOL	CDlgMain::CreateChildWnd()
{

	m_wndTab.InsertItem(0, _T("主界面"));
	m_wndTab.InsertItem(1, _T("数据查看"));	
	m_wndTab.InsertItem(2, _T("参数设置"));	
	m_wndTab.SetItemSize(CSize(50, 35));

	CRect rect;

	m_wndTab.GetWindowRect(rect);
	ScreenToClient(rect);
	rect.left -= 6;
	rect.top += 30;
	rect.right -= 20;
	rect.bottom -= 20;

	m_wndView.Create(CDlgView::IDD, &m_wndTab);
	m_wndView.MoveWindow(rect);
	m_wndDatabase.Create(CDlgDatabase::IDD, &m_wndTab);
	m_wndDatabase.MoveWindow(rect);
	m_wndParam.Create(CDlgParam::IDD, &m_wndTab);
	m_wndParam.MoveWindow(rect);

	return TRUE;
}

LRESULT CDlgMain::OnSwitchWnd(WPARAM wParam, LPARAM lParam)
{
	long lWindows = lParam;

	switch (lWindows)
	{
	case WND_MONITOR:
		m_wndView.ShowWindow(SW_SHOW);
		m_wndView.RedrawWindow();
		m_wndDatabase.ShowWindow(SW_HIDE);
		m_wndParam.ShowWindow(SW_HIDE);
		break;

	case WND_DATABASE:
		m_wndView.ShowWindow(SW_HIDE);
		m_wndParam.ShowWindow(SW_HIDE);
		m_wndDatabase.ShowWindow(SW_SHOW);		
	
		break;	
	case WND_PARAM:
		m_wndView.ShowWindow(SW_HIDE);
		m_wndDatabase.ShowWindow(SW_HIDE);
		m_wndParam.ShowWindow(SW_SHOW);
		break;
	default:
		break;
	}

	return 0;
}

void CDlgMain::OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO:  在此添加控件通知处理程序代码
	*pResult = 0;
	INT nTab = m_wndTab.GetCurSel();
	OnSwitchWnd(0, nTab);
}


void CDlgMain::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	CloseSys();
	CDialogEx::OnClose();
}


void CDlgMain::OnBnClickedBtnRun()
{
	// TODO:  在此添加控件通知处理程序代码
	if (!CHWorkPool->IsCreate())
	{
		CHWorkPool->Start(this);
		LOG(_T("开始监控"));
		CWorkFunc::m_nWorkStep = 10;
		GetDlgItem(IDC_BTN_RUN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	}
}


void CDlgMain::OnBnClickedBtnStop()
{
	// TODO:  在此添加控件通知处理程序代码
	if (CHWorkPool->IsCreate())
	{
		CHWorkPool->Stop();
		GetDlgItem(IDC_BTN_RUN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
		LOG(_T("停止监控"));
	}
}
