#ifndef _CH_STRIUTILS_H__
#define _CH_STRIUTILS_H__

#pragma once
#include <locale.h>

#define CHGetExeFilePath	CHStrUtils::GetExeFilePath
#define CHGetExeDirPath		CHStrUtils::GetExeDirPath
#define CHBuildPath			CHStrUtils::BuildPath
#define CHMessageBox		CHStrUtils::MessageBox
#define CHGetNameFromPath	CHStrUtils::GetNameFromPath
#define CHFilsIsExist		CHStrUtils::FileIsExist
#define CHReadFile			CHStrUtils::ReadFile
#define CHSplitString		CHStrUtils::SplitString
#define CHEnumFolders		CHStrUtils::EnumerateFolders
#define CHSearchFiles		CHStrUtils::SearchFiles
#define CHUTF8ToCString		CHStrUtils::UTF8ToCString
#define CHXWriteFile		CHStrUtils::XWriteFile
#define CHGetIntFromString	CHStrUtils::GetIntFromString
#ifndef Char2WChar
#define Char2WChar(lpMultiByteStr,cbMultiByte,lpWideCharStr,cbWideChar) \
	MultiByteToWideChar(CP_ACP/*代码页*/, 0, lpMultiByteStr/*ANSI字符串*/, cbMultiByte/*ANSI字符串大小*/, lpWideCharStr/*Unicode字符串缓冲区*/, cbWideChar/*Unicode字符串字符串缓冲区*/)
#endif

#ifndef WChar2Char
#define WChar2Char(lpWideCharStr,cbWideChar,lpMultiByteStr,cbMultiByte) \
	WideCharToMultiByte(CP_ACP/*代码页*/, 0, lpWideCharStr/*Unicode字符串*/, cbWideChar/*Unicode字符串大小*/, lpMultiByteStr/*ANSI字符串缓冲区*/, cbMultiByte/*ANSI字符串缓冲区大小*/, NULL, NULL)
#endif


class CHStrUtils
{
public:
	// 得到当前可执行文件的路径
	static void GetExeFilePath(CString& strPath)
	{
		LPTSTR lpBuffer = strPath.GetBuffer(MAX_PATH);
		ULONG nNameLen = ::GetModuleFileName(NULL, lpBuffer, MAX_PATH);
		strPath.ReleaseBuffer(nNameLen);
	}

	static CString GetExeFilePath()
	{
		CString strRet;
		GetExeFilePath(strRet);
		return strRet;
	}

	// 得到当前可执行文件所在目录的路径
	static void GetExeDirPath(CString& strPath)
	{
		LPTSTR lpBuffer = strPath.GetBuffer(MAX_PATH);
		ULONG nNameLen = ::GetModuleFileName(NULL, lpBuffer, MAX_PATH);
		while(lpBuffer[nNameLen] != _T('\\') ) 
			--nNameLen;
		strPath.ReleaseBuffer(nNameLen+1);
	}
	static CString GetExeDirPath()
	{
		CString strRet;
		GetExeDirPath(strRet);
		return strRet;
	}

	// 得到与本程序的绝对路径,并和szFileName组成新路径,赋给szBuffer
	static CString BuildPath(const CString& strFileName)
	{
		CString strRet;
		GetExeDirPath(strRet);
		return strRet + strFileName;
	}

	//得到与本程序的绝对路径,并和szFileName组成新路径,赋给szBuffer
	static void BuildPath(TCHAR *szBuffer, TCHAR *szFileName)
	{
		GetModuleFileName(NULL, szBuffer, MAX_PATH);
		int i = _tcslen(szBuffer)-1;
		while(szBuffer[i] != '\\') i--;
		szBuffer[i] = 0;
		_tcscat_s(szBuffer,MAX_PATH, _T("\\"));
		_tcscat_s(szBuffer, MAX_PATH,szFileName);
	}

	static int MessageBox(LPCTSTR lpszFormat, ...)
	{
		ASSERT(AfxIsValidString(lpszFormat));

		CString str;

		va_list argList;
		va_start(argList, lpszFormat);
		str.FormatV(lpszFormat, argList);
		va_end(argList);

		return AfxMessageBox(str, MB_ICONINFORMATION | MB_OK);
	}

	// 得到路径中的文件名
	static CString GetNameFromPath(const CString& strPath)
	{
		int nTemp=0, nStart=0;
		while(TRUE)
		{
			nTemp = strPath.Find(_T("\\"), nTemp);
			if(nTemp == -1)
				break;
			nStart = nTemp++;
		}
	
		if(nStart != -1)
			return strPath.Mid(nStart+1);
		else
			return strPath;
	}

	//判断文件是否存在
	static BOOL FileIsExist(LPCTSTR pstrName)
	{
		CFileFind finder;
		return finder.FindFile(pstrName);
	}

	// 把文件读入到字符串中
	static BOOL ReadFile(const CString& strFile, CString& strBuffer)
	{
		CFile file;
		if(!file.Open(strFile, CFile::modeRead | CFile::shareDenyNone))
			return false;

		const ULONG nFileLen = (ULONG)file.GetLength();
		LPTSTR lpBuffer = strBuffer.GetBuffer(nFileLen);

		ULONG nReaded = 0, nTemp = 0;
		while(TRUE)
		{
			nTemp = file.Read(lpBuffer + nReaded, nFileLen - nReaded);
			nReaded += nTemp;
			if(nReaded >= nFileLen)	break;
		}

		ASSERT(nReaded == nFileLen);
		strBuffer.ReleaseBuffer(nFileLen);

		file.Close();
		return true;
	}

	static BOOL ReadFile(const CString strFileName, CStringArray& strArText)
	{
		try
		{
			CStdioFile mFile;
			CFileFind  fFind;
			BOOL bSuccess = fFind.FindFile(strFileName);
			fFind.Close();
			if (bSuccess)
			{
				CString str(_T(""));
				mFile.Open(strFileName, CFile::modeRead);
				while (FALSE != mFile.ReadString(str) || 0 != str.GetLength())
				{
					strArText.Add(str);
				}
				mFile.Close();
			}
		}
		catch (...)
		{
			return FALSE;
		}

		return TRUE;
	}

	// 枚举文件夹
	static int EnumerateFolders(CString strParentDir, CStringArray& arStrFolders)
	{
		CFileFind fFind;
		CString   strFilePath(strParentDir);
		strFilePath += _T("\\*.*");
		CString strFolder(_T(""));
		
		BOOL bFind = fFind.FindFile(strFilePath);
		while (bFind)
		{
			bFind = fFind.FindNextFile();
			if (fFind.IsDirectory() && !fFind.IsDots())			// 找到的是文件夹
			{
				strFolder = fFind.GetFilePath();
				int nIndex = strFolder.ReverseFind('\\');
				
				strFolder = strFolder.Right(strFolder.GetLength() - (nIndex + 1));
				arStrFolders.Add(strFolder);				
			}
		}
		
		fFind.Close();
		return 0;
	}

	// 搜索文件
	static int SearchFiles(CString strRoot, CStringArray& arStrFile, CString sExt)
	{
		CFileFind fFind;
		CString   strFilePath(strRoot);
		strFilePath += _T("*.");
		strFilePath += sExt;
		CString strFolder(_T(""));
		
		BOOL bFind = fFind.FindFile(strFilePath);
		while (bFind)
		{
			bFind = fFind.FindNextFile();
			strFolder = fFind.GetFilePath();
			if (fFind.IsDirectory() && !fFind.IsDots())       // 找到的是文件夹
			{
				SearchFiles(strRoot, arStrFile, sExt);              // 递归
			}
			else if (!fFind.IsDirectory() && !fFind.IsDots()) // 找到的是文件
			{
				CString strFile(strFolder);
				int nIndex = strFile.ReverseFind('\\');
				strFile = strFile.Right(strFile.GetLength() - (nIndex + 1));
				nIndex = strFile.Find('.');
				strFile = strFile.Left(nIndex);
				
				BOOL bFlag = TRUE;
				int  nCount = arStrFile.GetSize();
				for (int i = 0; i < nCount; i++){
					if (strFile == arStrFile.GetAt(i))
						bFlag = FALSE;
				}
				
				if (bFlag){
					arStrFile.Add(strFile);
				}
			}
		}
		
		fFind.Close();
		
		return 0;
	}


	static CString SplitString(const CString& strString, const CString& strSplit, int& nStart)
	{
		ASSERT(strSplit.GetLength() > 0);

		if(nStart < 0 || nStart > strString.GetLength())
		{
			nStart = -1;
			return _T("");
		}

		int nPos = strString.Find(strSplit, nStart);
		if(nPos == -1) nPos = strString.GetLength();
		ASSERT(nPos >= nStart);

		CString strResult = strString.Mid(nStart, nPos - nStart);
		nStart = nPos + strSplit.GetLength();
		return strResult;
	}

	static void SplitString(const CString& strString, const CString& strSplit, CStringArray& arStr)
	{
		int nStart = 0;
		ASSERT(strSplit.GetLength() > 0);

		arStr.RemoveAll();
		while (TRUE)
		{
			if(nStart < 0 || nStart > strString.GetLength())
			{
				nStart = -1;
				break;
			}

			int nPos = strString.Find(strSplit, nStart);
			if(nPos == -1) nPos = strString.GetLength();
			ASSERT(nPos >= nStart);

			CString strResult = strString.Mid(nStart, nPos - nStart);
			nStart = nPos + strSplit.GetLength();
			arStr.Add(strResult);
		}

		return ;
	}

	static int XSearchFile(CString strRoot, CStringArray& arStrFile)
	{
		CFileFind fFind;
		CString   strFilePath(strRoot);
		strFilePath += _T("*.ini");
		CString strFolder(_T(""));

		BOOL bFind = fFind.FindFile(strFilePath);
		while (bFind)
		{
			bFind = fFind.FindNextFile();
			strFolder = fFind.GetFilePath();
			if (fFind.IsDirectory() && !fFind.IsDots())       // 找到的是文件夹
			{
				XSearchFile(strRoot, arStrFile);              // 递归
			}
			else if (!fFind.IsDirectory() && !fFind.IsDots()) // 找到的是文件
			{
				CString strFile(strFolder);
				int nIndex = strFile.ReverseFind('\\');
				strFile = strFile.Right(strFile.GetLength() - (nIndex + 1));
				nIndex = strFile.Find('.');
				strFile = strFile.Left(nIndex);

				BOOL bFlag = TRUE;
				int  nCount = arStrFile.GetCount();
				for (int i = 0; i < nCount; i++){
					if (strFile == arStrFile.GetAt(i))
						bFlag = FALSE;
				}

				if (bFlag){
					arStrFile.Add(strFile);
				}
			}
		}

		fFind.Close();

		return 0;
	}


	static int XWriteFile(CString strFileName, CString strText)
	{
		try
		{
			setlocale(LC_CTYPE, "CHS");
			CStdioFile mFile;
			CFileFind  fFind;
			BOOL bSuccess = fFind.FindFile(strFileName);
			fFind.Close();
			if (!bSuccess)
			{
				mFile.Open(strFileName, CFile::modeCreate);
				mFile.Close();
			}

			mFile.Open(strFileName, CFile::modeWrite);
			mFile.SeekToEnd();
			mFile.WriteString(strText);
			mFile.Close();
		}
		catch (...)
		{
			AfxMessageBox(_T("温馨提示：当前保存文件的路径不存在！"));
		}

		return 0;
	}


	static BOOL XCreateProFolder(CString strProductName)
	{
		CString strFolder = strProductName;
		CString strProPath(_T(""));

//		strProPath = theApp.m_strModulePath + _T("ProductCFG\\");
		strFolder = strProPath + strFolder;
		if (!PathFileExists(strFolder))
		{
			CreateDirectory(strFolder, NULL);

			CString strImageOKFolder(_T("\\ImageOK"));
			CString strImageNGFolder(_T("\\ImageNG"));
			CString strImageSavePath(_T(""));

			// 创建OK图像保存目录
			strImageSavePath = strFolder + strImageOKFolder;
			if (!PathFileExists(strImageSavePath)){
				CreateDirectory(strImageSavePath, NULL);
			}
			// 创建NG图像保存目录
			strImageSavePath = strFolder + strImageNGFolder;
			if (!PathFileExists(strImageSavePath)){
				CreateDirectory(strImageSavePath, NULL);
			}
			// 创建INI配置文件
		}
		else
		{
			AfxMessageBox(_T("该产品型号已经存在！"));
			return FALSE;
		}

		return TRUE;
	}

	static CString UTF8ToCString(_In_ const CString& sText)
	{
		//First call the function to determine how much space we need to allocate
		CStringA sAsciiText(sText);
		int nWideLength = MultiByteToWideChar(CP_UTF8, 0, sAsciiText, -1, NULL, 0);

		//If the calculated length is zero, then ensure we have at least room for a NULL terminator
		if (nWideLength == 0)
			nWideLength = 1;

		//Now recall with the buffer to get the converted text
		CStringW sWideString;
		wchar_t* pszWText = sWideString.GetBuffer(nWideLength);
		MultiByteToWideChar(CP_UTF8, 0, sAsciiText, -1, pszWText, nWideLength);
		sWideString.ReleaseBuffer();

		return CString(sWideString);
	}

	static CString CStringToUTF8(_In_ const CString& sText)
	{
		//First call the function to determine how much space we need to allocate
		CStringW sUnicodeText(sText);
		int nAsciiLength = WideCharToMultiByte(CP_UTF8, 0, sUnicodeText, -1, NULL, 0, NULL, NULL);

		//If the calculated length is zero, then ensure we have at least room for a NULL terminator
		if (nAsciiLength == 0)
			nAsciiLength = 1;

		//Now recall with the buffer to get the converted text
		CStringA sAsciiString;
		char* pszAsciiText = sAsciiString.GetBuffer(nAsciiLength);
		WideCharToMultiByte(CP_UTF8, 0, sUnicodeText, -1, pszAsciiText, nAsciiLength, NULL, NULL);
		sAsciiString.ReleaseBuffer();

		return CString(sAsciiString);
	}
	//提取出字符串中包含的整数
	static int GetIntFromString(_In_ const CString sText)
	{
		int nResult = 0;
		for(int i=0;i<sText.GetLength();i++)
		{
			if(sText[i]>= '0'&&sText[i]<= '9')
				nResult = nResult*10 + sText[i]-'0';
		}		

		return nResult;
	}
};

#endif //_CH_STRIUTILS_H__
