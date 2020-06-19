// PageParam1.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PageParam1.h"
#include "afxdialogex.h"
#include "ParamHelp.h"

// CPageParam1 对话框

IMPLEMENT_DYNAMIC(CPageParam1, CMFCPropertyPage)

CPageParam1::CPageParam1()
	: CMFCPropertyPage(CPageParam1::IDD)
{

}

CPageParam1::~CPageParam1()
{
}

void CPageParam1::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_CMB_PORT, m_wndPort);
	DDX_Control(pDX, IDC_CMB_BAUD, m_wndBaud);
	DDX_Control(pDX, IDC_CMB_DATABITS, m_wndDataBits);
	DDX_Control(pDX, IDC_CMB_PARITY, m_wndParity);
	DDX_Control(pDX, IDC_CMB_STOPBITS, m_wndStopBits);
}


BEGIN_MESSAGE_MAP(CPageParam1, CPropertyPage)
END_MESSAGE_MAP()


// CPageParam1 消息处理程序
BOOL CPageParam1::OnInitDialog()
{
	CMFCPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CStringArray arrPort;
	GetAllSerialPorts(arrPort);
	for(int i = 0 ;i < arrPort.GetSize();i++)
	{
		m_wndPort.AddString(arrPort.GetAt(i));
	}

	m_wndBaud.AddString(_T("4800"));
	m_wndBaud.AddString(_T("9600"));
	m_wndBaud.AddString(_T("14400"));
	m_wndBaud.AddString(_T("19200"));
	m_wndBaud.AddString(_T("38400"));
	m_wndBaud.AddString(_T("57600"));
	m_wndBaud.AddString(_T("115200"));

	m_wndStopBits.AddString(_T("1"));
	m_wndStopBits.AddString(_T("1.5"));
	m_wndStopBits.AddString(_T("2"));

	m_wndParity.AddString(_T("None"));
	m_wndParity.AddString(_T("Odd"));
	m_wndParity.AddString(_T("Even"));	

	m_wndDataBits.AddString(_T("5"));
	m_wndDataBits.AddString(_T("6"));
	m_wndDataBits.AddString(_T("7"));
	m_wndDataBits.AddString(_T("8"));

	m_wndPort.SetCurSel(0);
	m_wndBaud.SetCurSel(0);
	m_wndStopBits.SetCurSel(0);
	m_wndParity.SetCurSel(0);
	m_wndDataBits.SetCurSel(0);



	XInitCtrlValue();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}



bool CPageParam1::GetAllSerialPorts(CStringArray& arrPorts)
{
	long lReg, k = 0;
	HKEY hKey;
	DWORD MaxValueLength;
	DWORD dwValueNumber;
	lReg = RegOpenKeyExA(HKEY_LOCAL_MACHINE,
		"HARDWARE\\DEVICEMAP\\SERIALCOMM",
		0,
		KEY_QUERY_VALUE,
		&hKey);
	if (lReg != ERROR_SUCCESS)
	{
		return false;
	}
	lReg = RegQueryInfoKeyA(hKey,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		&dwValueNumber,
		&MaxValueLength,
		NULL,
		NULL,
		NULL);

	if (lReg != ERROR_SUCCESS)
	{
		return false;
	}

	LPSTR pValueName, pCOMNumber;
	DWORD cchValueName, dwValueSize = 6;
	for (int i = 0; i < dwValueNumber; i++)
	{
		cchValueName = MaxValueLength + 1;
		dwValueSize = 6;
		pValueName = (LPSTR)VirtualAlloc(NULL, cchValueName, MEM_COMMIT, PAGE_READWRITE);
		lReg = RegEnumValueA(hKey,
			i,
			pValueName,
			&cchValueName,
			NULL,
			NULL,
			NULL,
			NULL);
		if ((lReg != ERROR_SUCCESS) && (lReg != ERROR_NO_MORE_ITEMS))
		{
			return false;
		}
		pCOMNumber = (LPSTR)VirtualAlloc(NULL, 6, MEM_COMMIT, PAGE_READWRITE);
		lReg = RegQueryValueExA(hKey,
			pValueName,
			NULL,
			NULL,
			(LPBYTE)pCOMNumber,
			&dwValueSize);
		if (lReg != ERROR_SUCCESS)
		{
			return false;
		}
		
		USES_CONVERSION;
		CString strPortName = A2T(pCOMNumber);
		arrPorts.Add(strPortName);
		VirtualFree(pValueName, 0, MEM_RELEASE);
		VirtualFree(pCOMNumber, 0, MEM_RELEASE);
	}


	return true;
}


void CPageParam1::XInitCtrlValue()
{
	CHParam->ReadSerialRoot();
	m_wndPort.SetCurSel(0);
	m_wndBaud.SetCurSel(0);
	m_wndStopBits.SetCurSel(0);
	m_wndParity.SetCurSel(0);
	m_wndDataBits.SetCurSel(0);

	CString strText;
	strText.Format(_T("COM%d"),CHParam->m_nPort);
	int nSel = m_wndPort.FindString(0,strText);
	m_wndPort.SetCurSel(nSel);

	strText.Format(_T("%d"),CHParam->m_nBaud);
	nSel = m_wndBaud.FindString(0,strText);
	m_wndBaud.SetCurSel(nSel);

	m_wndStopBits.SetCurSel(CHParam->m_nStopBits);
	m_wndParity.SetCurSel(CHParam->m_nParity);

	strText.Format(_T("%d"),CHParam->m_nDataBits);
	nSel = m_wndDataBits.FindString(0,strText);
	m_wndDataBits.SetCurSel(nSel);

	SetDlgItemInt(IDC_EDIT_TIMESPAN,CHParam->m_nTimeSpan);
}

void CPageParam1::XSaveCtrlValue()
{
	CString strPort;
	m_wndPort.GetWindowText(strPort);
	CHParam->m_nPort = CHGetIntFromString(strPort);

	CHParam->m_nBaud = GetDlgItemInt(IDC_CMB_BAUD);
	CHParam->m_nParity = m_wndParity.GetCurSel();
	CHParam->m_nStopBits = m_wndStopBits.GetCurSel();
	CHParam->m_nDataBits = GetDlgItemInt(IDC_CMB_DATABITS);
	CHParam->m_nTimeSpan = GetDlgItemInt(IDC_EDIT_TIMESPAN);
	CHParam->WriteSerialRoot();

	SetModified(FALSE);
}

BOOL CPageParam1::OnCommand(WPARAM wParam, LPARAM lParam)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(lParam!=NULL)
	{
		if (HIWORD(wParam)==EN_CHANGE||HIWORD(wParam)==BN_CLICKED||HIWORD(wParam)==CBN_SELCHANGE)
		{
			SetModified();
		}
 
	}
	return CMFCPropertyPage::OnCommand(wParam, lParam);
}
