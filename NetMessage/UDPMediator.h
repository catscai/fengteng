
#pragma once
#ifndef UDPMEDIATOR_H
#define UDPMEDIATOR_H
#include "UDPNet.h"
#include "Packdef.h"
#include <map>
#include <vector>
using namespace std;
//定义协议映射表
class UDPMediator;//前向声明
typedef bool (UDPMediator::*PDEAL)(char*);
typedef struct ProtectMegMap
{
	PackType ptype;
	PDEAL pfMeg;
}ProtectMegMap;
class UDPMediator:public IMediator
{
public:
	UDPNet* m_udpNet;
	long m_userid;			//登录成功的账号
	bool m_isLoginFlag;		//用来标记是否已经登录成功

public:
	UDPMediator();
	~UDPMediator();
public:
	virtual bool OpenServer();
	virtual void CloseServer();
	virtual void DealData(char*szbuf);
	virtual bool SendData(char*szbuf,int len);
public:
	bool OnCloseClient(char*szbuf);		//收到消息：关闭客户端
	bool OnRegisterRqId(char*szbuf);	//收到消息：返回userid
	bool OnPublicWord(char*szbuf);		//收到消息：返回公告
	bool OnLoginSuccess(char*szbuf);	//登录成功消息
	bool OnLoginFailture(char*szbuf);	//登录失败消息
	bool OnRegisterSuccess(char*szbuf);	//注册成功消息
	bool OnRecvMovieLink(char*szbuf);	//上线后收到服务器发来的电影链接
	bool OnSerachMovieRs(char*szbuf);	//查询视频 回复
	bool OnSerachMovieInfoRs(char*szbuf);//查询视频 视频信息回复
	bool OnCollectRs(char*szbuf);		//收藏视频回复
	bool OnDeleteCollectionRs(char*szbuf);	//删除收藏项 回复
};

#endif