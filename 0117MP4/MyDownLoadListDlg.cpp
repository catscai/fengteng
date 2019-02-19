



// MyDownLoadListDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyDownLoadListDlg.h"
#include "afxdialogex.h"


// CMyDownLoadListDlg 对话框

IMPLEMENT_DYNAMIC(CMyDownLoadListDlg, CDialogEx)

CMyDownLoadListDlg::CMyDownLoadListDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDownLoadListDlg::IDD, pParent)
{
	
}

CMyDownLoadListDlg::~CMyDownLoadListDlg()
{
}

void CMyDownLoadListDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROCESS_LIST, m_processList);
}


BEGIN_MESSAGE_MAP(CMyDownLoadListDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyDownLoadListDlg 消息处理程序


BOOL CMyDownLoadListDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	
	CRect rect;
	m_processList.GetWindowRect(&rect);
	int nWidth=rect.Width()/4;
	m_processList.InsertColumn(0,_T("名称"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(1,_T("进度"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(2,_T("大小"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(3,_T("状态"), LVCFMT_LEFT,nWidth);
	//创建画刷
	m_BrushBk.CreateSolidBrush(RGB(158,158,158));
	//skinppSetNoSkinHwnd(m_processList.GetSafeHwnd());
	//HWND hwnd = this->UnsubclassWindow();
	//skinppSetNoSkinHwnd(hwnd);
	//this->SubclassWindow(hwnd);
	//m_processList.SetItemText(0,2,_T("45"));
	return TRUE;  // return TRUE unless you set the focus to a control

}


HBRUSH CMyDownLoadListDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	//if(GetDlgItem(IDC_PROCESS_LIST)==pWnd)
	//{
	//	pDC->SetTextColor(RGB(255,255,255));
	//	pDC->SetBkColor(RGB(158,158,158));
	//	return m_BrushBk;
	//}
	return hbr;
}


void CMyDownLoadListDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_BrushBk.DeleteObject();
	// TODO: 在此处添加消息处理程序代码
}
