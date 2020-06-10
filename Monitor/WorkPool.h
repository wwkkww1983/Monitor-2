#pragma once
#include "Singleton.h"
#include "Monitor.h"


#define CHWorkPool		CWorkPool::GetInstance()

class CWorkPool
{
public:
	friend class Singleton<CWorkPool>;

public:
	CWorkPool(void);
	~CWorkPool(void);

// var
public:
	CEvent				m_StopEvent;
protected:
	CEvent				m_WorkStartEvent;
	CEvent				m_RunEvent;
	CWinThread*			m_pWorkThread;
	DWORD				m_dwErrorCode;
	CCriticalSection	m_csWorkThread;
	CWnd*				m_pDlgMain;


// func
public:
	static CWorkPool* GetInstance();
	BOOL Start(CWnd* pDlgMain);
	BOOL Stop();
	BOOL Wait();
	BOOL IsCreate();
	static UINT WorkFunction(LPVOID pParam);
	void WorkFunction();
	void OnError(const CString& sError);

};

