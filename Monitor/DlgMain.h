
// DlgMain.h : 头文件
//

#pragma once
#include "DlgDatabase.h"

#include "DlgView.h"
#include "DlgParam.h"

#include "afxcmn.h"

// define
#define		WM_MSG_SWITCHWND	WM_USER + 100
#define		WND_MONITOR					0				// main 对话框
#define		WND_DATABASE				1				// 数据记录对话框
#define		WND_PARAM					2				// 参数对话框

// CDlgMain 对话框
class CDlgMain : public CDialogEx
{
// 构造
public:
	CDlgMain(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

protected:
	CImageList			m_ImageList;
	CTabCtrl			m_wndTab;
public:
	CDlgDatabase		m_wndDatabase;
	CDlgView			m_wndView;
	CDlgParam			m_wndParam;
public:
	BOOL	CreateChildWnd();
	LRESULT OnSwitchWnd(WPARAM wParam, LPARAM lParam);
	void	Run();
	BOOL	InitSys();			// 初始化所有资源
	BOOL    CloseSys();			//
	LRESULT OnLog(WPARAM wParam, LPARAM lParam);
	BOOL	InitLogList();


	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTcnSelchangeTab1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_listLog;
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnRun();
	afx_msg void OnBnClickedBtnStop();
};
