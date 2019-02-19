// MyStreaming.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyStreaming.h"
#include "afxdialogex.h"


// CMyStreaming �Ի���

IMPLEMENT_DYNAMIC(CMyStreaming, CDialogEx)

CMyStreaming::CMyStreaming(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyStreaming::IDD, pParent)
	, m_PlayStreamName(_T(""))
{

}

CMyStreaming::~CMyStreaming()
{
}

void CMyStreaming::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_PLAYING, m_NameStreamList);
	DDX_Control(pDX, IDC_SERACH_STREAM_EDIT, m_SreachName);
	DDX_Text(pDX, IDC_STATIC_PLAYVIDEONAME, m_PlayStreamName);
}


BEGIN_MESSAGE_MAP(CMyStreaming, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_LBN_DBLCLK(IDC_LIST_PLAYING, &CMyStreaming::OnLbnDblclkListPlaying)
END_MESSAGE_MAP()


// CMyStreaming ��Ϣ�������


BOOL CMyStreaming::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//���û�ˢ
	m_brush.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control
}


HBRUSH CMyStreaming::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return m_brush;
	}
	if(pWnd==GetDlgItem(IDC_LIST_PLAYING))
	{
		pDC->SetBkColor(RGB(158,158,158));
		pDC->SetTextColor(RGB(255,255,255));
		return m_brush;
	}
	if(pWnd==GetDlgItem(IDC_STATIC_PLAYVIDEONAME))
	{
		pDC->SetBkColor(RGB(158,158,158));
		pDC->SetTextColor(RGB(255,255,255));
		return m_brush;
	}
	return hbr;
}


void CMyStreaming::OnLbnDblclkListPlaying()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int nPos=m_NameStreamList.GetCurSel();
	if(nPos<0)
		return;



	//ȥ���б��ϵĹ��
	m_NameStreamList.SetCurSel(-1);
}
