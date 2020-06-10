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
		AfxMessageBox(_T("���ڴ�ʧ��"));
		return FALSE;
	}
	AfxMessageBox(_T("���ڱ�ռ�ã�"));
	return FALSE;
}

//�������ܣ�����CRC16
//����1��*pData  16λCRCУ�����ݣ�
//����2��nLength ����������
//����3��init    ��ʼ��ֵ
//����4��ptable  16λCRC���ұ�

//����CRC����
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

//����CRC����
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

/*******����ָ��****************/
//����1 Hight		�Ĵ����ߵ�ַ
//����2 Low			�Ĵ����͵�ַ
//����3 LowPoint	���Ĵ�������
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

/************16����ת����IEEE754������***************/
//1A 2B 3C 4D
//����1 byHight1			���ֽ�1A
//����2 byHight2			���ֽ�2B
//����3 byLow1				���ֽ�3C
//����4 byLow2				���ֽ�4D
float CComModBus::HexToIE754(BYTE byHight1,BYTE byHight2,BYTE byLow1,BYTE byLow2)
{
	IEEE result;
	result.bytes[3] = byHight1;
	result.bytes[2] = byHight2;
	result.bytes[1] = byLow1;
	result.bytes[0] = byLow2;
	return result.df;
}

//��UINT��
BOOL CComModBus::Read2Byte(CString& sRecvData)
{
	BYTE bchBuff[96];	
	Com_.Read(bchBuff,96);
	int Hig = bchBuff[3]<<8;
	int Low = bchBuff[4];
	sRecvData.Format(_T("%d"),Hig+Low);
	return TRUE;
}

//��������
BOOL CComModBus::Read4Byte(CString& sRecvData)
{
	BYTE bchBuff[96];	
	float result;
	if(Com_.Read(bchBuff,96))
	{	
		if(bchBuff[1] == 0x83)
		{
			AfxMessageBox(_T("ͨ���쳣"));
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
			AfxMessageBox(_T("ͨ���쳣"));
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