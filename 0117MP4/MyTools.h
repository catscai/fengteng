#pragma once
class CMyTools
{
public:
	CMyTools(void);
	~CMyTools(void);
public:
	static 	bool CheckUserId(DWORD id);
	static bool CheckUserPasswd(CString userPasswd);
	static bool CheckUserName(CString userName);
	static WCHAR* EnCodeUtfToWCHAR(char*utf);
	static char* EnCodeWCHARToUtf(WCHAR*uncode);
	static CString GetPlayingName(CString videoPath);
	static CString GetUrlName(CString videoPath);
	static CString GetNamesAlbum(CString vName);
	static CString GetClearFormatName(CString vName);
	//static void DownLoadVideo(const wchar_t *Url, const wchar_t *FileName, DownLoadCallback Func);
};

