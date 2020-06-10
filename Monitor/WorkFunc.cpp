#include "StdAfx.h"
#include "Monitor.h"
#include "WorkFunc.h"
#include "ParamHelp.h"
#include "WorkPool.h"
#include "ModbusHelp.h"
#include "AdoHelp.h"
#include "DlgMain.h"

//�¶�ֵ������Y����ֵ�߱�ĳ�����Թ�ϵ
#define TEMPTOY(x)   (2*x+100)

//ʪ��ֵ������Y����ֵ�߱�ĳ�����Թ�ϵ
#define HTOY(x)   (3*x)

// ���Ʋ���
unsigned int CWorkFunc::m_nWorkStep = 10;


int		 CWorkFunc::m_nPixYTemperature[11] = { 0 };
int		 CWorkFunc::m_nPixYHumidity[11] = { 0 };

double		CWorkFunc::m_fCurTemperature = 0;
double		CWorkFunc::m_fCurHumidity = 0;
// ȫ�ֲ�������



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

	// ��ȡϵͳ����
	CHParam->Refresh();

	LOG(_T("�����������"));
	return TRUE;
}


BOOL CWorkFunc::ReadyWork()
{
	
	if (!CHModbus->m_bInit)
	{
		LOG(_T("���ڳ�ʼ��ʧ��"));
		AfxMessageBox(_T("��ܰ��ʾ�����ڳ�ʼ��ʧ��!"));
		return FALSE;
	}

	return TRUE;
}



BOOL CWorkFunc::ResetCtrlParam()
{

//	TIP(_T("�Զ�������..."));
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

	LOG(_T("��ʼ��ȡ����"));
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
			LOG_ERR(_T("ͨѶ��ʱ�����鴮������"));
			return FALSE;
		}
	} while (TRUE);

	LOG2(_T("��ȡ���¶�ֵΪ��%.1f��ʪ��ֵΪ��%.1f"), m_fCurTemperature, m_fCurHumidity);

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

	// ���͸�DlgView���������ʪ��ͼ
	HWND hWnd = ((CDlgMain*)(theApp.m_pMainWnd))->m_wndView.m_hWnd;
	::PostMessage(hWnd, WM_USER_UPDATE_VIEW, 0, 0);

	return TRUE;
}


BOOL CWorkFunc::Alarm()
{	
	LOG_ERR(_T("���г��ִ���"));

	return TRUE;
}



BOOL CWorkFunc::End()
{

	return TRUE;
}

