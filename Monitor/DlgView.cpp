// DlgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgView.h"
#include "afxdialogex.h"
#include "WorkFunc.h"
#include "ParamHelp.h"


// CDlgView �Ի���

IMPLEMENT_DYNAMIC(CDlgView, CDialogEx)

CDlgView::CDlgView(CWnd* pParent /*=NULL*/)
	: CDialogEx(CDlgView::IDD, pParent)
{

}

CDlgView::~CDlgView()
{
}

void CDlgView::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgView, CDialogEx)
	ON_WM_PAINT()
	ON_MESSAGE(WM_USER_UPDATE_VIEW, &CDlgView::OnUserUpdateView)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgView ��Ϣ�������
BOOL CDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CRect rect;
	GetClientRect(rect);
	m_ThermoMeter.Create(_T(""),WS_VISIBLE|WS_CHILD,rect,this);
	m_ThermoMeter.MoveWindow(rect);

	SetTimer(10, 700,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);

	dc.SetBkMode(TRANSPARENT);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CBitmap MemBmp;
	MemBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBmp = MemDC.SelectObject(&MemBmp);
//	��ɫ�������
	MemDC.FillSolidRect(rect, RGB(128, 128, 128));
	// ˫���廭ͼ
	//��������
	m_ThermoMeter.DrawAxis(&MemDC);
	//���¶ȼ�
	m_ThermoMeter.DrawHermometer(&MemDC);
	//�������źŵ�
	m_ThermoMeter.DrawAlarmT(&MemDC);
	m_ThermoMeter.DrawAlarmH(&MemDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	// �ͷ�
	MemDC.SelectObject(pOldBmp);
	MemBmp.DeleteObject();
	MemDC.DeleteDC();
}



afx_msg LRESULT CDlgView::OnUserUpdateView(WPARAM wParam, LPARAM lParam)
{
	CRect rc;
	GetClientRect(&rc);
	InvalidateRect(rc);
	return 0;
}


BOOL CDlgView::OnEraseBkgnd(CDC* pDC)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
}






void CDlgView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	m_ThermoMeter.OnTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}
