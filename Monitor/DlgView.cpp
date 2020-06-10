// DlgView.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "DlgView.h"
#include "afxdialogex.h"
#include "WorkFunc.h"
#include "ParamHelp.h"

//y��̶ȳ�����
static int nY1[11] = { -50, -35, -20, -5, 10, 25, 40, 55, 70, 85, 100 };
static int nY2[11] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

#define OffsetX		50 
#define OffsetY		100
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
//	MemDC.FillRect(&rect, (CBrush*)MemDC.SelectStockObject(DKGRAY_BRUSH));
	MemDC.FillSolidRect(rect, RGB(128, 128, 128));
	// ˫���廭ͼ
	//��������
	DrawAxis(&MemDC);
	//���¶ȼ�
	DrawHermometer(&MemDC);
	DrawAlarmT(&MemDC);
	DrawAlarmH(&MemDC);
	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &MemDC, 0, 0, SRCCOPY);

	// �ͷ�
	MemDC.SelectObject(pOldBmp);
	MemBmp.DeleteObject();
	MemDC.DeleteDC();
}



void CDlgView::DrawAxis(CDC* pDC)
{
	CPen pen(0, 1, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);


	int nAxisWidth = 300;
	int nAxisHeight = 300;
	


	DrawLine(pDC, 0, nAxisHeight, 0, 0);
	DrawLine(pDC, 0, nAxisHeight, nAxisWidth, nAxisHeight);
	pDC->TextOut(OffsetX + 0, OffsetY - 30, _T("�����¶�/��"));
	pDC->TextOut(OffsetX + nAxisWidth, OffsetY + nAxisHeight-30, _T("ʱ��/��֮ǰ"));

	DrawLine(pDC, nAxisWidth + 200, nAxisHeight, nAxisWidth + 200, 0);
	DrawLine(pDC, nAxisWidth + 200, nAxisHeight, nAxisWidth + 200 + nAxisWidth, nAxisHeight);
	pDC->TextOut(OffsetX + 500, OffsetY - 30, _T("����ʪ��/RH%"));
	pDC->TextOut(OffsetX + 800, OffsetY + nAxisHeight-30, _T("ʱ��/��֮ǰ"));

	CString strDelta;

	int nDelta = 30;


	for (int i = 0; i < 11; i++)
	{
		//���¶�x��̶ȳߣ�����5����
		DrawLine(pDC, i*nDelta, nAxisHeight - 5, i*nDelta, nAxisHeight);
		strDelta.Format(_T("%d"), CHParam->m_nUpdateDelteTime*(10 - i));
		//�¶�X��̶�ֵ
		pDC->TextOut(OffsetX + i*nDelta, OffsetY + nAxisHeight + 5, strDelta);
		//��ʪ��x��̶ȳߣ�����5����
		DrawLine(pDC, 500 + i*nDelta, nAxisHeight - 5, 500 + i*nDelta, nAxisHeight);
		strDelta.Format(_T("%d"), CHParam->m_nUpdateDelteTime*(10 - i));
		//ʪ��X��̶�ֵ
		pDC->TextOut(OffsetX + 500 + i*nDelta, OffsetY + nAxisHeight + 5, strDelta);


		//���¶�y��̶ȳߣ�����5����
		DrawLine(pDC, 0, nAxisHeight - i*nDelta, 5, nAxisHeight - i*nDelta);
		strDelta.Format(_T("%d"), nY1[i]);
		//�¶�y��̶�ֵ
		pDC->TextOut(OffsetX + -25, OffsetY + nAxisHeight - i*nDelta-10, strDelta);
		//��ʪ��y��̶ȳߣ�����5����
		DrawLine(pDC, 500, nAxisHeight - i*nDelta, 500 + 5, nAxisHeight - i*nDelta);
		strDelta.Format(_T("%d"), nY2[i]);
		//ʪ��y��̶�ֵ
		pDC->TextOut(OffsetX + -25 + 500, OffsetY + nAxisHeight - i*nDelta-10, strDelta);

		if (i < 10 )
		{	//�¶�ֵ����			
			DrawLine(pDC, i*nDelta, nAxisHeight - CWorkFunc::m_nPixYTemperature[i], (i + 1) * nDelta, nAxisHeight - CWorkFunc::m_nPixYTemperature[i + 1]);
			//ʪ��ֵ����		
			DrawLine(pDC, 500 + i*nDelta, nAxisHeight - CWorkFunc::m_nPixYHumidity[i], 500 + (i + 1) * nDelta, nAxisHeight - CWorkFunc::m_nPixYHumidity[i + 1]);
		}
	}

	pDC->SelectObject(pOldPen);

}


void CDlgView::DrawLine(CDC* pDC, int x1, int y1, int x2, int y2)
{
	pDC->MoveTo(OffsetX + x1, OffsetY + y1);
	pDC->LineTo(OffsetX + x2, OffsetY + y2);
}

//���¶ȼ�
void CDlgView::DrawHermometer(CDC* pDC)
{
	int nAxisHeight = 300;
	CString strText;

	int nPixT = 2 * CWorkFunc::m_fCurTemperature + 100;
	int nPixH = 3 * CWorkFunc::m_fCurHumidity ;

	CRect rect;
	int nDelta = 30;

	pDC->SetBkMode(TRANSPARENT);

	

	pDC->TextOut(OffsetX + 390, OffsetY - 30, _T("�����¶�/��"));
	DrawLine(pDC, 415, 0, 415, nAxisHeight);
	DrawLine(pDC, 435, 0, 435, nAxisHeight);
	pDC->Rectangle(OffsetX + 418, OffsetY , OffsetX + 433, OffsetY + nAxisHeight);
	rect.SetRect(OffsetX + 400, OffsetY + nAxisHeight, OffsetX + 450, OffsetY + nAxisHeight + 40);	
	pDC->Ellipse(rect);
	rect.DeflateRect(2, 10);
	strText.Format(_T("%.1f��"), CWorkFunc::m_fCurTemperature);
	if (CWorkFunc::m_fCurTemperature < -50.0)
		CWorkFunc::m_fCurTemperature = -50.0;

	pDC->DrawText(strText, rect, DT_VCENTER);


	//�¶�ֵ�������
	rect.SetRect(OffsetX + 418, OffsetY + nAxisHeight - nPixT, OffsetX + 433, OffsetY + nAxisHeight);
	if (rect.top>rect.bottom)
	{
		rect.top = rect.bottom;
	}
	pDC->FillRect(rect, &(CBrush(RGB(0, 255, 0))));

	pDC->TextOut(OffsetX + 880, OffsetY - 30, _T("����ʪ��/RH%"));
	DrawLine(pDC, 910, 0, 910, nAxisHeight);
	DrawLine(pDC, 930, 0, 930, nAxisHeight);
	pDC->Rectangle(OffsetX + 913, OffsetY , OffsetX + 927, OffsetY + nAxisHeight);
	//ʪ��ֵ�������
	rect.SetRect(OffsetX + 913, OffsetY + nAxisHeight - nPixH, OffsetX + 927, OffsetY + nAxisHeight);	
	if (rect.top>rect.bottom)
	{
		rect.top = rect.bottom;
	}
	pDC->FillRect(rect,& (CBrush(RGB(228, 0, 0))));
	rect.SetRect(OffsetX + 895, OffsetY + nAxisHeight, OffsetX + 945, OffsetY + nAxisHeight + 40);
	pDC->Ellipse(rect);
	rect.DeflateRect(2, 10);
	strText.Format(_T("%.1f%%"), CWorkFunc::m_fCurHumidity);
	if (CWorkFunc::m_fCurHumidity < 0)
		CWorkFunc::m_fCurHumidity = 0;

	pDC->DrawText(strText, rect, DT_VCENTER);

	for (int i = 0; i < 11; i++)
	{
		//���¶�y��̶ȳߣ�����5����
		DrawLine(pDC, 410, nAxisHeight - i*nDelta, 415, nAxisHeight - i*nDelta);
		DrawLine(pDC, 435, nAxisHeight - i*nDelta, 440, nAxisHeight - i*nDelta);
		strText.Format(_T("%d"), nY1[i]);
		//�¶�y��̶�ֵ
		pDC->TextOut(OffsetX + 400 - 15, OffsetY - 10 + nAxisHeight - i*nDelta, strText);

		DrawLine(pDC, 905, nAxisHeight - i*nDelta, 910, nAxisHeight - i*nDelta);
		DrawLine(pDC, 930, nAxisHeight - i*nDelta, 935, nAxisHeight - i*nDelta);
		strText.Format(_T("%d"), nY2[i]);
		//�¶�y��̶�ֵ
		pDC->TextOut(OffsetX + 900 - 20, OffsetY - 10 + nAxisHeight - i*nDelta, strText);
	}

}
void CDlgView::DrawAlarmT(CDC* pDC)
{
	CRgn rgn;
	rgn.CreateEllipticRgn(OffsetX + 405, OffsetY - 80, OffsetX + 445, OffsetY - 40);
	CBrush brush;
	brush.CreateSolidBrush(m_clrAlarmT);
	pDC->FillRgn(&rgn, &brush);
	brush.DeleteObject();
	rgn.DeleteObject();
}
void CDlgView::DrawAlarmH(CDC* pDC)
{
	CRgn rgn;
	rgn.CreateEllipticRgn(OffsetX + 900, OffsetY - 80, OffsetX + 940, OffsetY - 40);
	CBrush brush;
	brush.CreateSolidBrush(m_clrAlarmT);
	pDC->FillRgn(&rgn, &brush);
	brush.DeleteObject();
	rgn.DeleteObject();
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




BOOL CDlgView::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_clrAlarmT = RGB(0, 255, 0);
	m_clrAlarmT = RGB(0, 255, 0);
	SetTimer(10, 700,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣:  OCX ����ҳӦ���� FALSE
}

void CDlgView::OnTimer(UINT_PTR nIDEvent)
{
	// TODO:  �ڴ������Ϣ�����������/�����Ĭ��ֵ
	CRect rect;
	if (CWorkFunc::m_fCurTemperature > 100)
	{
		if (m_clrAlarmT == RGB(255, 0, 0))
			m_clrAlarmT = RGB(0, 255, 0);
		else
			m_clrAlarmT = RGB(255, 0, 0);
		rect.SetRect(OffsetX + 405, OffsetY - 80, OffsetX + 445, OffsetY - 40);
		InvalidateRect(rect);
	}
	if (CWorkFunc::m_fCurHumidity > 100)
	{
		if (m_clrAlarmH == RGB(255, 0, 0))
			m_clrAlarmH = RGB(0, 255, 0);
		else
			m_clrAlarmH = RGB(255, 0, 0);
		rect.SetRect(OffsetX + 900, OffsetY - 80, OffsetX + 940, OffsetY - 40);
		InvalidateRect(rect);
	}
	CDialogEx::OnTimer(nIDEvent);
}
