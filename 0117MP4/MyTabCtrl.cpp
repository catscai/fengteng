// MyTabCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyTabCtrl.h"


// CMyTabCtrl

IMPLEMENT_DYNAMIC(CMyTabCtrl, CTabCtrl)

CMyTabCtrl::CMyTabCtrl()
{

}

CMyTabCtrl::~CMyTabCtrl()
{
}


BEGIN_MESSAGE_MAP(CMyTabCtrl, CTabCtrl)
	ON_NOTIFY_REFLECT(NM_CLICK, &CMyTabCtrl::OnNMClick)
END_MESSAGE_MAP()



// CMyTabCtrl 消息处理程序

void CMyTabCtrl::InitTabCtrl(int nCount,CString strName[])
{
	//给标签添加标签项
	for(int i=0;i<nCount;i++)
	{
		this->InsertItem(i,strName[i]);
	}
	CRect rec;
	//得到用户区矩形
	this->GetClientRect(rec);
	rec.top+=33;
	//rec.left+=1;
	CSize size(0,30);
	this->SetItemSize(size);
	//因为是子窗口所以 this
	m_downListDlg.Create(IDD_DOWNLOADDLG,this);
	
	m_finishedListDlg.Create(IDD_DOWNLOAD_FINISHED,this);
	m_localListDlg.Create(IDD_DOWNLOAD_LOCAL,this);
		//创建一个矩形
	m_downListDlg.MoveWindow(rec);
	m_finishedListDlg.MoveWindow(rec);
	m_localListDlg.MoveWindow(rec);
	m_downListDlg.ShowWindow(SW_SHOW);
	m_finishedListDlg.ShowWindow(SW_HIDE);
	m_localListDlg.ShowWindow(SW_HIDE);
}

void CMyTabCtrl::OnNMClick(NMHDR *pNMHDR, LRESULT *pResult)
{
	int index = this->GetCurSel();
	if(index==-1)
		return;
	switch(index)
	{
	case 0:
		{
			m_finishedListDlg.ShowWindow(SW_HIDE);
			m_localListDlg.ShowWindow(SW_HIDE);
			m_downListDlg.ShowWindow(SW_SHOW);
		}
		break;
	case 1:
		{
			m_downListDlg.ShowWindow(SW_HIDE);
			m_localListDlg.ShowWindow(SW_HIDE);
			m_finishedListDlg.ShowWindow(SW_SHOW);
		}
		break;
	case 2:
		{
			m_finishedListDlg.ShowWindow(SW_HIDE);
			m_downListDlg.ShowWindow(SW_HIDE);
			m_localListDlg.ShowVideos();
			m_localListDlg.ShowWindow(SW_SHOW);
		}
		break;
	}
}
