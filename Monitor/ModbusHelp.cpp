#include "StdAfx.h"
#include "ModbusHelp.h"



CHModbusHelp::CHModbusHelp(void)
{
	m_bInit = FALSE;
}


CHModbusHelp::~CHModbusHelp(void)
{

}


CHModbusHelp* CHModbusHelp::GetInstance()
{
	return Singleton<CHModbusHelp>::Instance();
}


BOOL CHModbusHelp::Init(int uPort, int uBaud, int uParity, int uDataBits, int uStopBits)
{
	BOOL bRtn = m_ComModBus.InitCom(uPort, uBaud, uParity, uDataBits, uStopBits);
	
	return bRtn;
}






BOOL CHModbusHelp::WriteData()
{
	BOOL bRtn = FALSE;

	BYTE Hight, Low, LowPoint;
	Hight = _ttoi(_T("0"));
	Low = _ttoi(_T("0"));
	LowPoint = _ttoi(_T("2"));
	bRtn = m_ComModBus.SendRequest(Hight, Low, LowPoint);

	return bRtn;
}



BOOL CHModbusHelp::ReadData(double& fData1, double& fData2,DWORD dwWaitTime)
{
	int nData1, nData2;
	BOOL bRtn = m_ComModBus.Read4Byte(nData1, nData2, dwWaitTime);
	fData1 = (double) nData1 / 10.0;
	fData2 = (double) nData2 / 10.0;
	return bRtn;
}


