
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
	libvlc_instance_t*  m_vlcInst;		//ʵ�����
	libvlc_media_player_t* m_vlcMplay;	//����ʵ��
	libvlc_media_t*   m_vlcMedia;		//ý��ʵ��
	libvlc_time_t m_TotalTime;			//��¼�ļ�����
	VideoTime m_videoTime;				//���ļ�����ת��ʱ���֣���
	bool m_isPlayLocalFlag;				//��¼�Ƿ��ڲ��ű����ļ�
	bool m_newFileFlag;					//�ж��Ƿ���һ�����ļ�
	int m_maxPlayerVolume;				//�������������150
public:
	VideoManager();
	~VideoManager();
private:
	char* EncodeToUTF8(const WCHAR* mbcsStr);
	void ReleasePlayer();
	void PlayVideoLocal(char*filePath,HWND hwnd);		//���ű�����Ƶ
	void PlayVideoNet(char*netLoc,HWND hwnd);			//����������Ƶ
public:
	bool InitPlayer();									//��ʼ��
	void StopVideo();									//ֹͣ
	void PauseVideo();									//��ͣ
	void SetCurrentPlayTime(int time);					//���ò���ʱ��
	CString GetCurrentPlayTime();						//�õ���ǰ����ʱ��
	CString GetTotalPlayTime();							//�õ���Ƶ��ʱ��
	long long GetCurrentPlayTimeL();						
	long long GetTotalPlayTimeL();		
	void SetPlayerVolume(int volume);					//��������
	int GetPlayerMaxVolume();							//�õ��������������
	void PlayNetOrLocal(CString VideoPath,HWND hwnd);		//������Ƶ
	int GetPlayerStatus();								//�õ���Ƶ����״̬
	bool ScreenSnapShot(char*filePath);					//����(��Ƶ����)
		
};






#endif