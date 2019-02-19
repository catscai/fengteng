// MyDownTaskDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyDownTaskDlg.h"
#include "afxdialogex.h"


// CMyDownTaskDlg 对话框

IMPLEMENT_DYNAMIC(CMyDownTaskDlg, CDialogEx)

CMyDownTaskDlg::CMyDownTaskDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDownTaskDlg::IDD, pParent)
{

}

CMyDownTaskDlg::~CMyDownTaskDlg()
{
}

void CMyDownTaskDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TAB1, m_tabCtrl);
}


BEGIN_MESSAGE_MAP(CMyDownTaskDlg, CDialogEx)
END_MESSAGE_MAP()


// CMyDownTaskDlg 消息处理程序


BOOL CMyDownTaskDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CString tabNames[3]={_T("正在下载"),_T("下载完成"),_T("本地历史")};
	m_tabCtrl.InitTabCtrl(3,tabNames);
	return TRUE;  // return TRUE unless you set the focus to a control

}

