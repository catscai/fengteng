
#pragma once
#ifndef PACKDEF_H
#define PACKDEF_H

#define PLAY_PROCESS_TIMER 1	//���Ž��ȶ�ʱ��

#define SLIDER_PLAY_RANGE 1000	//���Ż���ķ�Χ
#define DEF_PLAY_VOLUME 100		//Ĭ��������С
#define MAX_PLAY_VOLUME 150		//������� Ҳ���������鷶Χ

//Ӧ��Ŀ¼
static TCHAR*g_AppPath=_T("C:\\fengteng");
//ͼƬ��ȡĬ��·��

static TCHAR*g_ScreenSnapShotSty	=_T(".jpg");
static char*g_ServerIP = "127.0.0.1";
//ֱ���ĵ���Ƶ��
//#define MAX_LENGTH_CHANNEL 100
//#define NAME_LENGTH_CHANNEL 20
//struct CHANNEL
//{
//	char name[NAME_LENGTH_CHANNEL];
//	char channel[MAX_LENGTH_CHANNEL];
//};
//static const CHANNEL channels[]=
//{
//	{"CCTV1����","http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"},
//	{"CCTV3����","http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8"},
//	{"CCTV5����","http://ivi.bupt.edu.cn/hls/cctv5hd.m3u8"},
//	{"CCTV5+����","http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8"},
//	{"CCTV6����","http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8"},
//	{"",""}
//};
//��Ϣ
#define DEFAULT_MEG 1300
#define SOCKREAD_MEG DEFAULT_MEG+1	//UDP�첽ѡ�񴰿ڽ�����Ϣ 
#define REGISTER_RQUSERID DEFAULT_MEG+2 //��ע�ᴰ�ڷ��͵ķ����˺���Ϣ ���͸�ע�ᴰ��
#define PUBLIC_WORD		DEFAULT_MEG+3	//���ع�����Ϣ ���͸�������
#define LOGIN_SUCCESS_MEG DEFAULT_MEG+4	//��¼�ɹ���Ϣ ����������
#define LOGIN_FAILTURE_MEG DEFAULT_MEG+5//��¼ʧ�� ����������
#define REGISTER_SUCCESS_MEG DEFAULT_MEG+6	//ע��ɹ� ����ע�ᴰ��
#define MOVIEINFO_MEG	DEFAULT_MEG+7		//��Ӱ��Ϣ���͸��б���
#define SERACH_MOVIENAME_MEG DEFAULT_MEG+8	//������Ƶ�Ļظ���Ϣ
#define SERACH_MOVIEINFO_MEG DEFAULT_MEG+9	//������Ƶ�������Ϣ ��Ϣ
#define GET_COLLECTIONS_MEG	DEFAULT_MEG+10	//�ղػظ���Ϣ
#define DELETE_COLLECTIONS_MEG DEFAULT_MEG+11	//ɾ���ղ���
//����
#define UDP_PACKAGE_SIZE 10240	//udp���ݰ���С
#define UDP_SERVER_PORT 2048 //�������˶˿�
#define UDP_CLIENT_PORT 2049 //�ͻ���udp�˿�

//���������������
#define UDP_ONLINE_RQ 1		//����
#define UDP_OFFLINE_RQ 2	//����
typedef int PackType;
struct LINEINFO
{
	PackType  RqType;

};
//�����������
#define UDP_LOGIN_RQ 3		//��¼
#define UDP_UNLOGIN_RQ 4	//�˳���¼
#define MAX_LOGIN_PASSWD 16	//��¼����,������󳤶�
struct LOGININFO
{
	PackType  RqType;
	long      uid;
	char	  upasswd[MAX_LOGIN_PASSWD];
};
//ע��
//������������˺�
#define UDP_REGISTER_RQ 5	//������������˺�
#define UDP_REGISTER_USER 6	//�����˺ųɹ���ע���˺�
struct REGISRTERRQ			//������������˺�
{
	PackType  RqType;
	long	  userid;		//�����˺���ظ�ʹ��һ��Э���������Ӵ���
};
struct REGISTERINFO			//�ύע����Ϣ
{
	PackType  RqType;
	long	  userid;
	char	  username[MAX_LOGIN_PASSWD];
	char	  passwd[MAX_LOGIN_PASSWD];
	char	  birth[MAX_LOGIN_PASSWD];
};
//�ͻ��˽�����Ϣ
#define CLOSE_CLIENT 7		//��������ǿ�ƹرտͻ���
struct CLOSEINFO
{
	PackType  RqType;
};
//����announcement
#define ANNOUNCEMENT 8	//���͹���
#define ANNOUNCEMENT_SIZE 2048	//�������ݴ�С
struct ANNOUNCEMENTINFO
{
	PackType  RqType;
	char	  content[ANNOUNCEMENT_SIZE];
};
//��ͻ��˷��ص�¼��Ϣ
#define LOGIN_SUCCESS 9	//��¼�ɹ�
#define LOGIN_FAILTURE 10 //��¼ʧ��
struct LOGINMESSAGE
{
	PackType  RqType;
	long	  uid;
	char	  username[MAX_LOGIN_PASSWD];
};
//ע��ɹ���Ϣ
#define REGISTER_SUCCESS 11
struct REGISTERMESSAGE	//ע��ɹ�
{
	PackType  RqType;
};

//��Ӱ����Э���
#define MOVIE_LINK_PACK 12	//��Ӱ��Ϣ
#define MAX_MOVIE_NAME  200	//����Ӱ����
#define MAX_MOVIE_LINK	300	//������ӳ���
#define MAX_LINK_COUNT	25	//�������Ӱ�����
#define SEND_MOVIE_COUNT 30	//�����Ƽ���Ӱ������
typedef short VideoType;	//��Ƶ����
#define VIDEOTYPE_MOVIE	1	//��Ӱ
#define VIDEOTYPE_TVPLAY 2	//���Ӿ�
struct MOVIELINK	//�ֶε�����
{
	char	link[MAX_MOVIE_LINK];
};
typedef struct MOVIEINFO
{
	PackType  RqType;
	VideoType VqType;
	int       linksNum;
	char      movieName[MAX_MOVIE_NAME];
	MOVIELINK links[MAX_LINK_COUNT];
}MOVIEINFO,SERACHMOVIERS;
//��������
#define SERACH_MOVIE_RQ 13
#define SERACH_MOVIE_RS 14
#define SERACH_RETURN_NUM 30	//�������ص�����
struct SERACHRQ
{
	PackType  RqType;
	char	  movieName[MAX_MOVIE_NAME];
};
struct SERACHMOVIENAME
{
	char	movieName[MAX_MOVIE_NAME];
};
struct SERACHRS
{
	PackType  RqType;
	int		  realNum;
	SERACHMOVIENAME movieNames[SERACH_RETURN_NUM];
};
//������Ƶ��Ϣ
#define SERACH_MOVIEINFO_RQ 15
#define SERACH_MOVIEINFO_RS 16
struct SERACHMOVIERQ
{
	PackType  RqType;
	char	movieName[MAX_MOVIE_NAME];
};
//�ղ���Ƶ
#define COLLECT_SINGLE_RQ 17
#define COLLECT_SINGLE_RS 18
#define COLLECT_TOTAL_RQ  19
#define COLLECT_TOTAL_RS  20
struct COLLECTSINGLERQ
{
	PackType  RqType;
	long		userid;
	char	movieName[MAX_MOVIE_NAME];
	char	link[MAX_MOVIE_LINK];
};
struct COLLECTSINGLERS
{
	PackType  RqType;
	char	movieName[MAX_MOVIE_NAME];
	char	link[MAX_MOVIE_LINK];
};
struct COLLECTTOTAL
{
	PackType  RqType;
	long		userid;
	char	movieName[MAX_MOVIE_NAME];
	char	link[MAX_MOVIE_LINK];
};
#define GET_COLLECTIONS_RQ 21
#define GET_COLLECTIONS_RS 22
struct GETCOLLECTIONS
{
	PackType  RqType;
	long userid;
};
//ɾ���ղ�
#define DELETE_COLLECTION_RQ 23
#define DELETE_COLLECTION_RS 24
struct DELETECOLLECTIONRQ
{
	PackType  RqType;
	long		userid;
	char	movieName[MAX_MOVIE_NAME];
};
struct DELETECOLLECTIONRS
{
	PackType  RqType;
	char	movieName[MAX_MOVIE_NAME];
};
//���ظ���
#define RQ_LOADMORE_MOVIES 25
struct LOADMORE
{
	PackType  RqType;
	unsigned  moviepos;
};
#endif