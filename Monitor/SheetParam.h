#pragma once
#include "PageParam1.h"
#include "PageParam2.h"

// CSheetParam

class CSheetParam : public CMFCPropertySheet
{
	DECLARE_DYNAMIC(CSheetParam)

public:
	CSheetParam();
	virtual ~CSheetParam();

public:
	CPageParam1	m_Page1;
	CPageParam2	m_Page2;
protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnApplyNow();

};


