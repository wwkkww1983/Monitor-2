#pragma once


// CMeter

class CMeter 
{
public:
	CMeter();
	virtual ~CMeter();

public:
	//绘制所有
	void Draw(CDC* pDC);

	//设置温度计报警信号灯状态，TRUE显示红色，否则绿色
	void SetAlarmStateThermoMeter(BOOL bAlarm);
	//设置湿度计报警信号灯状态，TRUE显示红色，否则绿色
	void SetAlarmStateHygrometer(BOOL bAlarm);
	//获取温度计报警信号灯矩形位置
	void GetRectAlarmThermoMeter(CRect& rect);
	//获取湿度计报警信号灯矩形位置
	void GetRectAlarmHygrometer(CRect&  rect);
private:
	COLORREF m_clrAlarmT;
	COLORREF m_clrAlarmH;
private:
	//画线
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2);
	//画坐标轴
	void DrawCoordinateAxis(CDC* pDC);
	//画温度计
	void DrawThermoMeter(CDC* pDC);
	//画湿度计
	void DrawHygrometer(CDC* pDC);
	//温度计报警信号灯
	void DrawAlarmThermoMeter(CDC* pDC);
	//湿度计报警信号灯
	void DrawAlarmHygrometer(CDC* pDC);

};


