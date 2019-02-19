#pragma once


// PlayListBox
//#include "MyComDlg.h"
#include "TestThreadPool.h"
#include "MyTools.h"
#include "MyDownTaskDlg.h"
#include "MySetConfigDlg.h"
#include "Packdef.h"
#include <stdio.h>
#include <Winhttp.h>
#pragma comment(lib,"Winhttp.lib")
class DownLoadTask;
typedef void(*DownLoadCallback)(int ContentSize, int CUR_LEN);
typedef struct _URL_INFO
{
    WCHAR szScheme[512];
    WCHAR szHostName[512];
    WCHAR szUserName[512];
    WCHAR szPassword[512];
    WCHAR szUrlPath[512];
    WCHAR szExtraInfo[512];
}URL_INFO, *PURL_INFO;
//下载任务类(为方便线程池的使用)
class DownLoadTask:public CTestTask
{
private:
	wchar_t Url[300];
	wchar_t FileName[300];
public:
	int nIteam;						//记录是哪一行
	int currentIteam;
	LVFINDINFO info;
	CMyDownLoadListDlg* downListDlg;//下载对话框
	CMyDownFinishedDlg* finishedDlg;//下载完成对话框
public:
	void SetTaskParams(const wchar_t *Urlx,const wchar_t *FileNamex)
	{
		wcscpy_s(Url,Urlx);
		wcscpy_s(FileName,FileNamex);
		info.flags=LVFI_PARTIAL;
	}
	//下载视频 回调函数
	void DownLoadCallBackFun(int totalSize, int currentSize)
	{
		double currentLen=currentSize;
		double rateDou=(currentLen/totalSize)*100;
		int rate=(int)rateDou;
		//设置进度
		downListDlg->m_processList.SetItemData(nIteam,rate);
	}
public:
	virtual void MakeTask()
	{
		//当调用这个函数时说明已经开始执行这个下载任务
		downListDlg->m_processList.SetItemText(nIteam,3,_T("正在下载"));
		URL_INFO url_info = { 0 };
		URL_COMPONENTSW lpUrlComponents = { 0 };
		lpUrlComponents.dwStructSize = sizeof(lpUrlComponents);
		lpUrlComponents.lpszExtraInfo = url_info.szExtraInfo;
		lpUrlComponents.lpszHostName = url_info.szHostName;
		lpUrlComponents.lpszPassword = url_info.szPassword;
		lpUrlComponents.lpszScheme = url_info.szScheme;
		lpUrlComponents.lpszUrlPath = url_info.szUrlPath;
		lpUrlComponents.lpszUserName = url_info.szUserName;

		lpUrlComponents.dwExtraInfoLength = 
			lpUrlComponents.dwHostNameLength = 
			lpUrlComponents.dwPasswordLength = 
			lpUrlComponents.dwSchemeLength = 
			lpUrlComponents.dwUrlPathLength = 
			lpUrlComponents.dwUserNameLength = 512;

		WinHttpCrackUrl(Url, 0, ICU_ESCAPE, &lpUrlComponents);

		// 创建一个会话
		HINTERNET hSession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
		DWORD dwReadBytes, dwSizeDW = sizeof(dwSizeDW), dwContentSize, dwIndex = 0;
		// 创建一个连接
		HINTERNET hConnect = WinHttpConnect(hSession, lpUrlComponents.lpszHostName, lpUrlComponents.nPort, 0);
		// 创建一个请求，先查询内容的大小
		HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"HEAD", lpUrlComponents.lpszUrlPath, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH);
		WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
		WinHttpReceiveResponse(hRequest, 0);
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwContentSize, &dwSizeDW, &dwIndex);
		WinHttpCloseHandle(hRequest);

		// 创建一个请求，获取数据
		hRequest = WinHttpOpenRequest(hConnect, L"GET", lpUrlComponents.lpszUrlPath, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH);
		WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
		WinHttpReceiveResponse(hRequest, 0);

		// 分段回调显示进度
		DWORD BUF_LEN = 1024, ReadedLen = 0;
		BYTE *pBuffer = NULL;
		pBuffer = new BYTE[BUF_LEN];

		HANDLE hFile = CreateFileW(FileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//-----------------------------------------------------------
		//设置文件大小
		WCHAR wStr[30]={0};
		DWORD totalNum= (dwContentSize/1024);
		_i64tot_s(dwContentSize,wStr,30,10);
		CString totalSize=wStr;
		if(totalNum==0){//小于1k
			downListDlg->m_processList.SetItemText(nIteam,2,totalSize+L"B");
		}else if(totalNum>=1000){//大于等于1MB
			DWORD totalNumMB=totalNum/1000;
			WCHAR Str[30]={0};
			_i64tot_s(totalNumMB,Str,30,10);
			CString totalStrMb=Str;
			downListDlg->m_processList.SetItemText(nIteam,2,totalStrMb+L"MB");
		}
		else{
			downListDlg->m_processList.SetItemText(nIteam,2,totalSize+L"K");
		}
		//------------------------------------------------------------
		while (dwContentSize > ReadedLen)
		{
			ZeroMemory(pBuffer, BUF_LEN);
			WinHttpReadData(hRequest, pBuffer, BUF_LEN, &dwReadBytes);
			ReadedLen += dwReadBytes;

			// 写入文件
			WriteFile(hFile, pBuffer, dwReadBytes, &dwReadBytes, NULL);
			// 进度回调
			DownLoadCallBackFun(dwContentSize, ReadedLen);

		}

		CloseHandle(hFile);
		delete pBuffer;


		/*
		// 一次性写入整个文件
		BYTE *pBuffer = NULL;

		pBuffer = new BYTE[dwContentSize];
		ZeroMemory(pBuffer, dwContentSize);
		//do{
			WinHttpReadData(hRequest, pBuffer, dwContentSize, &dwReadBytes);
			Func(dwContentSize, dwReadBytes);
		//} while (dwReadBytes == 0);
    

		HANDLE hFile = CreateFileW(FileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		WriteFile(hFile, pBuffer, dwContentSize, &dwReadBytes, NULL);
		CloseHandle(hFile);

		delete pBuffer;
		*/
		WinHttpCloseHandle(hRequest);
		WinHttpCloseHandle(hConnect);
		WinHttpCloseHandle(hSession);
		//设置下载任务完成后显示
 		downListDlg->m_processList.SetItemText(nIteam,3,_T("下载完成"));
		//有一个转换过程
		Sleep(1000);
		CString videoName=CMyTools::GetPlayingName(FileName);
		finishedDlg->m_FinishedDownloadLst.AddString(videoName);
		CString path=theApp.g_DownLoadVideoPath;
		path+=_T("\\");
		path+=videoName;
		finishedDlg->m_finishedToPathMap[videoName]=path;
		info.psz=videoName;
		currentIteam=downListDlg->m_processList.FindItem(&info);
		downListDlg->m_processList.DeleteItem(currentIteam);
	}
};
class CMyComDlg;
class PlayListBox : public CListBox
{
	DECLARE_DYNAMIC(PlayListBox)

public:
	PlayListBox();
	virtual ~PlayListBox();

protected:
	DECLARE_MESSAGE_MAP()
private:
	CMyComDlg* m_comdlg;
	
	CTestThreadPool pool;
public:
	void SetPlayListComDlg(CMyComDlg* m_comdlgx)
	{
		if(m_comdlgx)
			m_comdlg=m_comdlgx;
	}
public:
	CMenu m_menu;				//列表菜单
	//CMyDownLoadListDlg m_downListDlg;	//下载任务列表
	CMyDownTaskDlg m_downTaskDlg;
	CMySetConfigDlg m_SetConfigDlg;
public:
	void DownLoadVideoInUrl(CString urlc,CString vName);
public:
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTttDownLoad();
	afx_msg void OnMenuDownListShow();
	afx_msg void OnTtt32781();
	afx_msg void OnTtt32780();
	afx_msg void OnTtt32782();
	afx_msg void OnTtt32786();
	//afx_msg void OnTtt32787();
	afx_msg void OnTttSetConfig();
};




