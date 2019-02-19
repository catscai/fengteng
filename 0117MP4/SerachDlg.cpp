// SerachDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "SerachDlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "MyTools.h"

// CSerachDlg �Ի���

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


// CSerachDlg ��Ϣ�������


BOOL CSerachDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_SerachLst.SetHorizontalExtent(500);
	return TRUE;  // return TRUE unless you set the focus to a control

}


void CSerachDlg::OnLbnDblclkList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index=m_SerachLst.GetCurSel();
	if(index<0)
		return;
	//����������� ����Ƶ�������Ϣ
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

	// TODO: �ڴ˴������Ϣ����������
	//this->ShowWindow(SW_HIDE);
}


void CSerachDlg::OnLbnKillfocusList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	//this->ShowWindow(SW_HIDE);
}
