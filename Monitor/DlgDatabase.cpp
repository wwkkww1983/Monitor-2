// DlgDatabase.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgDatabase.h"
#include "afxdialogex.h"
#include "AdoHelp.h"

// CDlgDatabase 对话框

IMPLEMENT_DYNAMIC(CDlgDatabase, CDialogEx)

CDlgDatabase::CDlgDatabase(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgDatabase::IDD, pParent)
{

}

CDlgDatabase::~CDlgDatabase()
{
}

void CDlgDatabase::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DATA, m_ListCtrl);
}


BEGIN_MESSAGE_MAP(CDlgDatabase, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_CLEAR, &CDlgDatabase::OnBnClickedBtnClear)
	ON_BN_CLICKED(IDC_BTN_UPDATE, &CDlgDatabase::OnBnClickedBtnUpdate)
	ON_BN_CLICKED(IDC_BTN_DELETE, &CDlgDatabase::OnBnClickedBtnDelete)
END_MESSAGE_MAP()


// CDlgDatabase 消息处理程序


BOOL CDlgDatabase::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_ListCtrl.InsertColumn(0, _T("时间"), 0, 200);
	m_ListCtrl.InsertColumn(1, _T("温度"), 0, 200);
	m_ListCtrl.InsertColumn(2, _T("湿度"), 0, 200);
	DWORD dwStyle = m_ListCtrl.GetExtendedStyle();
	dwStyle |= LVS_EX_GRIDLINES;
	dwStyle |= LVS_EX_FULLROWSELECT;
	m_ListCtrl.SetExtendedStyle(dwStyle);


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CDlgDatabase::OnBnClickedBtnClear()
{
	// TODO:  在此添加控件通知处理程序代码
	CHAdo->ClearDatabase();
}


void CDlgDatabase::UpdateList()
{
	m_ListCtrl.DeleteAllItems();
	CHAdo->LoadDataToList(m_ListCtrl);
}

void CDlgDatabase::OnBnClickedBtnUpdate()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateList();
}


void CDlgDatabase::OnBnClickedBtnDelete()
{
	// TODO:  在此添加控件通知处理程序代码
	POSITION pos = m_ListCtrl.GetFirstSelectedItemPosition();
	int nIndex = m_ListCtrl.GetNextSelectedItem(pos);

	if (nIndex >= 0)
	{
		CString strTime = m_ListCtrl.GetItemText(nIndex, 0);
		CHAdo->DeleteRecord(strTime);
		m_ListCtrl.DeleteItem(nIndex);
	}
}
