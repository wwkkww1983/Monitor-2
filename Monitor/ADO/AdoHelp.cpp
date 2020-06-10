#include "StdAfx.h"
#include "AdoHelp.h"

#pragma warning (disable: 4146) 
#import "C:\Program Files\Common Files\System\ADO\msadox.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#import "C:\Program Files\Common Files\System\ADO\msado15.dll" named_guids rename("EOF","adoEOF"), rename("BOF","adoBOF")
#pragma warning (default:4146) 



CAdoHelp::CAdoHelp(void)
{

}

CAdoHelp::~CAdoHelp(void)
{
	
}

CAdoHelp* CAdoHelp::GetInstance()
{
	return Singleton<CAdoHelp>::Instance();
}

BOOL CAdoHelp::CreateDatabase()
{
	CString strMdb = CHGetExeDirPath()+_T("database.mdb");
	CFileFind  finder;
	if(finder.FindFile(strMdb))
		return TRUE;
	HRESULT hr = S_OK; 
	//Set ActiveConnection of Catalog to this string 
	CString strcnn(_T("Provider=Microsoft.JET.OLEDB.4.0;Data source = ") + strMdb); 

	try 
	{ 
		ADOX::_CatalogPtr m_pCatalog = NULL; 
		hr = m_pCatalog.CreateInstance(__uuidof(ADOX::Catalog)); 
		if(FAILED(hr)) 
		{ 
			_com_issue_error(hr); 
		} 
		else 
		{ 
			m_pCatalog->Create(_bstr_t(strcnn)); //Create MDB 
		} 
	} 
	catch(_com_error &e) 
	{ 
		//Notify the user of errors if any. 
		AfxMessageBox(_T("Create error")); 
		return FALSE;
	} 
	return TRUE;
}

void CAdoHelp::ClearDatabase()
{
	CString strSQL = _T("delete from ��ʪ��");
	Execute(strSQL);
}


//void CAdoHelp::SaveDatabase()
//{
//
//	POSITION pos = m_listData.GetHeadPosition();
//	while(pos!=NULL)
//	{
//		ST_DATA data = m_listData.GetNext(pos);
//		InsertTable(data.sTime,data.sTemperature,data.sHumidity);
//	} 
//}

//��Ʒ��
BOOL CAdoHelp::InsertTable(CString strTime, CString strTemperature, CString strHumidity)
{
	CString  strSql;
	strSql.Format(_T("INSERT INTO ��ʪ�� (ʱ��,�¶�,ʪ��) VALUES ( '%s', '%s', '%s')"), strTime, strTemperature, strHumidity);
	Execute(strSql);	
	return TRUE;
}


VOID CAdoHelp::DeleteRecord(CString strTime)
{
	CString strSQL;
	strSQL.Format(_T("delete from ��ʪ�� where ʱ�� = '%s' "), strTime);
	Execute(strSQL);
}



//�������ݵ�listctrl
BOOL CAdoHelp::LoadDataToList(CListCtrl& listctrl)
{

	CString strSql = _T("select * from ��ʪ��");
	CAdoRecordSet ret;	
 	ret.SetAdoConnection(this);
 	if(!ret.Open(strSql))
		return FALSE;
	if ( ret.GetRecordCount()==0 )
	{
		ret.Close();
		return FALSE;
	}
	int i = 0;
	while(!ret.IsEOF())	
	{
		ST_DATA data;
		ret.GetCollect(_T("ʱ��"), data.sTime);
		ret.GetCollect(_T("�¶�"), data.sTemperature);
		ret.GetCollect(_T("ʪ��"), data.sHumidity);		
		listctrl.InsertItem(i, data.sTime);
		listctrl.SetItemText(i, 1, data.sTemperature);
		listctrl.SetItemText(i, 2, data.sHumidity);
		i++;
		ret.MoveNext();	
	}
	ret.Close();
	return TRUE;
}