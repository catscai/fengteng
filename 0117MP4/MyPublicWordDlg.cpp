// MyPublicWordDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyPublicWordDlg.h"
#include "afxdialogex.h"


// CMyPublicWordDlg 对话框

IMPLEMENT_DYNAMIC(CMyPublicWordDlg, CDialogEx)

CMyPublicWordDlg::CMyPublicWordDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyPublicWordDlg::IDD, pParent)
{

}

CMyPublicWordDlg::~CMyPublicWordDlg()
{
}

void CMyPublicWordDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PUBLICWORD, m_publicBoard);
}


BEGIN_MESSAGE_MAP(CMyPublicWordDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyPublicWordDlg 消息处理程序


BOOL CMyPublicWordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//定义画刷
	m_brush.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control

}


HBRUSH CMyPublicWordDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd==GetDlgItem(IDC_PUBLICWORD))
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(158,158,158));
		return m_brush;
	}
	return hbr;
}


BOOL CMyPublicWordDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN)
	{
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyPublicWordDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_brush.DeleteObject();
	// TODO: 在此处添加消息处理程序代码
}
