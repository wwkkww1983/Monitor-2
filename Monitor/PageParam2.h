#pragma once


// CPageParam2 �Ի���

class CPageParam2 : public CMFCPropertyPage
{
	DECLARE_DYNAMIC(CPageParam2)

public:
	CPageParam2();
	virtual ~CPageParam2();

// �Ի�������
	enum { IDD = IDD_PROPPAGE_PARAM2 };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
};
