#include "stdafx.h"
#include "WriteConfigFile.h"


CWriteConfigFile::CWriteConfigFile(void)
{
	m_VideoDownLoadPath = "";
	m_VideoHistPath = "";
	m_ScreenShotPath = "";
}


CWriteConfigFile::~CWriteConfigFile(void)
{
}

bool CWriteConfigFile::WriteConfig()
{
	string filePath = "./fengtengconfig.ft";
	m_fout.open(filePath,ios::out);
	if(!m_fout)
		return false;
	m_fout<<m_VideoDownLoadPath<<endl;
	m_fout<<m_VideoHistPath<<endl;
	m_fout<<m_ScreenShotPath<<endl;
	m_fout.close();
	return true;
}
bool CWriteConfigFile::SetVideoDown(string VideoDown)
{
	m_VideoDownLoadPath = VideoDown;
	return true;
}
bool CWriteConfigFile::SetVideoHist(string VideoHist)
{
	m_VideoHistPath = VideoHist;
	return true;
}
bool CWriteConfigFile::SetScreenShot(string ScreenShot)
{
	m_ScreenShotPath = ScreenShot;
	return true;
}
