#pragma once


// CMyWndMeg 框架
#include "IMediator.h"
//#include "TestThreadPool.h"
//#include <queue>
//using std::queue;
struct MydealMessage
{
	char Message[UDP_PACKAGE_SIZE];
};
class CMyWndMeg : public CFrameWnd
{
	DECLARE_DYNCREATE(CMyWndMeg)
protected:
	CMyWndMeg();           // 动态创建所使用的受保护的构造函数
	virtual ~CMyWndMeg();

protected:
	DECLARE_MESSAGE_MAP()
private:
	static CMyWndMeg* MyWnd;
	IMediator*m_UdpMediator;
	//HANDLE    m_ThreadHandle;
	//bool	  m_ExitThreadFlag;
	//queue<MydealMessage> m_DealTaskQueue;
	//CTestLock			 m_lock;
private:
	static unsigned __stdcall ThreadPro(void* pvoid);
public:
	afx_msg LRESULT SocketRead(WPARAM w, LPARAM l);
public:
	static CMyWndMeg* GetMyWndMeg()
	{
		if(MyWnd)
			return MyWnd;
		else
			return NULL;
	}
	void SetUDPMediator(IMediator*Mediator)
	{
		m_UdpMediator=Mediator;
	}
	static void DeleteMyWndMeg()
	{
		if(MyWnd){
			MyWnd->DestroyWindow();
			delete MyWnd;
		}
		MyWnd=NULL;
	}
	afx_msg void OnDestroy();
};


