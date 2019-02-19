#include "stdafx.h"
#include "UDPMediator.h"
#include "0117MP4.h"
#include "0117MP4Dlg.h"
UDPMediator::UDPMediator()
{
	m_udpNet=new UDPNet(this);
	m_isLoginFlag=false;
}
UDPMediator::~UDPMediator()
{
	if(m_udpNet)
		delete m_udpNet;
	m_udpNet=NULL;
}
static const ProtectMegMap g_UdpMessageMap[]=
{
	{CLOSE_CLIENT,&UDPMediator::OnCloseClient},
	{UDP_REGISTER_RQ,&UDPMediator::OnRegisterRqId},
	{ANNOUNCEMENT,&UDPMediator::OnPublicWord},
	{LOGIN_SUCCESS,&UDPMediator::OnLoginSuccess},
	{LOGIN_FAILTURE,&UDPMediator::OnLoginFailture},
	{REGISTER_SUCCESS,&UDPMediator::OnRegisterSuccess},
	{MOVIE_LINK_PACK,&UDPMediator::OnRecvMovieLink},
	{SERACH_MOVIE_RS,&UDPMediator::OnSerachMovieRs},
	{SERACH_MOVIEINFO_RS,&UDPMediator::OnSerachMovieInfoRs},
	{COLLECT_SINGLE_RS,&UDPMediator::OnCollectRs},
	{DELETE_COLLECTION_RS,&UDPMediator::OnDeleteCollectionRs},
	{0,0}
};
bool UDPMediator::OpenServer()
{
	if(m_udpNet->InitServer()){
		//向服务器发送上线消息
		LINEINFO info;
		info.RqType=UDP_ONLINE_RQ;
		this->SendData((char*)&info,sizeof(info));
		return true;
	}
	return false;
}
void UDPMediator::CloseServer()
{
	LINEINFO info;
	info.RqType=UDP_OFFLINE_RQ;
	this->SendData((char*)&info,sizeof(info));
	if(m_isLoginFlag)//如果已经登录过了 退出时要发送退出登录消息
	{
		LOGININFO xinfo;
		xinfo.RqType=UDP_UNLOGIN_RQ;
		xinfo.uid=m_userid;
		this->SendData((char*)&xinfo,sizeof(xinfo));
	}
	m_udpNet->UnInitServer();
}
void UDPMediator::DealData(char*szbuf)
{
	PackType* TypeMsg=(PackType*)szbuf;
	int i=0;
	while(true){
		if(g_UdpMessageMap[i].ptype==0)
			break;
		if((*TypeMsg)==g_UdpMessageMap[i].ptype)
			(this->*g_UdpMessageMap[i].pfMeg)(szbuf);
		i++;
	}
}
bool UDPMediator::SendData(char*szbuf,int len)
{
	if(m_udpNet->SendData(szbuf,len))
		return true;
	else
		return false;
}
//关闭客户端消息处理
bool UDPMediator::OnCloseClient(char*szbuf)
{
	//CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	//pthis->OnDestroy();
	theApp.m_pMainWnd->PostMessage(WM_CLOSE);
	return true;
}
//返回申请的userid
bool UDPMediator::OnRegisterRqId(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	REGISRTERRQ* info=(REGISRTERRQ*)szbuf;
	//想注册窗口发送消息
	pthis->m_registerDlg.PostMessage(REGISTER_RQUSERID,0,info->userid);
	return true;
}

//公告消息
bool UDPMediator::OnPublicWord(char*szbuf)
{
	ANNOUNCEMENTINFO* info=(ANNOUNCEMENTINFO*)szbuf;
	theApp.m_pMainWnd->PostMessage(PUBLIC_WORD,(WPARAM)info->content,0);
	return true;
}
//登录成功消息
bool UDPMediator::OnLoginSuccess(char*szbuf)
{
	LOGINMESSAGE* info=(LOGINMESSAGE*)szbuf;
	theApp.m_pMainWnd->PostMessage(LOGIN_SUCCESS_MEG,(WPARAM)info->username,0);
	m_isLoginFlag=true;
	m_userid=info->uid;
	//登录成功获取收藏列表
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.GetCollections();
	return true;
}
//登录失败消息
bool UDPMediator::OnLoginFailture(char*szbuf)
{
	theApp.m_pMainWnd->PostMessage(LOGIN_FAILTURE_MEG);
	return true;
}
//注册成功
bool UDPMediator::OnRegisterSuccess(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	//消息发给注册窗口
	pthis->m_registerDlg.PostMessage(REGISTER_SUCCESS_MEG);
	return true;
}
//收到电影链接
bool UDPMediator::OnRecvMovieLink(char*szbuf)
{
	//发送给列表窗口
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_listDlg.SendMessage(MOVIEINFO_MEG,(WPARAM)szbuf,0);
	return true;
}
bool UDPMediator::OnSerachMovieRs(char*szbuf)
{
	//发送给列表窗口
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_listDlg.SendMessage(SERACH_MOVIENAME_MEG,(WPARAM)szbuf,0);
	return true;
}
bool UDPMediator::OnSerachMovieInfoRs(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_listDlg.SendMessage(SERACH_MOVIEINFO_MEG,(WPARAM)szbuf,0);
	return true;
}
//收藏视频回复
bool UDPMediator::OnCollectRs(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.SendMessage(GET_COLLECTIONS_MEG,(WPARAM)szbuf);
	return true;
}
//删除收藏项 回复
bool UDPMediator::OnDeleteCollectionRs(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.SendMessage(DELETE_COLLECTIONS_MEG,(WPARAM)szbuf);
	return true;
}