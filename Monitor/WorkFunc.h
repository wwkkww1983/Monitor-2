#pragma once



class CWorkFunc
{
public:
	CWorkFunc(void);
	~CWorkFunc(void);

	// var
public:
	static UINT				m_nWorkStep;
	//像素坐标数据
	static int		m_nPixYTemperature[11];
	static int		m_nPixYHumidity[11];
	//当前温度值
	static double	m_fCurTemperature;
	//当前湿度值
	static double	m_fCurHumidity;
	// func
public:

	static BOOL		Idel();							// 休眠
	static BOOL		Start();						// 流程开始
	static BOOL		ReadyWork();					// 运行前准备
	
	static BOOL		ResetCtrlParam();				// 复位运行控制参数
	static BOOL		WaitWork();						// 等待
	static BOOL		ReadData();						// 读取温度
	static BOOL		UpdateView();

	static BOOL		Alarm();
	static BOOL		End();							// 流程结束

};

