
// DlgMain.h : ͷ�ļ�
//

#pragma once
#include "DlgDatabase.h"

#include "DlgView.h"
#include "DlgParam.h"

#include "afxcmn.h"

// define
#define		WM_MSG_SWITCHWND	WM_USER + 100
#define		WND_MONITOR					0				// main �Ի���
#define		WND_DATABASE				1				// ���ݼ�¼�Ի���
#define		WND_PARAM					2				// �����Ի���

// CDlgMain �Ի���
class CDlgMain : public CDialogEx
{
// ����
public:
	CDlgMain(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_MAIN_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
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
	BOOL	InitSys();			// ��ʼ��������Դ
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
