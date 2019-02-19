#pragma once
#ifndef UDPNET_H
#define UDPNET_H
#include "INet.h"
#include "IMediator.h"
class UDPNet:public INet 
{
public:
	SOCKET m_sockClient;
	HANDLE m_threadRecv;
	//bool   m_threadExitFlag;
	sockaddr_in m_serverAddr;	//服务器地址信息
	IMediator *m_udpMediator;
public:
	UDPNet(IMediator *m_udpMediator);
	~UDPNet();
public:
	virtual bool InitServer();
	virtual void UnInitServer();
	virtual bool SendData(char*szbuf,long len);
public:
	//static unsigned __stdcall ThreadPro( void * lpvoid);
};

#endif