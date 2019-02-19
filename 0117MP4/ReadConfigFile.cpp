#include "stdafx.h"
#include "ReadConfigFile.h"


CReadConfigFile::CReadConfigFile(void)
{
	m_VideoDownLoadPath = "";
	m_VideoHistPath = "";
	m_ScreenShotPath = "";
}


CReadConfigFile::~CReadConfigFile(void)
{
}

bool CReadConfigFile::ReadConfig()
{
	string filePath = "./fengtengconfig.ft";
	m_fin.open(filePath,ios::in);
	if(!m_fin)
		return false;
	m_fin>>m_VideoDownLoadPath;
	m_fin>>m_VideoHistPath;
	m_fin>>m_ScreenShotPath;
	m_fin.close();
	return true;
}
string CReadConfigFile::GetVideoDown()
{
	return m_VideoDownLoadPath;
}
string CReadConfigFile::GetVideoHist()
{
	return m_VideoHistPath;
}
string CReadConfigFile::GetScreenShot()
{
	return m_ScreenShotPath;
}
