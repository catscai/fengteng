
#ifndef INET_H
#define INET_H
#include <winsock2.h>
#include <process.h>
#pragma comment(lib,"Ws2_32.lib")
class INet
{
public:
	INet(){}
	virtual ~INet(){}
public:
	virtual bool InitServer()=0;
	virtual void UnInitServer()=0;
	virtual bool SendData(char*szbuf,long len)=0;
};

#endif