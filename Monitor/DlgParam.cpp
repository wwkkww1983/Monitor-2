// DlgParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgParam.h"
#include "afxdialogex.h"


// CDlgParam �Ի���

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


// CDlgParam ��Ϣ�������


BOOL CDlgParam::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetClientRect(&rect);

	m_wndSheetParam.Create(this,WS_CHILD|WS_VISIBLE);

	m_wndSheetParam.MoveWindow(rect);




	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}


void CDlgParam::OnBnClickedBtnParamSave()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_wndSheetParam.m_Page1.XSaveCtrlValue();

	AfxMessageBox(_T("�����������"));
}


