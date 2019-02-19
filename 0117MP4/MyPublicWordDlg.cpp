// MyPublicWordDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyPublicWordDlg.h"
#include "afxdialogex.h"


// CMyPublicWordDlg �Ի���

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


// CMyPublicWordDlg ��Ϣ�������


BOOL CMyPublicWordDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//���廭ˢ
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
	// TODO: �ڴ����ר�ô����/����û���
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
	// TODO: �ڴ˴������Ϣ����������
}
