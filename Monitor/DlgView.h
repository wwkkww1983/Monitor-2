#pragma once
#include "ThermoMeter.h"

// CDlgView �Ի���

class CDlgView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgView)

public:
	CDlgView(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDlgView();

// �Ի�������
	enum { IDD = IDD_DLGVIEW };
//�¶ȼ�ͼ��
	CThermoMeter	m_ThermoMeter;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnPaint();

protected:
	afx_msg LRESULT OnUserUpdateView(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
};
