
// DlgMain.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CDlgMain �Ի���




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


// CDlgMain ��Ϣ�������

BOOL CDlgMain::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	InitLogList();

	InitSys();

	CreateChildWnd();
	OnSwitchWnd(0, WND_MONITOR);

	
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CDlgMain::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
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
	case 10:		// �Զ����в�����ʼ��	
		bRtn = CWorkFunc::Start();
		CWorkFunc::m_nWorkStep = bRtn ? 20:600;		
		break;
	case 20:		// �Զ������������		
		bRtn = CWorkFunc::ReadyWork();	
		CWorkFunc::m_nWorkStep = bRtn ? 30 : 600;
		break;
	case 30:		// �ȴ����ʱ��	
		bRtn = CWorkFunc::WaitWork();	
		CWorkFunc::m_nWorkStep = bRtn ? 40 : 600;
		break;
	case 40:		// ��ȡ����
		bRtn = CWorkFunc::ReadData();
		CWorkFunc::m_nWorkStep = bRtn ? 50 : 600;
		break;
	case 50:		// ������ʪ��ͼ
		bRtn = CWorkFunc::UpdateView();
		bRtn ? (CWorkFunc::m_nWorkStep = 30) : (CWorkFunc::m_nWorkStep = 0);
		break;
	case 600:		// ����
		bRtn = CWorkFunc::Alarm();
		bRtn ? (CWorkFunc::m_nWorkStep = 0) : (CWorkFunc::m_nWorkStep = 0);
		break;
	default:
		break;
	}
}

BOOL	CDlgMain::InitSys()			// ��ʼ��������Դ
{
	BOOL bRtn = FALSE;

	LOG(_T("����ϵͳ����"));
	CHParam->Refresh();

	CString strDbPath = CHGetExeDirPath() + _T("database.db");
	bRtn = CHSQLite->Open(strDbPath);
	if (!bRtn)
	{
		LOG_ERR(_T("�����ݿ�ʧ��"));
		return FALSE;
	}

	//////////////////////////////////////////////////////////////////////////
	bRtn = CHModbus->Init(CHParam->m_nPort, CHParam->m_nBaud, CHParam->m_nParity, CHParam->m_nDataBits, CHParam->m_nStopBits);				// ���ڳ�ʼ��
	if (!bRtn)
	{
		LOG_ERR(_T("���ڳ�ʼ��ʧ��"));		
		return FALSE;
	}
	CHModbus->m_bInit = TRUE;
	LOG(_T("���ڳ�ʼ�����"));
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
		{ _T("���"), 90 },
		{ _T("ʱ���"), 165 },
		{ _T("����"), 1200 }
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

	m_wndTab.InsertItem(0, _T("������"));
	m_wndTab.InsertItem(1, _T("���ݲ鿴"));	
	m_wndTab.InsertItem(2, _T("��������"));	
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
	INT nTab = m_wndTab.GetCurSel();
	OnSwitchWnd(0, nTab);
}


void CDlgMain::OnClose()
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CloseSys();
	CDialogEx::OnClose();
}


void CDlgMain::OnBnClickedBtnRun()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (!CHWorkPool->IsCreate())
	{
		CHWorkPool->Start(this);
		LOG(_T("��ʼ���"));
		CWorkFunc::m_nWorkStep = 10;
		GetDlgItem(IDC_BTN_RUN)->EnableWindow(FALSE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(TRUE);
	}
}


void CDlgMain::OnBnClickedBtnStop()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	if (CHWorkPool->IsCreate())
	{
		CHWorkPool->Stop();
		GetDlgItem(IDC_BTN_RUN)->EnableWindow(TRUE);
		GetDlgItem(IDC_BTN_STOP)->EnableWindow(FALSE);
		LOG(_T("ֹͣ���"));
	}
}
