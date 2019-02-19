// MyCollectDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyCollectDlg.h"
#include "0117MP4Dlg.h"
#include "UDPMediator.h"
#include "Packdef.h"
#include "MyTools.h"
#include "afxdialogex.h"


// CMyCollectDlg 对话框

IMPLEMENT_DYNAMIC(CMyCollectDlg, CDialogEx)

CMyCollectDlg::CMyCollectDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyCollectDlg::IDD, pParent)
{

}

CMyCollectDlg::~CMyCollectDlg()
{
}

void CMyCollectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_collectLst);
}


BEGIN_MESSAGE_MAP(CMyCollectDlg, CDialogEx)
	ON_WM_CTLCOLOR()
	ON_MESSAGE(GET_COLLECTIONS_MEG,&CMyCollectDlg::GetCollections)
	ON_MESSAGE(DELETE_COLLECTIONS_MEG,&CMyCollectDlg::DeleteCollections)
	ON_LBN_DBLCLK(IDC_LIST1, &CMyCollectDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CMyCollectDlg 消息处理程序
LRESULT CMyCollectDlg::DeleteCollections(WPARAM w, LPARAM l)
{
	DELETECOLLECTIONRS*delcolRs=(DELETECOLLECTIONRS*)w;
	WCHAR*wStr=CMyTools::EnCodeUtfToWCHAR(delcolRs->movieName);
	CString vName=wStr;
	delete[] wStr;
	int index=m_collectLst.FindString(-1,vName);
	if(index!=LB_ERR)
	{
		m_collectLst.DeleteString(index);
		m_collectMap.erase(vName);
		UpdateData(FALSE);
	}
	return 0;
}

LRESULT CMyCollectDlg::GetCollections(WPARAM w, LPARAM l)
{
	COLLECTSINGLERS*getcollect=(COLLECTSINGLERS*)w;
	WCHAR*wStr=CMyTools::EnCodeUtfToWCHAR(getcollect->movieName);
	CString vName=wStr;
	delete[] wStr;
	WCHAR*wStr1=CMyTools::EnCodeUtfToWCHAR(getcollect->link);
	CString urlc=wStr1;
	delete[] wStr1;
	m_collectLst.AddString(vName);
	m_collectMap[vName]=urlc;
	UpdateData(FALSE);
	return 0;
}

BOOL CMyCollectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	
	//创建画刷
	m_brush.CreateSolidBrush(RGB(158,158,158));
	return TRUE;  // return TRUE unless you set the focus to a control

}
void CMyCollectDlg::GetCollections()
{
	//请求收藏数据
	UDPMediator*udpMediator=(UDPMediator*)theApp.getUDPMediator();
	if(udpMediator->m_isLoginFlag==false)
		return ;
	GETCOLLECTIONS getcollect;
	getcollect.RqType=GET_COLLECTIONS_RQ;
	getcollect.userid=udpMediator->m_userid;
	udpMediator->SendData((char*)&getcollect,sizeof(getcollect));
}


HBRUSH CMyCollectDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(pWnd==GetDlgItem(IDC_LIST1))
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(158,158,158));
		return m_brush;
	}
	return hbr;
}


BOOL CMyCollectDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->message==WM_KEYDOWN&&pMsg->wParam==VK_DELETE){
		int index=this->m_collectLst.GetCurSel();
		UDPMediator*udpMediator=(UDPMediator*)theApp.getUDPMediator();
		if(index>-1&&udpMediator->m_isLoginFlag==true)
		{
			DELETECOLLECTIONRQ delcolRq;
			delcolRq.RqType=DELETE_COLLECTION_RQ;
			CString vName;
			this->m_collectLst.GetText(index,vName);
			char*temp=CMyTools::EnCodeWCHARToUtf(vName.GetBuffer());
			strcpy_s(delcolRq.movieName,temp);
			delete[] temp;
			delcolRq.userid=udpMediator->m_userid;

			//发送删除请求
			udpMediator->SendData((char*)&delcolRq,sizeof(delcolRq));
			return FALSE;
		}
		
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyCollectDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=this->m_collectLst.GetCurSel();
	if(index==-1)
		return;
	CString vName;
	this->m_collectLst.GetText(index,vName);
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	if(pthis->m_listDlg.m_listName.FindString(-1,vName)==LB_ERR)
	{
		pthis->m_listDlg.m_listName.AddString(vName);
		pthis->m_listDlg.m_nameToPathMap[vName]=this->m_collectMap[vName];
		pthis->m_listDlg.UpdateData(FALSE);
	}
}
