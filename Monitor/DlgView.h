#pragma once


// CDlgView 对话框

class CDlgView : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgView)

public:
	CDlgView(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgView();

// 对话框数据
	enum { IDD = IDD_DLGVIEW };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
private:
	COLORREF m_clrAlarmT;
	COLORREF m_clrAlarmH;
public:
	afx_msg void OnPaint();
	void DrawAxis(CDC* pDC);
	void DrawHermometer(CDC* pDC);
	void DrawAlarmT(CDC* pDC);
	void DrawAlarmH(CDC* pDC);
	void DrawLine(CDC* pDC, int x1, int y1, int x2, int y2);
protected:
	afx_msg LRESULT OnUserUpdateView(WPARAM wParam, LPARAM lParam);
public:
	virtual BOOL OnInitDialog();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
};
