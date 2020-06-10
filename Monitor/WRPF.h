#ifndef _WRPF_H
#define _WRPF_H

class WRPF  
{
public:
	WRPF();
	WRPF(LPCTSTR fname, bool throwError = true);
	~WRPF();
	void Load(LPCTSTR fname) {::_tcscpy_s(filename, fname);}
	void throwErrors(bool throwError = true) {throwErr = throwError;}
	inline void changeRoot(LPCTSTR newRoot);

	// action
	void rd(LPCTSTR pname, short &p);
	void rd(LPCTSTR pname, int &p);
	void rd(LPCTSTR pname, long &p);
	void rd(LPCTSTR pname, UINT &p);
	void rd(LPCTSTR pname, BYTE &p);
	void rd(LPCTSTR pname, WORD &p);
	void rd(LPCTSTR pname, DWORD &p);
	void rd(LPCTSTR pname, float &p);
	void rd(LPCTSTR pname, double &p);
	void rd(LPCTSTR pname, bool &p);
	void rd(LPCTSTR pname, CString &p);
	void rd(LPCTSTR pname, TCHAR* p, int nChar);

	void wt(LPCTSTR pname, int p);
	void wt(LPCTSTR pname, long p);
	void wt(LPCTSTR pname, UINT p);
	void wt(LPCTSTR pname, BYTE p);
	void wt(LPCTSTR pname, WORD p);
	void wt(LPCTSTR pname, DWORD p);
	void wt(LPCTSTR pname, float p);
	void wt(LPCTSTR pname, double p);
	void wt(LPCTSTR pname, bool p);
	void wt(LPCTSTR pname, LPCTSTR p);

protected:
	inline void errorHandle(bool ignore = false);
	inline void errorShow(bool ignore = false);
	void setFileType();
	void createXMLFile();
	void createRootNode();
	void createChildNode();
	const TCHAR* RootName() {return curRoot;}

private:
	TCHAR filename[MAX_PATH];
	bool throwErr;
	TCHAR curRoot[MAX_PATH];  // Root section-name of ini file
	//typedef enum {INI = 1, XML} eFILETYPE;
	//eFILETYPE fileType;

private:
	WRPF(const WRPF &another);            // no implementation
	WRPF& operator =(const WRPF &right);  // no implementation
};

inline void WRPF::errorHandle(bool ignore)
{
}

inline void WRPF::errorShow(bool ignore)
{
	/*if (!ignore)
	{
		DWORD dwErr = ::GetLastError();
		::MessageBox(
	}*/
}

inline void WRPF::changeRoot(LPCTSTR newRoot)
{
	if (::_tcslen(newRoot) >= MAX_PATH)
	{
		errorShow();
		return;
	}
	::_tcscpy_s(curRoot, newRoot);
}

#endif // _WRPF_H
