// PageParam2.cpp : 实现文件
//

#include "stdafx.h"
#include "Monitor.h"
#include "PageParam2.h"
#include "afxdialogex.h"


// CPageParam2 对话框

IMPLEMENT_DYNAMIC(CPageParam2, CMFCPropertyPage)

CPageParam2::CPageParam2()
	: CMFCPropertyPage(CPageParam2::IDD)
{

}

CPageParam2::~CPageParam2()
{
}

void CPageParam2::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPageParam2, CPropertyPage)
END_MESSAGE_MAP()


// CPageParam2 消息处理程序
