
#pragma once
#ifndef PACKDEF_H
#define PACKDEF_H

#define PLAY_PROCESS_TIMER 1	//播放进度定时器

#define SLIDER_PLAY_RANGE 1000	//播放滑块的范围
#define DEF_PLAY_VOLUME 100		//默认声音大小
#define MAX_PLAY_VOLUME 150		//最大声音 也是音量滑块范围

//应用目录
static TCHAR*g_AppPath=_T("C:\\fengteng");
//图片截取默认路径

static TCHAR*g_ScreenSnapShotSty	=_T(".jpg");
static char*g_ServerIP = "127.0.0.1";
//直播的电视频道
//#define MAX_LENGTH_CHANNEL 100
//#define NAME_LENGTH_CHANNEL 20
//struct CHANNEL
//{
//	char name[NAME_LENGTH_CHANNEL];
//	char channel[MAX_LENGTH_CHANNEL];
//};
//static const CHANNEL channels[]=
//{
//	{"CCTV1高清","http://ivi.bupt.edu.cn/hls/cctv1hd.m3u8"},
//	{"CCTV3高清","http://ivi.bupt.edu.cn/hls/cctv3hd.m3u8"},
//	{"CCTV5高清","http://ivi.bupt.edu.cn/hls/cctv5hd.m3u8"},
//	{"CCTV5+高清","http://ivi.bupt.edu.cn/hls/cctv5phd.m3u8"},
//	{"CCTV6高清","http://ivi.bupt.edu.cn/hls/cctv6hd.m3u8"},
//	{"",""}
//};
//消息
#define DEFAULT_MEG 1300
#define SOCKREAD_MEG DEFAULT_MEG+1	//UDP异步选择窗口接受消息 
#define REGISTER_RQUSERID DEFAULT_MEG+2 //向注册窗口发送的返回账号消息 发送给注册窗口
#define PUBLIC_WORD		DEFAULT_MEG+3	//返回公告消息 发送给主窗口
#define LOGIN_SUCCESS_MEG DEFAULT_MEG+4	//登录成功消息 发给主窗口
#define LOGIN_FAILTURE_MEG DEFAULT_MEG+5//登录失败 发给主窗口
#define REGISTER_SUCCESS_MEG DEFAULT_MEG+6	//注册成功 发给注册窗口
#define MOVIEINFO_MEG	DEFAULT_MEG+7		//电影信息发送给列表窗口
#define SERACH_MOVIENAME_MEG DEFAULT_MEG+8	//搜索视频的回复消息
#define SERACH_MOVIEINFO_MEG DEFAULT_MEG+9	//搜索视频的相关信息 消息
#define GET_COLLECTIONS_MEG	DEFAULT_MEG+10	//收藏回复消息
#define DELETE_COLLECTIONS_MEG DEFAULT_MEG+11	//删除收藏项
//网络
#define UDP_PACKAGE_SIZE 10240	//udp数据包大小
#define UDP_SERVER_PORT 2048 //服务器端端口
#define UDP_CLIENT_PORT 2049 //客户端udp端口

//向服务器发送请求
#define UDP_ONLINE_RQ 1		//上线
#define UDP_OFFLINE_RQ 2	//下线
typedef int PackType;
struct LINEINFO
{
	PackType  RqType;

};
//向服务器请求
#define UDP_LOGIN_RQ 3		//登录
#define UDP_UNLOGIN_RQ 4	//退出登录
#define MAX_LOGIN_PASSWD 16	//登录密码,名字最大长度
struct LOGININFO
{
	PackType  RqType;
	long      uid;
	char	  upasswd[MAX_LOGIN_PASSWD];
};
//注册
//向服务器申请账号
#define UDP_REGISTER_RQ 5	//向服务器申请账号
#define UDP_REGISTER_USER 6	//申请账号成功，注册账号
struct REGISRTERRQ			//向服务器申请账号
{
	PackType  RqType;
	long	  userid;		//申请账号与回复使用一个协议包所以添加此项
};
struct REGISTERINFO			//提交注册信息
{
	PackType  RqType;
	long	  userid;
	char	  username[MAX_LOGIN_PASSWD];
	char	  passwd[MAX_LOGIN_PASSWD];
	char	  birth[MAX_LOGIN_PASSWD];
};
//客户端接受消息
#define CLOSE_CLIENT 7		//服务器端强制关闭客户端
struct CLOSEINFO
{
	PackType  RqType;
};
//公告announcement
#define ANNOUNCEMENT 8	//发送公告
#define ANNOUNCEMENT_SIZE 2048	//公告内容大小
struct ANNOUNCEMENTINFO
{
	PackType  RqType;
	char	  content[ANNOUNCEMENT_SIZE];
};
//向客户端返回登录信息
#define LOGIN_SUCCESS 9	//登录成功
#define LOGIN_FAILTURE 10 //登录失败
struct LOGINMESSAGE
{
	PackType  RqType;
	long	  uid;
	char	  username[MAX_LOGIN_PASSWD];
};
//注册成功消息
#define REGISTER_SUCCESS 11
struct REGISTERMESSAGE	//注册成功
{
	PackType  RqType;
};

//电影链接协议包
#define MOVIE_LINK_PACK 12	//电影信息
#define MAX_MOVIE_NAME  200	//最大电影名称
#define MAX_MOVIE_LINK	300	//最大链接长度
#define MAX_LINK_COUNT	25	//最大的链接包个数
#define SEND_MOVIE_COUNT 30	//发送推荐电影的数量
typedef short VideoType;	//视频类型
#define VIDEOTYPE_MOVIE	1	//电影
#define VIDEOTYPE_TVPLAY 2	//电视剧
struct MOVIELINK	//分段的链接
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
//搜索请求
#define SERACH_MOVIE_RQ 13
#define SERACH_MOVIE_RS 14
#define SERACH_RETURN_NUM 30	//搜索返回的数量
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
//搜索视频信息
#define SERACH_MOVIEINFO_RQ 15
#define SERACH_MOVIEINFO_RS 16
struct SERACHMOVIERQ
{
	PackType  RqType;
	char	movieName[MAX_MOVIE_NAME];
};
//收藏视频
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
//删除收藏
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
//加载更多
#define RQ_LOADMORE_MOVIES 25
struct LOADMORE
{
	PackType  RqType;
	unsigned  moviepos;
};
#endif