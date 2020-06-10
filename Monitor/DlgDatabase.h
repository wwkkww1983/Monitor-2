#pragma once
#include "afxcmn.h"


// CDlgDatabase 对话框

class CDlgDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabase)

public:
	CDlgDatabase(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgDatabase();

// 对话框数据
	enum { IDD = IDD_DLGDATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnClear();

	void UpdateList();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnDelete();
};
