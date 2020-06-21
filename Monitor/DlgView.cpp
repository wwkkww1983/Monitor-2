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
	ON_MESSAGE(WM_USER_UPDATE_ALARM, &CDlgView::OnUserUpdateAlarm)
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()	
END_MESSAGE_MAP()


// CDlgView 消息处理程序
BOOL CDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化


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
	//灰色背景填充
	MemDC.FillSolidRect(rect, RGB(128, 128, 128));
	//双缓冲画图
	m_Meter.Draw(&MemDC);

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

afx_msg LRESULT CDlgView::OnUserUpdateAlarm(WPARAM wParam, LPARAM lParam)
{
	CRect rect;
	BOOL bStateMeter = CWorkFunc::m_fCurTemperature > 100 ? TRUE : FALSE;
	m_Meter.SetAlarmStateThermoMeter(bStateMeter);
	m_Meter.GetRectAlarmThermoMeter(rect);
	InvalidateRect(rect);

	BOOL bStateHygrometer = CWorkFunc::m_fCurHumidity > 100 ? TRUE : FALSE;
	m_Meter.SetAlarmStateHygrometer(bStateHygrometer);
	m_Meter.GetRectAlarmHygrometer(rect);
	InvalidateRect(rect);

	return 0;
}
