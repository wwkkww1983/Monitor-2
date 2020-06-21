#pragma once


// CThermoMeter

class CThermoMeter : public CStatic
{
	DECLARE_DYNAMIC(CThermoMeter)

public:
	CThermoMeter();
	virtual ~CThermoMeter();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();

private:
	COLORREF m_clrAlarmT;
	COLORREF m_clrAlarmH;
public:

	void DrawAxis(CDC* pDC);
	void DrawHermometer(CDC* pDC);
	void DrawAlarmT(CDC* pDC);
	void DrawAlarmH(CDC* pDC);
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
};


