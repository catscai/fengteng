#include "stdafx.h"
#include "UDPNet.h"
#include "Packdef.h"
#include "MyWndMeg.h"
UDPNet::UDPNet(IMediator *m_udpMediator)
{
	m_sockClient=NULL;
	m_threadRecv=NULL;
	//m_threadExitFlag=true;
	this->m_udpMediator=m_udpMediator;
}
UDPNet::~UDPNet()
{

}
bool UDPNet::InitServer()
{
	//1.加载库
	WORD wVersionRequested;
    WSADATA wsaData;
    int err;

    wVersionRequested = MAKEWORD(2, 2);

    err = WSAStartup(wVersionRequested, &wsaData);
    if (err != 0) {
        return false;
    }
    if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		UnInitServer();
        return false;
    }
	//2.创建Socket
	m_sockClient = socket(AF_INET,SOCK_DGRAM ,IPPROTO_UDP );

	if(INVALID_SOCKET==m_sockClient)
	{
		UnInitServer();
		return false;
	}
	int RecvBufSize = 20480;
	if(SOCKET_ERROR == setsockopt(m_sockClient,SOL_SOCKET,SO_RCVBUF,(const char*)&RecvBufSize,sizeof(int)))
	{
		UnInitServer();
		return false;
	}
	//设置socket为非阻塞
	//u_long mark=1;
	//ioctlsocket(m_sockClient,FIONBIO ,&mark);
	//3.绑定
	sockaddr_in clientAddr;	//客户端
	//客户端的信息
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_port=htons(UDP_CLIENT_PORT);
	clientAddr.sin_addr.S_un.S_addr=INADDR_ANY;	//自动选择ip
	if(SOCKET_ERROR==bind(m_sockClient,(sockaddr*)&clientAddr,sizeof(clientAddr))){
		UnInitServer();
		return false;
	}
	//服务器端的信息
	m_serverAddr.sin_family=AF_INET;
	m_serverAddr.sin_port=htons(UDP_SERVER_PORT);
	m_serverAddr.sin_addr.S_un.S_addr=inet_addr(g_ServerIP);	//自动选择ip
	//创建接收消息线程
	//m_threadRecv=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,NULL);
	//使用异步选择方法接受消息 将消息绑定到CMyWndMeg窗口
	CMyWndMeg::GetMyWndMeg()->Create(NULL,_T("MyWnd"));
	CMyWndMeg::GetMyWndMeg()->SetUDPMediator(m_udpMediator);
	WSAAsyncSelect(m_sockClient,CMyWndMeg::GetMyWndMeg()->m_hWnd,SOCKREAD_MEG,FD_READ);
	return true;
}
//unsigned __stdcall UDPNet::ThreadPro( void * lpvoid)
//{
//	UDPNet*pthis=(UDPNet*)lpvoid;
//	int nRes;
//	char Message[UDP_PACKAGE_SIZE]={0};
//	while(pthis->m_threadExitFlag)
//	{
//		nRes=recvfrom(pthis->m_sockClient,Message,UDP_PACKAGE_SIZE,0,NULL,NULL);
//		if(nRes>0)
//			pthis->m_udpMediator->DealData(Message);
//	}
//	return 0;
//}
void UDPNet::UnInitServer()
{
	////退出接收消息的线程
	//m_threadExitFlag=false;
	//删除接受消息的窗口
	CMyWndMeg::DeleteMyWndMeg();
	WSACleanup();
	if(m_sockClient)
		closesocket(m_sockClient);
	m_sockClient=NULL;
}
bool UDPNet::SendData(char*szbuf,long len)
{
	if(!sendto(m_sockClient,szbuf,len,0,(sockaddr*)&m_serverAddr,sizeof(m_serverAddr))){
		return false;
	}
	return true;
}