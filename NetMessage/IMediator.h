
#ifndef IMEDIATOR_H
#define IMEDIATOR_H

class IMediator
{
public:
	IMediator(){}
	virtual ~IMediator(){}
public:
	virtual bool OpenServer()=0;
	virtual void CloseServer()=0;
	virtual void DealData(char*szbuf)=0;
	virtual bool SendData(char*szbuf,int len)=0;
};

#endif