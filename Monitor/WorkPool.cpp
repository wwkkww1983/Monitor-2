#include "StdAfx.h"
#include "WorkPool.h"
#include "DlgMain.h"


CWorkPool::CWorkPool(void) : m_StopEvent(FALSE,TRUE,NULL,NULL),
							 m_RunEvent(FALSE,TRUE,NULL,NULL)
{
	m_pWorkThread = NULL;
	m_dwErrorCode = ERROR_SUCCESS;
}


CWorkPool::~CWorkPool(void)
{
}


CWorkPool* CWorkPool::GetInstance()
{
	return Singleton<CWorkPool>::Instance();
}


BOOL CWorkPool::Start(CWnd* pDlgMain)
{
	CSingleLock sl(&m_csWorkThread, TRUE);
	AFXASSUME(m_pWorkThread == NULL);
	AFXASSUME(pDlgMain != NULL);

	m_pDlgMain = pDlgMain;
	m_dwErrorCode = ERROR_SUCCESS;
	m_StopEvent.ResetEvent();
	m_RunEvent.ResetEvent();
	m_WorkStartEvent.ResetEvent();
	m_pWorkThread = AfxBeginThread(WorkFunction, this, THREAD_PRIORITY_NORMAL, 0, CREATE_SUSPENDED);
	if (m_pWorkThread == NULL)
	{
		CString sError(_T(""));
		sError.Format(_T("CWorkServer::Start, Failed to create monitor thread, please check settings, Error:%u"), ::GetLastError());
		OnError(sError);
		return FALSE;
	}

	m_pWorkThread->m_bAutoDelete = FALSE;
	m_pWorkThread->ResumeThread();
	m_RunEvent.SetEvent();
	WaitForSingleObject(m_WorkStartEvent, INFINITE);

	return (m_dwErrorCode == ERROR_SUCCESS);
}

BOOL CWorkPool::IsCreate()
{
	return (m_pWorkThread != NULL);
}


BOOL CWorkPool::Stop()
{
	m_StopEvent.SetEvent();

	CSingleLock sl(&m_csWorkThread, TRUE);
	if (m_pWorkThread != NULL)
	{
		WaitForSingleObject(m_pWorkThread->m_hThread, INFINITE);
		delete m_pWorkThread;
		m_pWorkThread = NULL;
	}

	return TRUE;
}


BOOL CWorkPool::Wait()
{
	CSingleLock sl(&m_csWorkThread, TRUE);

	if (m_pWorkThread != NULL)
	{
		WaitForSingleObject(m_pWorkThread->m_hThread, INFINITE);
		delete m_pWorkThread;
		m_pWorkThread = NULL;
		return TRUE;
	}
	else
	{
		//Report the error
		CString sError;
		sError.Format(_T("CWorkPool::Wait, server is not running, so no need to wait"));
		OnError(sError);
		return FALSE;
	}
}


UINT CWorkPool::WorkFunction(LPVOID pParam)
{
	CWorkPool* pWorkPool = static_cast<CWorkPool*>(pParam);
	AFXASSUME(pWorkPool != NULL);

	pWorkPool->WorkFunction();
	return TRUE;
}


void CWorkPool::WorkFunction()
{
	m_dwErrorCode = ERROR_SUCCESS;
	m_WorkStartEvent.SetEvent();
	HANDLE Handles[2];
	Handles[0] = m_StopEvent;
	Handles[1] = m_RunEvent;

	BOOL bWaitStop = FALSE;
	while (!bWaitStop)
	{
		DWORD dwWait = WaitForMultipleObjects(2,Handles,FALSE,INFINITE);
		int nSignalHandle = dwWait - WAIT_OBJECT_0;
		if (nSignalHandle == 0)			// stop
		{
			bWaitStop = TRUE;
		}
		else if (nSignalHandle == 1)	// run
		{
			Sleep(10);
			((CDlgMain*)m_pDlgMain)->Run();
		}
	}
}

void CWorkPool::OnError(const CString& sError)
{
#ifdef _DEBUG
	//The default is to just TRACE the details
	TRACE(_T("%s\n"), sError.operator LPCTSTR());
#else
	UNREFERENCED_PARAMETER(sError);
#endif //#ifdef _DEBUG
	AfxMessageBox(sError);
}


