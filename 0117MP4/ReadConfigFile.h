#pragma once
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class CReadConfigFile
{
private:
	ifstream m_fin;
	string   m_VideoDownLoadPath;
	string   m_VideoHistPath;
	string   m_ScreenShotPath;
public:
	CReadConfigFile(void);
	~CReadConfigFile(void);
public:
	bool ReadConfig();
	string GetVideoDown();
	string GetVideoHist();
	string GetScreenShot();
};

