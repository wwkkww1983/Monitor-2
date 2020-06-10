#ifndef			__HPLCHELP_H__
#define			__HPLCHELP_H__

#include "Singleton.h"
#include <vector>
#include "COM\ComModBus.h"


using namespace std;

#define	 CHModbus		CHModbusHelp::GetInstance()


//typedef int (CALLBACK *FNTRIGGER)(LPARAM, LPARAM, LPARAM);
//#define SETBIT(a, b)		( a |=  (1 << b))
//#define CLRBIT(a, b)		( a &= ~(1 << b))
//#define GETBIT(a, b)		( (a >> b) & 1)


class CHModbusHelp
{
public:
	friend class Singleton<CHModbusHelp>;
	~CHModbusHelp(void);

private:
	CHModbusHelp(void);
	

// var 
public:
	BOOL				m_bInit;
private:

	CComModBus			m_ComModBus;
	
// func
public:
	static  CHModbusHelp* GetInstance();
	BOOL	Init(int uPort = 1, int uBaud = 115200, int uParity = NOPARITY, int uDataBits = 8, int uStopBits = ONESTOPBIT);

	BOOL	WriteData();

	BOOL	ReadData(double& nData1, double& nData2, DWORD dwWaitTime = INFINITE);

};

#endif			__HPLCHELP_H__