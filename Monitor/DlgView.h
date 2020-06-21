#pragma once
#include "ThermoMeter.h"

// CDlgView 对话框

class CDlgView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgView)

public:
	CDlgView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgView();

// 对话框数据
	enum { IDD = IDD_DLGVIEW };
//温度计图表
	CThermoMeter	m_ThermoMeter;
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

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
