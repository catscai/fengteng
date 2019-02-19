#include "stdafx.h"
#include "VideoManager.h"

VideoManager::VideoManager()
{
	m_vlcInst=NULL;
	m_vlcMplay=NULL;
	m_vlcMedia=NULL;
	m_TotalTime=0;
	m_videoTime.hous=0;
	m_videoTime.minute=0;
	m_videoTime.socend=0;
	m_videoTime.timeFormat=L"";
	m_isPlayLocalFlag=true;
	m_newFileFlag=true;
	m_maxPlayerVolume=150;
}
VideoManager::~VideoManager()
{
	ReleasePlayer();
}

bool VideoManager::InitPlayer()
{
	const char *vlc_args[] =   
	{  
    "--ignore-config",  
    "--network-caching=500",  
    "--rtsp-tcp", 
	//"--http-user-agent=Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/67.0.3396.99 Safari/537.36"
	//"--rtsp-http",
    "--advanced"
	}; 
	m_vlcInst=libvlc_new(sizeof(vlc_args)/sizeof(vlc_args[0]),vlc_args);
	if(!m_vlcInst)
		return false;
	m_vlcMplay=libvlc_media_player_new(m_vlcInst);
	if(!m_vlcMplay)
		return false;
	return true;
}
void VideoManager::PlayVideoLocal(char*filePath,HWND hwnd)
{
	if(strcmp(filePath,"")==0)
	{
		return;
	}
	if(m_newFileFlag==true){
		if(m_vlcMplay!=NULL)
		{
			libvlc_media_player_release(m_vlcMplay);
		}
		//char filePathByte[MAX_PATH];
		//char*tempPath=EncodeToUTF8(filePath);
		//strcpy_s(filePathByte,MAX_PATH,tempPath);
		/*delete[] tempPath;*/
		m_vlcMedia=libvlc_media_new_path(m_vlcInst,filePath);
		libvlc_media_parse(m_vlcMedia);
		 m_vlcMplay = libvlc_media_player_new_from_media (m_vlcMedia);
		libvlc_media_player_set_hwnd(m_vlcMplay,hwnd);
		libvlc_media_player_set_media(m_vlcMplay,m_vlcMedia);
		m_newFileFlag=false;
	}
	libvlc_media_player_play (m_vlcMplay);
	m_isPlayLocalFlag=true;
}
void VideoManager::PlayVideoNet(char*netLoc,HWND hwnd)
{
	if(strcmp(netLoc,"")==0)
	{
		return;
	}
	if(m_newFileFlag==true){
		if(m_vlcMplay!=NULL)
		{
			libvlc_media_player_release(m_vlcMplay);
		}
		m_vlcMedia=libvlc_media_new_location(m_vlcInst,netLoc);
		libvlc_media_parse(m_vlcMedia);
		 m_vlcMplay = libvlc_media_player_new_from_media (m_vlcMedia);
		libvlc_media_player_set_hwnd(m_vlcMplay,hwnd);
		libvlc_media_player_set_media(m_vlcMplay,m_vlcMedia);
		m_newFileFlag=false;
	}
	libvlc_media_player_play (m_vlcMplay);
	m_isPlayLocalFlag=false;
}
void VideoManager::StopVideo()
{
	if (m_vlcMplay == NULL)
	 {
	  return;
	 }
	  libvlc_media_player_stop(m_vlcMplay);

	 if (m_vlcMedia != NULL)
	 {
	  libvlc_media_release(m_vlcMedia);
	  m_vlcMedia=NULL;
	 }
	 if (m_vlcMplay != NULL)
	 {
	  libvlc_media_player_release(m_vlcMplay);
	  m_vlcMplay=NULL;
	 }
	 m_newFileFlag=true;
}
void VideoManager::PauseVideo()
{
	if(m_vlcMplay != NULL)
		libvlc_media_player_pause(m_vlcMplay);
}
void VideoManager::SetCurrentPlayTime(int time)
{
	if(m_vlcMplay != NULL)
	  {
	   libvlc_time_t m_CurTime;
	   m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
	   double pos = time/1000.0;
	   m_CurTime = static_cast<libvlc_time_t>(m_TotalTime * pos);
	   libvlc_media_player_set_time(m_vlcMplay,m_CurTime);
	  }
}
char* VideoManager::EncodeToUTF8(const WCHAR* mbcsStr)
{
	  char*   utf8Str; 
	  int   charLen;
	  charLen = WideCharToMultiByte(CP_UTF8, 0, mbcsStr, -1, NULL, 0, NULL, NULL);

	  utf8Str = (char*) malloc(charLen);

	  WideCharToMultiByte(CP_UTF8, 0, mbcsStr, -1, utf8Str, charLen, NULL, NULL);

	  return utf8Str;
}
void VideoManager::ReleasePlayer()
{
	 if (m_vlcMplay != NULL)
	 {
		libvlc_media_player_release(m_vlcMplay);
		m_vlcMplay=NULL;
	 }
	 if (m_vlcMedia != NULL)
	 {
		libvlc_media_release(m_vlcMedia);
		m_vlcMedia=NULL;
	 }
	 if(m_vlcInst!=NULL)
	 {
		 libvlc_release(m_vlcInst);
		 m_vlcInst=NULL;
	 }
}
CString VideoManager::GetCurrentPlayTime()
{
	if(m_vlcMplay!=NULL){
		libvlc_time_t m_CurTime = libvlc_media_player_get_time(m_vlcMplay);
		m_videoTime.socend=(m_CurTime/1000)%60;
		m_videoTime.minute=((m_CurTime/1000)/60)%60;
		m_videoTime.hous=(((m_CurTime/1000)/60)/60)%60;
		m_videoTime.timeFormat.Format(_T("%d:%d:%d"),m_videoTime.hous,m_videoTime.minute,m_videoTime.socend);
		return m_videoTime.timeFormat;
	}else
		return _T("");
}
CString VideoManager::GetTotalPlayTime()
{
	if(m_vlcMplay!=NULL){
		m_TotalTime = libvlc_media_player_get_length(m_vlcMplay);
		if(m_TotalTime==0)
			return _T("");
		m_videoTime.socend=(m_TotalTime/1000)%60;
		m_videoTime.minute=((m_TotalTime/1000)/60)%60;
		m_videoTime.hous=(((m_TotalTime/1000)/60)/60)%60;
		m_videoTime.timeFormat.Format(_T("%d:%d:%d"),m_videoTime.hous,m_videoTime.minute,m_videoTime.socend);
		return m_videoTime.timeFormat;
	}else
		return _T("");
}
long long VideoManager::GetCurrentPlayTimeL()
{
	if(m_vlcMplay!=NULL){
		return libvlc_media_player_get_time(m_vlcMplay);
	}else
		return 0;
}
long long VideoManager::GetTotalPlayTimeL()
{
	if(m_vlcMplay!=NULL){
		return libvlc_media_player_get_length(m_vlcMplay);
	}else
		return 0;
}
void VideoManager::SetPlayerVolume(int volume)
{
	if(m_vlcMplay!=NULL){
		if(volume>m_maxPlayerVolume)
			libvlc_audio_set_volume(m_vlcMplay,m_maxPlayerVolume);
		else
			libvlc_audio_set_volume(m_vlcMplay,volume);
	}
}
int VideoManager::GetPlayerMaxVolume()
{
	return m_maxPlayerVolume;
}
void VideoManager::PlayNetOrLocal(CString VideoPath,HWND hwnd)
{
	if(VideoPath==_T("")||hwnd==NULL)
		return;
	char path[MAX_PATH];
	char *pt=EncodeToUTF8(VideoPath.GetBuffer(0));
	strcpy_s(path,MAX_PATH,pt);
	delete[] pt;
	if(strncmp(path,"https",5)==0||strncmp(path,"rtmp",4)==0||strncmp(path,"http",4)==0||strncmp(path,"rstp",4)==0||strncmp(path,"tcp",3)==0||strncmp(path,"udp",3)==0)
	{
		this->PlayVideoNet(path,hwnd);
	}else{
		this->PlayVideoLocal(path,hwnd);
	}
}
int VideoManager::GetPlayerStatus(){
	if(m_vlcMplay!=NULL){
		return libvlc_media_player_get_state(m_vlcMplay);
	}
	return -1;
}
bool VideoManager::ScreenSnapShot(char*filePath)
{
	if(m_vlcMplay!=NULL){
		if(0==libvlc_video_take_snapshot(m_vlcMplay,0,filePath,0,0)){
			return true;
		}
	}
	return false;
}