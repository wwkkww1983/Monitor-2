// DlgView.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgView.h"
#include "afxdialogex.h"
#include "WorkFunc.h"
#include "ParamHelp.h"


// CDlgView 对话框

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


// CDlgView 消息处理程序
BOOL CDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CRect rect;
	GetClientRect(rect);
	m_ThermoMeter.Create(_T(""),WS_VISIBLE|WS_CHILD,rect,this);
	m_ThermoMeter.MoveWindow(rect);

	SetTimer(10, 700,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}

void CDlgView::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	CRect rect;
	GetClientRect(&rect);

	dc.SetBkMode(TRANSPARENT);
	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);

	CBitmap MemBmp;
	MemBmp.CreateCompatibleBitmap(&dc, rect.Width(), rect.Height());

	CBitmap* pOldBmp = MemDC.SelectObject(&MemBmp);
//	灰色背景填充
	MemDC.FillSolidRect(rect, RGB(128, 128, 128));
	// 双缓冲画图
	//画坐标轴
	m_ThermoMeter.DrawAxis(&MemDC);
	//画温度计
	m_ThermoMeter.DrawHermometer(&MemDC);
	//画报警信号灯
	m_ThermoMeter.DrawAlarmT(&MemDC);
	m_ThermoMeter.DrawAlarmH(&MemDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	// 释放
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
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	return TRUE;
//	return CDialogEx::OnEraseBkgnd(pDC);
}






void CDlgView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	m_ThermoMeter.OnTimer(nIDEvent);
	CDialogEx::OnTimer(nIDEvent);
}
