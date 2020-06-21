#pragma once


// CMeter

class CMeter 
{
public:
	CMeter();
	virtual ~CMeter();

public:
	//��������
	void Draw(CDC* pDC);

	//�����¶ȼƱ����źŵ�״̬��TRUE��ʾ��ɫ��������ɫ
	void SetAlarmStateThermoMeter(BOOL bAlarm);
	//����ʪ�ȼƱ����źŵ�״̬��TRUE��ʾ��ɫ��������ɫ
	void SetAlarmStateHygrometer(BOOL bAlarm);
	//��ȡ�¶ȼƱ����źŵƾ���λ��
	void GetRectAlarmThermoMeter(CRect& rect);
	//��ȡʪ�ȼƱ����źŵƾ���λ��
	void GetRectAlarmHygrometer(CRect&  rect);
private:
	COLORREF m_clrAlarmT;
	COLORREF m_clrAlarmH;
private:
	//����
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2);
	//��������
	void DrawCoordinateAxis(CDC* pDC);
	//���¶ȼ�
	void DrawThermoMeter(CDC* pDC);
	//��ʪ�ȼ�
	void DrawHygrometer(CDC* pDC);
	//�¶ȼƱ����źŵ�
	void DrawAlarmThermoMeter(CDC* pDC);
	//ʪ�ȼƱ����źŵ�
	void DrawAlarmHygrometer(CDC* pDC);

};


