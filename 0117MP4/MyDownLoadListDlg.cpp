



// MyDownLoadListDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyDownLoadListDlg.h"
#include "afxdialogex.h"


// CMyDownLoadListDlg �Ի���

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


// CMyDownLoadListDlg ��Ϣ�������


BOOL CMyDownLoadListDlg::OnInitDialog()
{
	
	CDialogEx::OnInitDialog();
	
	CRect rect;
	m_processList.GetWindowRect(&rect);
	int nWidth=rect.Width()/4;
	m_processList.InsertColumn(0,_T("����"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(1,_T("����"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(2,_T("��С"), LVCFMT_LEFT,nWidth);
	m_processList.InsertColumn(3,_T("״̬"), LVCFMT_LEFT,nWidth);
	//������ˢ
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
	// TODO: �ڴ˴������Ϣ����������
}
