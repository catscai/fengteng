#include "stdafx.h"
#include "MyTools.h"
#include "Packdef.h"

CMyTools::CMyTools(void)
{
}


CMyTools::~CMyTools(void)
{
}
//¼ìÑéµÇÂ¼£¬×¢²áÕËºÅ
bool CMyTools::CheckUserId(DWORD userid)
{
	//if(userid<10000000)
	//	return false;
	return true;
}
//¼ìÑéµÇÂ¼£¬×¢²áÃÜÂë
bool CMyTools::CheckUserPasswd(CString userPasswd)
{
	if(userPasswd.GetLength()<1||userPasswd.GetLength()>MAX_LOGIN_PASSWD)
		return false;
	return true;
}
//¼ìÑé×¢²áÊ±ÓÃ»§Ãû
bool CMyTools::CheckUserName(CString userName)
{
	if(userName.GetLength()<1||userName.GetLength()>MAX_LOGIN_PASSWD)
		return false;
	return true;
}
WCHAR* CMyTools::EnCodeUtfToWCHAR(char*utf)
{
	int nLen = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, utf, -1, NULL, 0 );
	if (nLen == 0)
	{
	   return NULL;
	}
	wchar_t* pResult = new wchar_t[nLen];
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, utf, -1, pResult, nLen );
	return pResult;
}
char* CMyTools::EnCodeWCHARToUtf(WCHAR*uncode)
{
	int nLen = WideCharToMultiByte( CP_ACP, 0, uncode, -1, NULL, 0, NULL, NULL );
	if (nLen == 0)
	{
	   return NULL;
	}
	char* pResult = new char[nLen];
	WideCharToMultiByte( CP_ACP, 0, uncode, -1, pResult, nLen, NULL, NULL );
	return pResult;
}

CString CMyTools::GetPlayingName(CString videoPath)
{
	if(videoPath==_T(""))
		return _T("");
	TCHAR* temp=(videoPath.GetBuffer(0)+videoPath.GetLength());
	while(*temp!='\\'){
		if(temp==videoPath.GetBuffer(0)){
			temp--;
			break;
		}
		temp--;
	}
	temp++;
	CString Name(temp);
	return Name;
}

CString CMyTools::GetUrlName(CString videoPath)
{
	if(videoPath==_T(""))
		return _T("");
	if(videoPath.ReverseFind('.') < videoPath.ReverseFind('/'))
		return CString(_T(".flv"));
	TCHAR* temp = (videoPath.GetBuffer(0)+videoPath.GetLength());
	while(*temp!='.'){
		if(temp==videoPath.GetBuffer(0)){
			temp--;
			break;
		}
		temp--;
	}
	CString Name(temp);
	return Name;
}
CString CMyTools::GetNamesAlbum(CString vName)
{
	if(vName==_T(""))
		return _T("");
	TCHAR* temp=(vName.GetBuffer(0)+vName.GetLength());
	while(*temp!='-'){
		if(temp==vName.GetBuffer(0)){
			temp--;
			break;
		}
		temp--;
	}
	temp++;
	CString Name(temp);
	return Name;
}
CString CMyTools::GetClearFormatName(CString vName)
{
	if(vName==_T(""))
		return _T("");
	TCHAR* temp=vName.GetBuffer(0);
	TCHAR name[50]={0};
	int i=0;
	while(*temp!='.'){
		name[i]=*temp;
		i++;
		temp++;
	}
	CString Name(name);
	return Name;
}