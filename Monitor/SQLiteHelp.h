#pragma once
#include "sqlite3\CppSQLite3U.h"
#include "Singleton.h"
#include "common.h"

#define CHSQLite				CSQLiteHelp::GetInstance()

class CSQLiteHelp
{
public:
	friend class Singleton<CSQLiteHelp>;

	static  CSQLiteHelp* GetInstance();
private:
	CSQLiteHelp(void);
	~CSQLiteHelp(void);
protected:
	CppSQLite3DB m_database;

public:
	BOOL		Open(CString strDBPath);
	void		Close();

	BOOL		CreateDatabase();
	BOOL		ClearDatabase();
	BOOL		InsertTable(CString strTime, CString strTemperature, CString strHumidity);
	//以时间为关键字，删除一条记录
	BOOL		DeleteRecord(CString strTime);

	//加载数据到listctrl
	BOOL		LoadDataToList(CListCtrl& listctrl);
};

