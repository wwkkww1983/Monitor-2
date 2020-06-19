#pragma once


// CPageParam2 对话框

class CPageParam2 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPageParam2)

public:
	CPageParam2();
	virtual ~CPageParam2();

// 对话框数据
	enum { IDD = IDD_PROPPAGE_PARAM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
