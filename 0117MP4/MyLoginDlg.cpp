// MyLoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyLoginDlg.h"
#include "afxdialogex.h"
#include "MyTools.h"
#include "Packdef.h"
#include "0117MP4Dlg.h"
// CMyLoginDlg 对话框

IMPLEMENT_DYNAMIC(CMyLoginDlg, CDialogEx)

CMyLoginDlg::CMyLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyLoginDlg::IDD, pParent)
	, m_userPasswd(_T(""))
	, m_userId(0)
{

}

CMyLoginDlg::~CMyLoginDlg()
{
}

void CMyLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	/*DDX_Text(pDX, IDC_EDIT1, m_userName);*/
	DDX_Text(pDX, IDC_EDIT2, m_userPasswd);
	DDX_Text(pDX, IDC_EDIT1, m_userId);
}


BEGIN_MESSAGE_MAP(CMyLoginDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON3, &CMyLoginDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMyLoginDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON8, &CMyLoginDlg::OnBnClickedButton8)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CMyLoginDlg 消息处理程序
BOOL CMyLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//定义画刷
	m_brush.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control

}

HBRUSH CMyLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return m_brush;
	}
	if(pWnd==GetDlgItem(IDC_EDIT1)||pWnd==GetDlgItem(IDC_EDIT2))
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(158,158,158));
		return m_brush;
	}
	return hbr;
}

//login
void CMyLoginDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if(m_userPasswd==_T(""))
		return;
	//校验账号和密码
	if(!CMyTools::CheckUserId(m_userId))
		return;
	if(!CMyTools::CheckUserPasswd(m_userPasswd))
		return;
	//向服务器发送登录消息
	LOGININFO loginInfo;
	loginInfo.RqType=UDP_LOGIN_RQ;
	loginInfo.uid=m_userId;
	char*temp=CMyTools::EnCodeWCHARToUtf(m_userPasswd.GetBuffer(0));
	strcpy_s(loginInfo.upasswd,temp);
	delete[] temp;
	theApp.getUDPMediator()->SendData((char*)&loginInfo,sizeof(loginInfo));
}

//cancel
void CMyLoginDlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	this->ShowWindow(SW_HIDE);
}

//register
void CMyLoginDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_registerDlg.ShowWindow(SW_SHOW);
}


BOOL CMyLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN){
		//回车键 登录
		OnBnClickedButton3();
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyLoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_brush.DeleteObject();
	// TODO: 在此处添加消息处理程序代码
}
