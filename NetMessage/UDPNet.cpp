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
	//1.���ؿ�
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
	//2.����Socket
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
	//����socketΪ������
	//u_long mark=1;
	//ioctlsocket(m_sockClient,FIONBIO ,&mark);
	//3.��
	sockaddr_in clientAddr;	//�ͻ���
	//�ͻ��˵���Ϣ
	clientAddr.sin_family=AF_INET;
	clientAddr.sin_port=htons(UDP_CLIENT_PORT);
	clientAddr.sin_addr.S_un.S_addr=INADDR_ANY;	//�Զ�ѡ��ip
	if(SOCKET_ERROR==bind(m_sockClient,(sockaddr*)&clientAddr,sizeof(clientAddr))){
		UnInitServer();
		return false;
	}
	//�������˵���Ϣ
	m_serverAddr.sin_family=AF_INET;
	m_serverAddr.sin_port=htons(UDP_SERVER_PORT);
	m_serverAddr.sin_addr.S_un.S_addr=inet_addr(g_ServerIP);	//�Զ�ѡ��ip
	//����������Ϣ�߳�
	//m_threadRecv=(HANDLE)_beginthreadex(NULL,0,&ThreadPro,this,0,NULL);
	//ʹ���첽ѡ�񷽷�������Ϣ ����Ϣ�󶨵�CMyWndMeg����
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
	////�˳�������Ϣ���߳�
	//m_threadExitFlag=false;
	//ɾ��������Ϣ�Ĵ���
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