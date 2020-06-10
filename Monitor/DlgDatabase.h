#pragma once
#include "afxcmn.h"


// CDlgDatabase �Ի���

class CDlgDatabase : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgDatabase)

public:
	CDlgDatabase(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgDatabase();

// �Ի�������
	enum { IDD = IDD_DLGDATABASE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	CListCtrl m_ListCtrl;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnClear();

	void UpdateList();
	afx_msg void OnBnClickedBtnUpdate();
	afx_msg void OnBnClickedBtnDelete();
};
