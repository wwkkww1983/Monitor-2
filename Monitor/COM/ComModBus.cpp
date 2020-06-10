#include "StdAfx.h"
#include "ComModBus.h"
#include <stdlib.h>

CComModBus::CComModBus(void)
{
}


CComModBus::~CComModBus(void)
{
}


BOOL CComModBus::IsOpen()
{
	return Com_.IsOpen();
}

BOOL CComModBus::InitCom(int nPort, int nBaudRate, int nParity, int nByteSize, int nStopBits)
{
	//nPort = 4;
	//nBaudRate = 9600;
	//nParity = NOPARITY;
	//nByteSize = 8;
	//nStopBits = ONESTOPBIT;
	Rx_.SetMinBlockSize(4096);

	if (!Com_.IsOpen())
	{
		if(Com_.Open(nPort,nBaudRate,nParity,nByteSize,nStopBits))
		{
			return TRUE;
		}
		AfxMessageBox(_T("串口打开失败"));
		return FALSE;
	}
	AfxMessageBox(_T("串口被占用！"));
	return FALSE;
}

//函数功能：计算CRC16
//参数1：*pData  16位CRC校验数据，
//参数2：nLength 数据流长度
//参数3：init    初始化值
//参数4：ptable  16位CRC查找表

//逆序CRC计算
unsigned short CComModBus::GetRevCrc_16(unsigned char * pData, int nLength, 
	unsigned short init, const unsigned short *ptable)
{
	unsigned short cRc_16 = init;
	unsigned char temp;

	while(nLength-- > 0)
	{
	temp = cRc_16 >> 8; 
	cRc_16 = (cRc_16 << 8) ^ ptable[(temp ^ *pData++) & 0xFF];
	}

	return cRc_16;    
}

//正序CRC计算
unsigned short CComModBus::GetCrc_16(unsigned char * pData, int nLength, 
	unsigned short init, const unsigned short *ptable)
{
	unsigned short cRc_16 = init;
	unsigned char temp;

	while(nLength-- > 0)
	{
	temp = cRc_16 & 0xFF; 
	cRc_16 = (cRc_16 >> 8) ^ ptable[(temp ^ *pData++) & 0xFF];
	}
	return cRc_16;
}

/*******发送指令****************/
//参数1 Hight		寄存器高地址
//参数2 Low			寄存器低地址
//参数3 LowPoint	读寄存器个数
//Slave addr | Function Code | Start Addr Hi | Start Addr Lo | 0x00 | Num of Point Lo | CRC
//0x01		 | 0x03			 | 0x01			 | 0x02			 | 0x00 | 0x02			  | CRC
BOOL CComModBus::SendRequest(BYTE Hight,BYTE Low,BYTE LowPoint)
{
	BYTE bchBuff[6];
	bchBuff[0] = 0x01;
	bchBuff[1] = 0x03;
	bchBuff[2] = Hight;
	bchBuff[3] = Low;
	bchBuff[4] = 0x00;
	bchBuff[5] = LowPoint;
	
	unsigned short Buf = {GetCrc_16(bchBuff,6,0xFFFF,g_McRctable_16)};

	BYTE SendBuf[8];
	SendBuf[0] = bchBuff[0];
	SendBuf[1] = bchBuff[1];
	SendBuf[2] = bchBuff[2];
	SendBuf[3] = bchBuff[3];
	SendBuf[4] = bchBuff[4];
	SendBuf[5] = bchBuff[5];
	SendBuf[6] = Buf & 0x00FF;
	SendBuf[7] = (Buf & 0xFF00) >>8;

	Com_.Write(SendBuf,sizeof(SendBuf));
	return TRUE;
}

/************16进制转换成IEEE754浮点型***************/
//1A 2B 3C 4D
//参数1 byHight1			高字节1A
//参数2 byHight2			高字节2B
//参数3 byLow1				低字节3C
//参数4 byLow2				低字节4D
float CComModBus::HexToIE754(BYTE byHight1,BYTE byHight2,BYTE byLow1,BYTE byLow2)
{
	IEEE result;
	result.bytes[3] = byHight1;
	result.bytes[2] = byHight2;
	result.bytes[1] = byLow1;
	result.bytes[0] = byLow2;
	return result.df;
}

//读UINT型
BOOL CComModBus::Read2Byte(CString& sRecvData)
{
	BYTE bchBuff[96];	
	Com_.Read(bchBuff,96);
	int Hig = bchBuff[3]<<8;
	int Low = bchBuff[4];
	sRecvData.Format(_T("%d"),Hig+Low);
	return TRUE;
}

//读浮点型
BOOL CComModBus::Read4Byte(CString& sRecvData)
{
	BYTE bchBuff[96];	
	float result;
	if(Com_.Read(bchBuff,96))
	{	
		if(bchBuff[1] == 0x83)
		{
			AfxMessageBox(_T("通信异常"));
			return FALSE;
		}
		result = HexToIE754(bchBuff[3],bchBuff[4],bchBuff[5],bchBuff[6]);
		sRecvData.Format(_T("%f"),result);
		return TRUE;
	}
	return FALSE;
}


BOOL CComModBus::Read4Byte(int& nData1, int& nData2, DWORD dwWaitTime )
{
	BYTE bchBuff[96];
	float result;
	if (Com_.Read(bchBuff, 96, dwWaitTime))
	{
		if (bchBuff[1] == 0x83)
		{
			AfxMessageBox(_T("通信异常"));
			return FALSE;
		}

		int Hig = bchBuff[3] << 8;
		int Low = bchBuff[4];
		nData1 = Hig + Low;

		int Hig2 = bchBuff[5] << 8;
		int Low2 = bchBuff[6];
		nData2 = Hig2 + Low2;
		return TRUE;
	}
	return FALSE;
}