// SheetParam.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "Monitor.h"
#include "SheetParam.h"


// CSheetParam

IMPLEMENT_DYNAMIC(CSheetParam, CMFCPropertySheet)

CSheetParam::CSheetParam()
{
	m_psh.dwFlags &= ~PSH_HASHELP;

	m_Page1.m_psp.dwFlags&= ~PSP_HASHELP;
    m_Page2.m_psp.dwFlags&= ~PSP_HASHELP;

	SetLook (PropSheetLook_Tree);
	CMFCPropertySheetCategoryInfo* pCategory1 = AddTreeCategory (_T("��������"), 0, 1);
	AddPageToTree (pCategory1, &m_Page1, -1, 2);
	AddPageToTree (pCategory1, &m_Page2, -1, 2);

	
	
}


CSheetParam::~CSheetParam()
{
}


BEGIN_MESSAGE_MAP(CSheetParam, CMFCPropertySheet)
	ON_COMMAND(ID_APPLY_NOW, &CSheetParam::OnApplyNow)
END_MESSAGE_MAP()



// CSheetParam ��Ϣ�������




BOOL CSheetParam::OnInitDialog()
{

	m_bModeless = FALSE;
	m_nFlags |= WF_CONTINUEMODAL;

	ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	BOOL bResult = CMFCPropertySheet::OnInitDialog();
	m_bModeless = TRUE;
	m_nFlags &= ~WF_CONTINUEMODAL;
	// TODO:  �ڴ��������ר�ô���
	GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
	GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);

	//int ids [] = { IDOK, IDCANCEL, ID_APPLY_NOW };
 //  
 //   CRect rectBtn;
 //   int nSpacing = 0;       
 //
 //   for( int i =0; i < sizeof(ids)/sizeof(int); i++)
 //   {
 //       GetDlgItem (ids [i])->GetWindowRect (rectBtn);
 //      
 //       ScreenToClient (&rectBtn);
 //       int btnWidth = rectBtn.Width();
 //       rectBtn.left = rectBtn.left + (btnWidth + nSpacing)* 2;
 //       rectBtn.right = rectBtn.right + (btnWidth + nSpacing)* 2;
 //
 //       GetDlgItem (ids [i])->MoveWindow(rectBtn);
 //   }
 
	return bResult;
}


void CSheetParam::OnApplyNow()
{
	// TODO: �ڴ���������������
	m_Page1.XSaveCtrlValue();
}


