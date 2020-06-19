// DlgParam.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgParam.h"
#include "afxdialogex.h"


// CDlgParam 对话框

IMPLEMENT_DYNAMIC(CDlgParam, CDialogEx)

CDlgParam::CDlgParam(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgParam::IDD, pParent)
{

}

CDlgParam::~CDlgParam()
{
}

void CDlgParam::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);

}


BEGIN_MESSAGE_MAP(CDlgParam, CDialogEx)

END_MESSAGE_MAP()


// CDlgParam 消息处理程序


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	GetClientRect(&rect);

	m_wndSheetParam.Create(this,WS_CHILD|WS_VISIBLE);

	m_wndSheetParam.MoveWindow(rect);




	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}


void CDlgParam::OnBnClickedBtnParamSave()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wndSheetParam.m_Page1.XSaveCtrlValue();

	AfxMessageBox(_T("参数保存完成"));
}


