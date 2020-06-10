#include "StdAfx.h"
#include "Monitor.h"
#include "ParamHelp.h"
#include "CHStrUtils.h"
#include "WorkFunc.h"



CParamHelp::CParamHelp(void)
{
}

CParamHelp::~CParamHelp(void)
{
}

CParamHelp* CParamHelp::GetInstance()
{
	return Singleton<CParamHelp>::Instance();
}

void CParamHelp::Refresh()
{
	ReadConnectRoot();
	ReadSerialRoot();
}

void CParamHelp::Save()
{
	WriteConnectRoot();
	WriteSerialRoot();
}




void CParamHelp::ReadConnectRoot()
{
	WRPF wrpf;
	wrpf.Load(CHGetExeDirPath()+_T("Param.ini"));
	wrpf.changeRoot(_T("System"));


	wrpf.rd(_T("m_nUpdateDelteTime"), m_nUpdateDelteTime);
}


void CParamHelp::WriteConnectRoot()
{
	WRPF wrpf;
	wrpf.Load(CHGetExeDirPath()+_T("Param.ini"));
	wrpf.changeRoot(_T("System"));


	wrpf.wt(_T("m_nUpdateDelteTime"), m_nUpdateDelteTime);
}


void CParamHelp::ReadSerialRoot()
{
	WRPF wrpf;
	wrpf.Load(CHGetExeDirPath() + _T("Param.ini"));
	wrpf.changeRoot(_T("Serial"));

	wrpf.rd(_T("m_nPort"), m_nPort);
	wrpf.rd(_T("m_nBaud"), m_nBaud);
	wrpf.rd(_T("m_nParity"), m_nParity);
	wrpf.rd(_T("m_nDataBits"), m_nDataBits);
	wrpf.rd(_T("m_nStopBits"), m_nStopBits);

}


void CParamHelp::WriteSerialRoot()
{
	WRPF wrpf;
	wrpf.Load(CHGetExeDirPath() + _T("Param.ini"));
	wrpf.changeRoot(_T("Serial"));

	wrpf.wt(_T("m_nPort"), m_nPort);
	wrpf.wt(_T("m_nBaud"), m_nBaud);
	wrpf.wt(_T("m_nParity"), m_nParity);
	wrpf.wt(_T("m_nDataBits"), m_nDataBits);
	wrpf.wt(_T("m_nStopBits"), m_nStopBits);

}


