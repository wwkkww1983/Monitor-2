#pragma once
#include "SheetParam.h"
#include "afxcmn.h"

// CDlgParam 对话框

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgParam();

// 对话框数据
	enum { IDD = IDD_DLGPARAM };

	CSheetParam		m_wndSheetParam;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnParamSave();
	

};
