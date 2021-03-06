// Meter.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "Meter.h"
#include "WorkFunc.h"
#include "ParamHelp.h"

//y轴刻度尺数据
static int nY1[11] = { -50, -35, -20, -5, 10, 25, 40, 55, 70, 85, 100 };
static int nY2[11] = { 0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 };

#define OffsetX		50 
#define OffsetY		100

// CMeter


CMeter::CMeter()
{
	m_clrAlarmT = RGB(0, 255, 0);
	m_clrAlarmT = RGB(0, 255, 0);
}

CMeter::~CMeter()
{
}

void CMeter::Draw(CDC* pDC)
{
	//画坐标轴
	DrawCoordinateAxis(pDC);
	//画温度计
	DrawThermoMeter(pDC);
	//画湿度计
	DrawHygrometer(pDC);
	//画报警信号灯
	DrawAlarmThermoMeter(pDC);
	DrawAlarmHygrometer(pDC);
}


void CMeter::DrawCoordinateAxis(CDC* pDC)
{
	CPen pen(0, 1, RGB(0, 0, 255));
	CPen* pOldPen = pDC->SelectObject(&pen);

	int nAxisWidth = 300;
	int nAxisHeight = 300;

	DrawLine(pDC, 0, nAxisHeight, 0, 0);
	DrawLine(pDC, 0, nAxisHeight, nAxisWidth, nAxisHeight);
	pDC->TextOut(OffsetX + 0, OffsetY - 30, _T("大气温度/℃"));
	pDC->TextOut(OffsetX + nAxisWidth, OffsetY + nAxisHeight-30, _T("时间/秒之前"));

	DrawLine(pDC, nAxisWidth + 200, nAxisHeight, nAxisWidth + 200, 0);
	DrawLine(pDC, nAxisWidth + 200, nAxisHeight, nAxisWidth + 200 + nAxisWidth, nAxisHeight);
	pDC->TextOut(OffsetX + 500, OffsetY - 30, _T("大气湿度/RH%"));
	pDC->TextOut(OffsetX + 800, OffsetY + nAxisHeight-30, _T("时间/秒之前"));

	CString strDelta;

	int nDelta = 30;


	for (int i = 0; i < 11; i++)
	{
		//画温度x轴刻度尺，长度5像素
		DrawLine(pDC, i*nDelta, nAxisHeight - 5, i*nDelta, nAxisHeight);
		strDelta.Format(_T("%d"), CHParam->m_nTimeSpan*(10 - i));
		//温度X轴刻度值
		pDC->TextOut(OffsetX + i*nDelta, OffsetY + nAxisHeight + 5, strDelta);
		//画湿度x轴刻度尺，长度5像素
		DrawLine(pDC, 500 + i*nDelta, nAxisHeight - 5, 500 + i*nDelta, nAxisHeight);
		strDelta.Format(_T("%d"), CHParam->m_nTimeSpan*(10 - i));
		//湿度X轴刻度值
		pDC->TextOut(OffsetX + 500 + i*nDelta, OffsetY + nAxisHeight + 5, strDelta);


		//画温度y轴刻度尺，长度5像素
		DrawLine(pDC, 0, nAxisHeight - i*nDelta, 5, nAxisHeight - i*nDelta);
		strDelta.Format(_T("%d"), nY1[i]);
		//温度y轴刻度值
		pDC->TextOut(OffsetX + -25, OffsetY + nAxisHeight - i*nDelta-10, strDelta);
		//画湿度y轴刻度尺，长度5像素
		DrawLine(pDC, 500, nAxisHeight - i*nDelta, 500 + 5, nAxisHeight - i*nDelta);
		strDelta.Format(_T("%d"), nY2[i]);
		//湿度y轴刻度值
		pDC->TextOut(OffsetX + -25 + 500, OffsetY + nAxisHeight - i*nDelta-10, strDelta);

		if (i < 10 )
		{	//温度值连线			
			DrawLine(pDC, i*nDelta, nAxisHeight - CWorkFunc::m_nPixYTemperature[i], (i + 1) * nDelta, nAxisHeight - CWorkFunc::m_nPixYTemperature[i + 1]);
			//湿度值连线		
			DrawLine(pDC, 500 + i*nDelta, nAxisHeight - CWorkFunc::m_nPixYHumidity[i], 500 + (i + 1) * nDelta, nAxisHeight - CWorkFunc::m_nPixYHumidity[i + 1]);
		}
	}

	pDC->SelectObject(pOldPen);

}


void CMeter::DrawLine(CDC* pDC, int x1, int y1, int x2, int y2)
{
	pDC->MoveTo(OffsetX + x1, OffsetY + y1);
	pDC->LineTo(OffsetX + x2, OffsetY + y2);
}

//画温度计
void CMeter::DrawThermoMeter(CDC* pDC)
{
	int nAxisHeight = 300;
	CString strText;
	CRect rect;

	int nPixT = 2 * CWorkFunc::m_fCurTemperature + 100;
	
	int nDelta = 30;

	pDC->SetBkMode(TRANSPARENT);

	pDC->TextOut(OffsetX + 390, OffsetY - 30, _T("大气温度/℃"));
	DrawLine(pDC, 415, 0, 415, nAxisHeight);
	DrawLine(pDC, 435, 0, 435, nAxisHeight);
	pDC->Rectangle(OffsetX + 418, OffsetY , OffsetX + 433, OffsetY + nAxisHeight);
	rect.SetRect(OffsetX + 400, OffsetY + nAxisHeight, OffsetX + 450, OffsetY + nAxisHeight + 40);	
	pDC->Ellipse(rect);
	rect.DeflateRect(2, 10);
	strText.Format(_T("%.1f℃"), CWorkFunc::m_fCurTemperature);
	if (CWorkFunc::m_fCurTemperature < -50.0)
		CWorkFunc::m_fCurTemperature = -50.0;

	pDC->DrawText(strText, rect, DT_VCENTER);

	//温度值矩形填充
	rect.SetRect(OffsetX + 418, OffsetY + nAxisHeight - nPixT, OffsetX + 433, OffsetY + nAxisHeight);
	if (rect.top>rect.bottom)
	{
		rect.top = rect.bottom;
	}
	pDC->FillRect(rect, &(CBrush(RGB(0, 255, 0))));

}

//画湿度计
void CMeter::DrawHygrometer(CDC* pDC)
{
	int nAxisHeight = 300;	
	int nPixH = 3 * CWorkFunc::m_fCurHumidity ;
	CString strText;
	CRect rect;

	pDC->TextOut(OffsetX + 880, OffsetY - 30, _T("大气湿度/RH%"));
	DrawLine(pDC, 910, 0, 910, nAxisHeight);
	DrawLine(pDC, 930, 0, 930, nAxisHeight);
	pDC->Rectangle(OffsetX + 913, OffsetY , OffsetX + 927, OffsetY + nAxisHeight);
	//湿度值矩形填充
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

	int nDelta = 30;
	for (int i = 0; i < 11; i++)
	{
		//画湿度y轴刻度尺，长度5像素
		DrawLine(pDC, 410, nAxisHeight - i*nDelta, 415, nAxisHeight - i*nDelta);
		DrawLine(pDC, 435, nAxisHeight - i*nDelta, 440, nAxisHeight - i*nDelta);
		strText.Format(_T("%d"), nY1[i]);
		//湿度y轴刻度值
		pDC->TextOut(OffsetX + 400 - 15, OffsetY - 10 + nAxisHeight - i*nDelta, strText);

		DrawLine(pDC, 905, nAxisHeight - i*nDelta, 910, nAxisHeight - i*nDelta);
		DrawLine(pDC, 930, nAxisHeight - i*nDelta, 935, nAxisHeight - i*nDelta);
		strText.Format(_T("%d"), nY2[i]);
		//湿度y轴刻度值
		pDC->TextOut(OffsetX + 900 - 20, OffsetY - 10 + nAxisHeight - i*nDelta, strText);
	}
}

void CMeter::DrawAlarmThermoMeter(CDC* pDC)
{
	CRgn rgn;
	rgn.CreateEllipticRgn(OffsetX + 405, OffsetY - 80, OffsetX + 445, OffsetY - 40);
	CBrush brush;
	brush.CreateSolidBrush(m_clrAlarmT);
	pDC->FillRgn(&rgn, &brush);
	brush.DeleteObject();
	rgn.DeleteObject();
}
void CMeter::DrawAlarmHygrometer(CDC* pDC)
{
	CRgn rgn;
	rgn.CreateEllipticRgn(OffsetX + 900, OffsetY - 80, OffsetX + 940, OffsetY - 40);
	CBrush brush;
	brush.CreateSolidBrush(m_clrAlarmT);
	pDC->FillRgn(&rgn, &brush);
	brush.DeleteObject();
	rgn.DeleteObject();
}

void CMeter::SetAlarmStateThermoMeter(BOOL bAlarm)
{
	if (bAlarm)
		m_clrAlarmT = RGB(255, 0, 0);			
	else
		m_clrAlarmT = RGB(0, 255, 0);
}

void CMeter::SetAlarmStateHygrometer(BOOL bAlarm)
{
	if (bAlarm)
		m_clrAlarmH = RGB(255, 0, 0);			
	else
		m_clrAlarmH = RGB(0, 255, 0);
}


//获取温度计报警信号灯矩形位置
void CMeter::GetRectAlarmThermoMeter(CRect&  rect)
{
	rect.SetRect(OffsetX + 405, OffsetY - 80, OffsetX + 445, OffsetY - 40);
}

//获取湿度计报警信号灯矩形位置
void CMeter::GetRectAlarmHygrometer(CRect&  rect)
{
	rect.SetRect(OffsetX + 900, OffsetY - 80, OffsetX + 940, OffsetY - 40);
}