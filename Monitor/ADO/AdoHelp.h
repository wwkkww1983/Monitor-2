#pragma once
#include "ado.h"
#include "Singleton.h"

#include "common.h"

#define CHAdo				CAdoHelp::GetInstance()

class CAdoHelp :public CAdoConnection
{
public:
	friend class Singleton<CAdoHelp>;

public:
	CAdoHelp(void);
	~CAdoHelp(void);

	////�����ʪ������
	//CList<ST_DATA>	m_listData;

public:

	static  CAdoHelp* GetInstance();

	BOOL CreateDatabase();
	void ClearDatabase();

//	void SaveDatabase();


	//��������
	BOOL InsertTable(CString strTime, CString strTemperature, CString strHumidity);
	
	//��ʱ��Ϊ�ؼ��֣�ɾ��һ����¼
	VOID DeleteRecord(CString strTime);

	//�������ݵ�list
	BOOL LoadDataToList(CListCtrl& listctrl);

};

