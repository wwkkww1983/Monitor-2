#pragma once



class CWorkFunc
{
public:
	CWorkFunc(void);
	~CWorkFunc(void);

	// var
public:
	static UINT				m_nWorkStep;
	//������������
	static int		m_nPixYTemperature[11];
	static int		m_nPixYHumidity[11];
	//��ǰ�¶�ֵ
	static double	m_fCurTemperature;
	//��ǰʪ��ֵ
	static double	m_fCurHumidity;
	// func
public:

	static BOOL		Idel();							// ����
	static BOOL		Start();						// ���̿�ʼ
	static BOOL		ReadyWork();					// ����ǰ׼��
	
	static BOOL		ResetCtrlParam();				// ��λ���п��Ʋ���
	static BOOL		WaitWork();						// �ȴ�
	static BOOL		ReadData();						// ��ȡ�¶�
	static BOOL		UpdateView();

	static BOOL		Alarm();
	static BOOL		End();							// ���̽���

};

