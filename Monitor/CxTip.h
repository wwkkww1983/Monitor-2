#pragma once

#define TIP(msg)		CxTip::Instance().Tip(CxTip::CX_TIP_MESSAGE,msg)
#define TIP_ERR(msg)	CxTip::Instance().Tip(CxTip::CX_TIP_ERROR,msg)
#define WM_CX_TIP		WM_USER + 500

class CxTip
{
public:
	CxTip(BOOL &alive) : _bAlive(alive)
	{
		_bAlive = TRUE;
		_hWnd = NULL;
	}

	~CxTip(void)
	{
		_bAlive = FALSE;
		_hWnd = NULL;
	}


	static CxTip& Instance()
	{
		static BOOL alive = FALSE;
		static CxTip tip(alive);

		if(!alive)
		{
			OutputDebugString(_T("CxTip has destroy!"));
		}

		return tip;
	}

// var
public:
	enum EnumType
	{
		CX_TIP_MESSAGE = 0,
		CX_TIP_ERROR
	};
	CString		_sMsg;

protected:
	BOOL&		_bAlive;
	HWND		_hWnd;

// func
public:
	void SetWnd(HWND hWnd)
	{
		_hWnd = hWnd;
	}

	void Tip(EnumType enTipType, CString sMsg)
	{
		_sMsg = sMsg;
		if(IsWindow(_hWnd))
		{
			PostMessage(_hWnd, WM_CX_TIP, 0, (LPARAM)enTipType);
		}
	}
};

