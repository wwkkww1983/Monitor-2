#pragma once
#include "Singleton.h"
#include "WRPF.h"


#define CHParam		CParamHelp::GetInstance()

class CParamHelp 
{
public:
	friend class Singleton<CParamHelp>;

private:
	CParamHelp(void);
	~CParamHelp(void);

// var
public:
	// [SYSTEM]

	int	m_nUpdateDelteTime;
	// [Serial]
	int				m_nPort;
	int				m_nBaud;
	int				m_nParity;
	int				m_nDataBits;
	int				m_nStopBits;

private:

// func
public:
	void Refresh();
	void Save();

	void ReadConnectRoot();							// 读取
	void WriteConnectRoot();						// 写入

	void ReadSerialRoot();							// 读取【Serial】
	void WriteSerialRoot();							// 写入【Serial】
public:
	static CParamHelp* GetInstance();
	
};

