// MyLoginDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyLoginDlg.h"
#include "afxdialogex.h"
#include "MyTools.h"
#include "Packdef.h"
#include "0117MP4Dlg.h"
// CMyLoginDlg �Ի���

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


// CMyLoginDlg ��Ϣ�������
BOOL CMyLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//���廭ˢ
	m_brush.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control

}

HBRUSH CMyLoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	if(m_userPasswd==_T(""))
		return;
	//У���˺ź�����
	if(!CMyTools::CheckUserId(m_userId))
		return;
	if(!CMyTools::CheckUserPasswd(m_userPasswd))
		return;
	//����������͵�¼��Ϣ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
}

//register
void CMyLoginDlg::OnBnClickedButton8()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_registerDlg.ShowWindow(SW_SHOW);
}


BOOL CMyLoginDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_RETURN){
		//�س��� ��¼
		OnBnClickedButton3();
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyLoginDlg::OnDestroy()
{
	CDialogEx::OnDestroy();
	m_brush.DeleteObject();
	// TODO: �ڴ˴������Ϣ����������
}
