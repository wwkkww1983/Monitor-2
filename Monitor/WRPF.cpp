// WRPF.cpp: implementation of the WRPF class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "WRPF.h"

WRPF::WRPF()
{
	::memset(filename, '\0', MAX_PATH*sizeof(TCHAR));
	throwErr = true;
	::memset(curRoot, '\0', MAX_PATH*sizeof(TCHAR));
	::_tcscpy_s(curRoot, _T("Parameters")); // default root section-name of ini file
}

WRPF::WRPF(LPCTSTR fname, bool throwError)
{
	::memset(filename, '\0', MAX_PATH*sizeof(TCHAR));
	::memset(curRoot, '\0', MAX_PATH*sizeof(TCHAR));
	::_tcscpy_s(curRoot, _T("Parameters"));
	::_tcscpy_s(filename, fname);
	throwErr = throwError;
}

WRPF::~WRPF()
{

}

// action
void WRPF::rd(LPCTSTR pname, short &p)
{
	p = (int)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, int &p)
{
	p = (int)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, long &p)
{
	p = (long)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, UINT &p)
{
	p = ::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, BYTE &p)
{
	p = (BYTE)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, WORD &p)
{
	p = (WORD)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, DWORD &p)
{
	p = (DWORD)::GetPrivateProfileInt(curRoot, pname, 0, filename);
}

void WRPF::rd(LPCTSTR pname, float &p)
{
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::GetPrivateProfileString(curRoot, pname, _T("0"), buf, MAX_PATH, filename);
	p = (float)::_tcstod(buf, NULL);
}

void WRPF::rd(LPCTSTR pname, double &p)
{
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::GetPrivateProfileString(curRoot, pname, _T("0"), buf, MAX_PATH, filename);
	p = ::_tcstod(buf, NULL);
}

void WRPF::rd(LPCTSTR pname, bool &p)
{
	UINT nValue;
	nValue = ::GetPrivateProfileInt(curRoot, pname, 0, filename);
	p = (0 == nValue)? false : true;
}

void WRPF::rd(LPCTSTR pname, CString &p)
{
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::GetPrivateProfileString(curRoot, pname, _T("0"), buf, MAX_PATH, filename);
	p = buf;
}

void WRPF::rd(LPCTSTR pname, TCHAR* p, int nChar)
{
	if (NULL == p || nChar < 0)
	{
		errorShow();
		return;
	}
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::GetPrivateProfileString(curRoot, pname, _T("0"), buf, MAX_PATH, filename);
	::_tcsncpy_s(p, MAX_PATH,buf, nChar);
}

void WRPF::wt(LPCTSTR pname, int p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%d"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, long p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%d"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, UINT p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%u"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, BYTE p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%u"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, WORD p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%u"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, DWORD p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%u"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, float p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%.4f"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, double p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%.8f"), p);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, bool p)
{
	BOOL ret = 0;
	TCHAR buf[MAX_PATH] = {_T('\0')};
	::_stprintf_s(buf, _T("%d"), p? 1 : 0);
	ret = ::WritePrivateProfileString(curRoot, pname, buf, filename);
	if (0 == ret)
		errorHandle(false);
}

void WRPF::wt(LPCTSTR pname, LPCTSTR p)
{
	BOOL ret = 0;
	ret = ::WritePrivateProfileString(curRoot, pname, p, filename);
	if (0 == ret)
		errorHandle(false);
}