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
	ReadSerialRoot();
	ReadOtherRoot();
}

void CParamHelp::Save()
{	
	WriteSerialRoot();
	WriteOtherRoot();
}




void CParamHelp::ReadOtherRoot()
{
	//WRPF wrpf;
	//wrpf.Load(CHGetExeDirPath()+_T("Param.ini"));
	//wrpf.changeRoot(_T("Other"));
	
}


void CParamHelp::WriteOtherRoot()
{
	//WRPF wrpf;
	//wrpf.Load(CHGetExeDirPath()+_T("Param.ini"));
	//wrpf.changeRoot(_T("Other"));
	
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

	wrpf.rd(_T("m_nTimeSpan"), m_nTimeSpan);
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

	wrpf.wt(_T("m_nTimeSpan"), m_nTimeSpan);
}


