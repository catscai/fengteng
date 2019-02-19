
// 0117MP4.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "VideoManager.h"
#include "IMediator.h"
#include "ReadConfigFile.h"
#include "WriteConfigFile.h"
// CMy0117MP4App:
// �йش����ʵ�֣������ 0117MP4.cpp
//

class CMy0117MP4App : public CWinApp
{
public:
	CMy0117MP4App();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
private:
	VideoManager* m_videoManager;
	IMediator* m_pUDPMediator;
private:
	CReadConfigFile m_ReadConfig;
	CWriteConfigFile m_WriteConfig;
public:
	TCHAR g_ScreenSnapShotPath[MAX_PATH]; 
	//��Ƶ����·��
	TCHAR g_DownLoadVideoPath[MAX_PATH]; 
	TCHAR g_HistVideoPath[MAX_PATH]; 
public:
	//�����ļ������ӿ�
	bool ReadConfig();
	bool WriteConfig();
	CString GetVideoDown();
	CString GetVideoHist();
	CString GetScreenShot();
	bool SetVideoDown(CString VideoDown);
	bool SetVideoHist(CString VideoHist);
	bool SetScreenShot(CString ScreenShot);
public:
	VideoManager* getVideoManager(){
		if(m_videoManager)
			return m_videoManager;
		else
			return NULL;
	}
	IMediator* getUDPMediator(){
		if(m_pUDPMediator)
			return m_pUDPMediator;
		else
			return NULL;
	}
	virtual int ExitInstance();
};

extern CMy0117MP4App theApp;