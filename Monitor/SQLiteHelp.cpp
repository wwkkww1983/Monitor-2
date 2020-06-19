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
	//���������db�ļ��򴴽�һ�����ݿ�
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

//����
BOOL	CSQLiteHelp::CreateDatabase()
{

	CString strDBPath = CHGetExeDirPath() + _T("database.db");
	
	try
	{
		m_database.open(strDBPath);
		CString strSQL = _T("CREATE TABLE ��ʪ�� (\
							ʱ�� TEXT PRIMARY KEY	\
							UNIQUE	\
							NOT NULL,	\
							�¶� TEXT,	\
							ʪ�� TEXT)");
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
		CString strSQL = _T("delete from ��ʪ��");
		m_database.execDML(strSQL);	
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}
	return TRUE;
}

//����
BOOL CSQLiteHelp::InsertTable(CString strTime, CString strTemperature, CString strHumidity)
{
	CString  strSql;
	strSql.Format(_T("INSERT INTO ��ʪ�� (ʱ��,�¶�,ʪ��) VALUES ( '%s', '%s', '%s')"), strTime, strTemperature, strHumidity);
	m_database.execDML(strSql);	
	return TRUE;
}

//ɾ��
BOOL CSQLiteHelp::DeleteRecord(CString strTime)
{
	CString strSQL;
	try
	{
		strSQL.Format(_T("delete from ��ʪ�� where ʱ�� = '%s' "), strTime);
		m_database.execDML(strSQL);
	}
	catch(CppSQLite3Exception e)
	{		
		AfxMessageBox(e.errorMessage());
		return FALSE;
	}
	return TRUE;
}



//�������ݵ�listctrl
BOOL CSQLiteHelp::LoadDataToList(CListCtrl& listctrl)
{
	
	try
	{
		if(m_database.tableExists(_T("��ʪ��")))
		{
			CString strSql = _T("select * from ��ʪ��");
			CppSQLite3Query dbQuery = m_database.execQuery(strSql);
	
			int i = 0;
			while(!dbQuery.eof())
			{
				ST_DATA data;
				data.sTime		= dbQuery.getStringField(_T("ʱ��"));
				data.sTemperature = dbQuery.getStringField(_T("�¶�"));
				data.sHumidity	= dbQuery.getStringField(_T("ʪ��"));
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