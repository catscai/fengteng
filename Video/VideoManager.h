
#ifndef VIDEO_MANAGER_H
#define VIDEO_MANAGER_H
#include "stdafx.h"
#include "vlc\vlc.h"
#pragma comment(lib,"lib\\libvlc.lib")
#pragma comment(lib,"lib\\libvlccore.lib")
typedef struct VideoTime
{
	int hous;
	int minute;
	int socend;
	CString timeFormat;
}VideoTime;
class VideoManager
{
private:
	libvlc_instance_t*  m_vlcInst;		//实例句柄
	libvlc_media_player_t* m_vlcMplay;	//播放实例
	libvlc_media_t*   m_vlcMedia;		//媒体实例
	libvlc_time_t m_TotalTime;			//记录文件长度
	VideoTime m_videoTime;				//将文件长度转化时，分，秒
	bool m_isPlayLocalFlag;				//记录是否在播放本地文件
	bool m_newFileFlag;					//判断是否是一个新文件
	int m_maxPlayerVolume;				//播放器最大声音150
public:
	VideoManager();
	~VideoManager();
private:
	char* EncodeToUTF8(const WCHAR* mbcsStr);
	void ReleasePlayer();
	void PlayVideoLocal(char*filePath,HWND hwnd);		//播放本地视频
	void PlayVideoNet(char*netLoc,HWND hwnd);			//播放网络视频
public:
	bool InitPlayer();									//初始化
	void StopVideo();									//停止
	void PauseVideo();									//暂停
	void SetCurrentPlayTime(int time);					//设置播放时间
	CString GetCurrentPlayTime();						//得到当前播放时间
	CString GetTotalPlayTime();							//得到视频总时间
	long long GetCurrentPlayTimeL();						
	long long GetTotalPlayTimeL();		
	void SetPlayerVolume(int volume);					//设置声音
	int GetPlayerMaxVolume();							//得到播放器最大声音
	void PlayNetOrLocal(CString VideoPath,HWND hwnd);		//播放视频
	int GetPlayerStatus();								//得到视频播放状态
	bool ScreenSnapShot(char*filePath);					//截屏(视频窗口)
		
};






#endif