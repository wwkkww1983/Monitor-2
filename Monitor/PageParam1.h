#pragma once
#include "afxwin.h"


// CPageParam1 对话框

class CPageParam1 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPageParam1)

public:
	CPageParam1();
	virtual ~CPageParam1();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_PARAM1 };

	CComboBox m_wndPort;
	CComboBox m_wndBaud;
	CComboBox m_wndDataBits;
	CComboBox m_wndParity;
	CComboBox m_wndStopBits;

	bool	GetAllSerialPorts(CStringArray& arrPorts);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();


	void XInitCtrlValue();
	void XSaveCtrlValue();

	virtual BOOL OnCommand(WPARAM wParam, LPARAM lParam);
};
