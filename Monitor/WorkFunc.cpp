#include "StdAfx.h"
#include "Monitor.h"
#include "WorkFunc.h"
#include "ParamHelp.h"
#include "WorkPool.h"
#include "ModbusHelp.h"
#include "AdoHelp.h"
#include "DlgMain.h"

//温度值和像素Y坐标值具备某种线性关系
#define TEMPTOY(x)   (2*x+100)

//湿度值和像素Y坐标值具备某种线性关系
#define HTOY(x)   (3*x)

// 控制参数
unsigned int CWorkFunc::m_nWorkStep = 10;


int		 CWorkFunc::m_nPixYTemperature[11] = { 0 };
int		 CWorkFunc::m_nPixYHumidity[11] = { 0 };

double		CWorkFunc::m_fCurTemperature = 0;
double		CWorkFunc::m_fCurHumidity = 0;
// 全局参数变量



CWorkFunc::CWorkFunc(void)
{
}


CWorkFunc::~CWorkFunc(void)
{
}


BOOL CWorkFunc::Idel()
{
	Sleep(5);
	return TRUE;
}


BOOL CWorkFunc::Start()
{
	BOOL bRtn = FALSE;

	// 读取系统参数
	CHParam->Refresh();

	LOG(_T("参数加载完成"));
	return TRUE;
}


BOOL CWorkFunc::ReadyWork()
{
	
	if (!CHModbus->m_bInit)
	{
		LOG(_T("串口初始化失败"));
		AfxMessageBox(_T("温馨提示：串口初始化失败!"));
		return FALSE;
	}

	return TRUE;
}



BOOL CWorkFunc::ResetCtrlParam()
{

//	TIP(_T("自动运行中..."));
	return TRUE;
}


BOOL CWorkFunc::WaitWork()
{
	
	CTime curTime = CTime::GetCurrentTime();
	CTime lastTime = curTime;
	CTimeSpan timeSpan;
	int nSignalHandle = 0;
	DWORD dwWait = 0;
	BOOL bSts = FALSE;

	do
	{
		dwWait = WaitForSingleObject(CHWorkPool->m_StopEvent, 0);
		nSignalHandle = dwWait - WAIT_OBJECT_0;
		if (nSignalHandle == 0)			// stop
		{
			return FALSE;
		}

		curTime = CTime::GetCurrentTime();
		timeSpan = curTime - lastTime;
		if (timeSpan.GetSeconds() >= CHParam->m_nUpdateDelteTime)
		{
			break;
		}	

	} while (TRUE);

	return TRUE;
}

BOOL CWorkFunc::ReadData()
{
	int nSignalHandle = 0;
	DWORD dwWait = 0;
	LONG bSts = FALSE;

	int nTick = 0;

	CHModbus->WriteData();

	LOG(_T("开始获取数据"));
	do
	{
		dwWait = WaitForSingleObject(CHWorkPool->m_StopEvent, 0);
		nSignalHandle = dwWait - WAIT_OBJECT_0;
		if (nSignalHandle == 0)			// stop
		{
			return FALSE;
		}

		DWORD startTick = GetTickCount();
		if (CHModbus->ReadData(m_fCurTemperature, m_fCurHumidity,3000))
		{
			break;
		}
		DWORD endTick = GetTickCount();
	
		nTick += (endTick - startTick);
		if (nTick > 3000)
		{
			LOG_ERR(_T("通讯超时，请检查串口连接"));
			return FALSE;
		}
	} while (TRUE);

	LOG2(_T("读取到温度值为：%.1f，湿度值为：%.1f"), m_fCurTemperature, m_fCurHumidity);

	CString strTemperature, strHumidity;
	CString strTime = CTime::GetCurrentTime().Format(_T("%y-%m-%d %H:%M:%S"));
	strTemperature.Format(_T("%.1f"), m_fCurTemperature);
	strHumidity.Format(_T("%.1f"), m_fCurHumidity);
	CHAdo->InsertTable(strTime, strTemperature, strHumidity);
	return TRUE;
}

BOOL	CWorkFunc::UpdateView()
{

	m_nPixYTemperature[10] = TEMPTOY(m_fCurTemperature);
	m_nPixYHumidity[10] = HTOY(m_fCurHumidity);
	for (int i = 0; i < 10; i++)
	{
		m_nPixYTemperature[i] = m_nPixYTemperature[i + 1];
		m_nPixYHumidity[i] = m_nPixYHumidity[i + 1];
	}

	// 发送给DlgView界面更新温湿度图
	HWND hWnd = ((CDlgMain*)(theApp.m_pMainWnd))->m_wndView.m_hWnd;
	::PostMessage(hWnd, WM_USER_UPDATE_VIEW, 0, 0);

	return TRUE;
}


BOOL CWorkFunc::Alarm()
{	
	LOG_ERR(_T("运行出现错误"));

	return TRUE;
}



BOOL CWorkFunc::End()
{

	return TRUE;
}

