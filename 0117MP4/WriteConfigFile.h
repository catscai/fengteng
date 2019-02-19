#pragma once
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
class CWriteConfigFile
{
private:
	ofstream m_fout;
	string   m_VideoDownLoadPath;
	string   m_VideoHistPath;
	string   m_ScreenShotPath;
public:
	CWriteConfigFile(void);
	~CWriteConfigFile(void);
public:
	bool WriteConfig();
	bool SetVideoDown(string VideoDown);
	bool SetVideoHist(string VideoHist);
	bool SetScreenShot(string ScreenShot);
};

