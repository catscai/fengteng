// MyDownFinishedDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "0117MP4Dlg.h"
#include "MyDownFinishedDlg.h"
#include "afxdialogex.h"


// CMyDownFinishedDlg �Ի���

IMPLEMENT_DYNAMIC(CMyDownFinishedDlg, CDialogEx)

CMyDownFinishedDlg::CMyDownFinishedDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDownFinishedDlg::IDD, pParent)
{

}

CMyDownFinishedDlg::~CMyDownFinishedDlg()
{
}

void CMyDownFinishedDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_FinishedDownloadLst);
}


BEGIN_MESSAGE_MAP(CMyDownFinishedDlg, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST1, &CMyDownFinishedDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CMyDownFinishedDlg ��Ϣ�������


void CMyDownFinishedDlg::OnLbnDblclkList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int index=m_FinishedDownloadLst.GetCurSel();
	if(index==-1)
		return;
	CString vName;
	m_FinishedDownloadLst.GetText(index,vName);
	if(vName==_T(""))
		return;
	if(m_finishedToPathMap.find(vName)==m_finishedToPathMap.end())
		return;
	CString vPath=m_finishedToPathMap[vName];
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	CString realName=CMyTools::GetClearFormatName(vName);
	if(pthis->m_listDlg.m_listName.FindString(-1,realName)==LB_ERR)
	{
		pthis->m_listDlg.m_listName.AddString(vName);
	}
	pthis->m_listDlg.m_nameToPathMap[vName]=vPath;
	pthis->m_listDlg.m_videoPath=vPath;
	pthis->m_listDlg.m_playingName=vName;
	//��ֹͣ��ǰ��Ƶ
	pthis->OnStnClickedStopBu();
	//�ı�Ϊ����״̬
	pthis->m_isPlayBit=true;
	pthis->OnStnClickedPlayBu();
	m_FinishedDownloadLst.SetCurSel(-1);
}


BOOL CMyDownFinishedDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_FinishedDownloadLst.SetHorizontalExtent(500);
	return TRUE;  // return TRUE unless you set the focus to a control

}
