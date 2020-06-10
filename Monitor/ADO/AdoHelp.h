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

	////存放温湿度数据
	//CList<ST_DATA>	m_listData;

public:

	static  CAdoHelp* GetInstance();

	BOOL CreateDatabase();
	void ClearDatabase();

//	void SaveDatabase();


	//插入数据
	BOOL InsertTable(CString strTime, CString strTemperature, CString strHumidity);
	
	//以时间为关键字，删除一条记录
	VOID DeleteRecord(CString strTime);

	//加载数据到list
	BOOL LoadDataToList(CListCtrl& listctrl);

};

