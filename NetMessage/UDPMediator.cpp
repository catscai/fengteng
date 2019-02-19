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
		//�����������������Ϣ
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
	if(m_isLoginFlag)//����Ѿ���¼���� �˳�ʱҪ�����˳���¼��Ϣ
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
//�رտͻ�����Ϣ����
bool UDPMediator::OnCloseClient(char*szbuf)
{
	//CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	//pthis->OnDestroy();
	theApp.m_pMainWnd->PostMessage(WM_CLOSE);
	return true;
}
//���������userid
bool UDPMediator::OnRegisterRqId(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	REGISRTERRQ* info=(REGISRTERRQ*)szbuf;
	//��ע�ᴰ�ڷ�����Ϣ
	pthis->m_registerDlg.PostMessage(REGISTER_RQUSERID,0,info->userid);
	return true;
}

//������Ϣ
bool UDPMediator::OnPublicWord(char*szbuf)
{
	ANNOUNCEMENTINFO* info=(ANNOUNCEMENTINFO*)szbuf;
	theApp.m_pMainWnd->PostMessage(PUBLIC_WORD,(WPARAM)info->content,0);
	return true;
}
//��¼�ɹ���Ϣ
bool UDPMediator::OnLoginSuccess(char*szbuf)
{
	LOGINMESSAGE* info=(LOGINMESSAGE*)szbuf;
	theApp.m_pMainWnd->PostMessage(LOGIN_SUCCESS_MEG,(WPARAM)info->username,0);
	m_isLoginFlag=true;
	m_userid=info->uid;
	//��¼�ɹ���ȡ�ղ��б�
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.GetCollections();
	return true;
}
//��¼ʧ����Ϣ
bool UDPMediator::OnLoginFailture(char*szbuf)
{
	theApp.m_pMainWnd->PostMessage(LOGIN_FAILTURE_MEG);
	return true;
}
//ע��ɹ�
bool UDPMediator::OnRegisterSuccess(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	//��Ϣ����ע�ᴰ��
	pthis->m_registerDlg.PostMessage(REGISTER_SUCCESS_MEG);
	return true;
}
//�յ���Ӱ����
bool UDPMediator::OnRecvMovieLink(char*szbuf)
{
	//���͸��б���
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_listDlg.SendMessage(MOVIEINFO_MEG,(WPARAM)szbuf,0);
	return true;
}
bool UDPMediator::OnSerachMovieRs(char*szbuf)
{
	//���͸��б���
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
//�ղ���Ƶ�ظ�
bool UDPMediator::OnCollectRs(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.SendMessage(GET_COLLECTIONS_MEG,(WPARAM)szbuf);
	return true;
}
//ɾ���ղ��� �ظ�
bool UDPMediator::OnDeleteCollectionRs(char*szbuf)
{
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	pthis->m_collectDlg.SendMessage(DELETE_COLLECTIONS_MEG,(WPARAM)szbuf);
	return true;
}