
// Monitor.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������

#define		WM_USER_UPDATE_VIEW			WM_USER + 103

struct XSleepStruct
{
	int duration;
	HANDLE eventHandle;
};
// CMonitorApp:
// �йش����ʵ�֣������ Monitor.cpp
//

class CMonitorApp : public CWinApp
{
public:
	CMonitorApp();

// ��д
public:
	virtual BOOL InitInstance();

	static void	XSleep(int nWaitInMSecs);
// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMonitorApp theApp;