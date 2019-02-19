// MyWndMeg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4Dlg.h"
#include "MyWndMeg.h"
#include "Packdef.h"

// CMyWndMeg

IMPLEMENT_DYNCREATE(CMyWndMeg, CFrameWnd)

CMyWndMeg::CMyWndMeg()
{
	//m_ThreadHandle = NULL;
	//m_ExitThreadFlag = true;
	////创建线程
	//m_ThreadHandle = (HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,NULL);
}

CMyWndMeg::~CMyWndMeg()
{
}

CMyWndMeg* CMyWndMeg::MyWnd = new CMyWndMeg;
BEGIN_MESSAGE_MAP(CMyWndMeg, CFrameWnd)
	ON_MESSAGE(SOCKREAD_MEG,&CMyWndMeg::SocketRead)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


//为处理消息单独开一个线程
//unsigned __stdcall CMyWndMeg::ThreadPro(void* pvoid)
//{
//	CMyWndMeg*pthis = (CMyWndMeg*)pvoid;
//	while(pthis->m_ExitThreadFlag)
//	{
//		pthis->m_lock.TestLock();
//		if(pthis->m_DealTaskQueue.empty())
//		{
//			pthis->m_lock.TestUnlock();
//			continue;
//		}
//		MydealMessage meg = pthis->m_DealTaskQueue.front();
//		pthis->m_UdpMediator->DealData(meg.Message);
//		pthis->m_DealTaskQueue.pop();
//		pthis->m_lock.TestUnlock();
//	}
//	return 0;
//}
// CMyWndMeg 消息处理程序
LRESULT CMyWndMeg::SocketRead(WPARAM w, LPARAM l)
{
	SOCKET m_sockClient = (SOCKET)w;
	int nRes;
	MydealMessage meg;
	sockaddr_in info;
	int nSize=sizeof(info);
	nRes=recvfrom(m_sockClient,meg.Message,UDP_PACKAGE_SIZE,0,(sockaddr*)&info,&nSize);
	if(nRes>0){
		m_UdpMediator->DealData(meg.Message);
	}
	return 0;
}

void CMyWndMeg::OnDestroy()
{
	CFrameWnd::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	//m_ExitThreadFlag = false;
	//if(WaitForSingleObject(m_ThreadHandle,100) == WAIT_TIMEOUT)
	//{
	//	TerminateThread(m_ThreadHandle,-1);
	//	CloseHandle(m_ThreadHandle);
	//	m_ThreadHandle = NULL;
	//}
}
