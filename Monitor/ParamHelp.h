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
	// [othoer]

	int				m_nTimeSpan;
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


	void ReadSerialRoot();							// 读取【Serial】参数
	void WriteSerialRoot();							// 写入【Serial】参数
	
	//备用
	void ReadOtherRoot();							// 读取【Other】参数
	void WriteOtherRoot();							// 写入【Other】参数
public:
	static CParamHelp* GetInstance();
	
};

