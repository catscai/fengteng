// SerachDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "SerachDlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "MyTools.h"

// CSerachDlg 对话框

IMPLEMENT_DYNAMIC(CSerachDlg, CDialogEx)

CSerachDlg::CSerachDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSerachDlg::IDD, pParent)
{

}

CSerachDlg::~CSerachDlg()
{
}

void CSerachDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_SerachLst);
}


BEGIN_MESSAGE_MAP(CSerachDlg, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST1, &CSerachDlg::OnLbnDblclkList1)
	ON_WM_KILLFOCUS()
	ON_LBN_KILLFOCUS(IDC_LIST1, &CSerachDlg::OnLbnKillfocusList1)
END_MESSAGE_MAP()


// CSerachDlg 消息处理程序


BOOL CSerachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_SerachLst.SetHorizontalExtent(500);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CSerachDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=m_SerachLst.GetCurSel();
	if(index<0)
		return;
	//向服务器请求 该视频的相关信息
	CString movName;
	m_SerachLst.GetText(index,movName);
	if(movName==_T(""))
		return;
	SERACHMOVIERQ info;
	info.RqType=SERACH_MOVIEINFO_RQ;
	char*temp=CMyTools::EnCodeWCHARToUtf(movName.GetBuffer());
	strcpy_s(info.movieName,temp);
	delete[] temp;

	theApp.getUDPMediator()->SendData((char*)&info,sizeof(info));
}


void CSerachDlg::OnKillFocus(CWnd* pNewWnd)
{
	CDialogEx::OnKillFocus(pNewWnd);

	// TODO: 在此处添加消息处理程序代码
	//this->ShowWindow(SW_HIDE);
}


void CSerachDlg::OnLbnKillfocusList1()
{
	// TODO: 在此添加控件通知处理程序代码
	//this->ShowWindow(SW_HIDE);
}
