#include "StdAfx.h"
#include "SQLiteHelp.h"


CSQLiteHelp::CSQLiteHelp(void)
{
}


CSQLiteHelp::~CSQLiteHelp(void)
{
}

CSQLiteHelp* CSQLiteHelp::GetInstance()
{
	return Singleton<CSQLiteHelp>::Instance();
}

BOOL		CSQLiteHelp::Open(CString strDBPath)
{
	CFileFind  finder;
	//如果不存在db文件则创建一个数据库
	if(!finder.FindFile(strDBPath))
		return CreateDatabase();

	try
	{
		m_database.open(strDBPath);		
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}
	return TRUE;
}

void		CSQLiteHelp::Close()
{
	m_database.close();
}

//创建
BOOL	CSQLiteHelp::CreateDatabase()
{

	CString strDBPath = CHGetExeDirPath() + _T("database.db");
	
	try
	{
		m_database.open(strDBPath);
		CString strSQL = _T("CREATE TABLE 温湿度 (\
							时间 TEXT PRIMARY KEY	\
							UNIQUE	\
							NOT NULL,	\
							温度 TEXT,	\
							湿度 TEXT)");
		m_database.execDML(strSQL);

	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}

	CFileFind  finder;
	if(finder.FindFile(strDBPath))
		return TRUE;
	return FALSE;
}

BOOL CSQLiteHelp::ClearDatabase()
{
	
	try
	{
		CString strSQL = _T("delete from 温湿度");
		m_database.execDML(strSQL);	
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}
	return TRUE;
}

//插入
BOOL CSQLiteHelp::InsertTable(CString strTime, CString strTemperature, CString strHumidity)
{
	CString  strSql;
	strSql.Format(_T("INSERT INTO 温湿度 (时间,温度,湿度) VALUES ( '%s', '%s', '%s')"), strTime, strTemperature, strHumidity);
	m_database.execDML(strSql);	
	return TRUE;
}

//删除
BOOL CSQLiteHelp::DeleteRecord(CString strTime)
{
	CString strSQL;
	try
	{
		strSQL.Format(_T("delete from 温湿度 where 时间 = '%s' "), strTime);
		m_database.execDML(strSQL);
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}
	return TRUE;
}



//加载数据到listctrl
BOOL CSQLiteHelp::LoadDataToList(CListCtrl& listctrl)
{
	
	try
	{
		if(m_database.tableExists(_T("温湿度")))
		{
			CString strSql = _T("select * from 温湿度");
			CppSQLite3Query dbQuery = m_database.execQuery(strSql);
	
			int i = 0;
			while(!dbQuery.eof())
			{
				ST_DATA data;
				data.sTime		= dbQuery.getStringField(_T("时间"));
				data.sTemperature = dbQuery.getStringField(_T("温度"));
				data.sHumidity	= dbQuery.getStringField(_T("湿度"));
				listctrl.InsertItem(i, data.sTime);
				listctrl.SetItemText(i, 1, data.sTemperature);
				listctrl.SetItemText(i, 2, data.sHumidity);
				i++;
				dbQuery.nextRow();
			}

		}
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}

	return TRUE;
}