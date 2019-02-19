
// 0117MP4.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "VideoManager.h"
#include "IMediator.h"
#include "ReadConfigFile.h"
#include "WriteConfigFile.h"
// CMy0117MP4App:
// 有关此类的实现，请参阅 0117MP4.cpp
//

class CMy0117MP4App : public CWinApp
{
public:
	CMy0117MP4App();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

	DECLARE_MESSAGE_MAP()
private:
	VideoManager* m_videoManager;
	IMediator* m_pUDPMediator;
private:
	CReadConfigFile m_ReadConfig;
	CWriteConfigFile m_WriteConfig;
public:
	TCHAR g_ScreenSnapShotPath[MAX_PATH]; 
	//视频下载路径
	TCHAR g_DownLoadVideoPath[MAX_PATH]; 
	TCHAR g_HistVideoPath[MAX_PATH]; 
public:
	//配置文件操作接口
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