#pragma once
#include "SheetParam.h"
#include "afxcmn.h"

// CDlgParam �Ի���

class CDlgParam : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgParam)

public:
	CDlgParam(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgParam();

// �Ի�������
	enum { IDD = IDD_DLGPARAM };

	CSheetParam		m_wndSheetParam;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnParamSave();
	

};
