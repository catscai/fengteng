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
//����������(Ϊ�����̳߳ص�ʹ��)
class DownLoadTask:public CTestTask
{
private:
	wchar_t Url[300];
	wchar_t FileName[300];
public:
	int nIteam;						//��¼����һ��
	int currentIteam;
	LVFINDINFO info;
	CMyDownLoadListDlg* downListDlg;//���ضԻ���
	CMyDownFinishedDlg* finishedDlg;//������ɶԻ���
public:
	void SetTaskParams(const wchar_t *Urlx,const wchar_t *FileNamex)
	{
		wcscpy_s(Url,Urlx);
		wcscpy_s(FileName,FileNamex);
		info.flags=LVFI_PARTIAL;
	}
	//������Ƶ �ص�����
	void DownLoadCallBackFun(int totalSize, int currentSize)
	{
		double currentLen=currentSize;
		double rateDou=(currentLen/totalSize)*100;
		int rate=(int)rateDou;
		//���ý���
		downListDlg->m_processList.SetItemData(nIteam,rate);
	}
public:
	virtual void MakeTask()
	{
		//�������������ʱ˵���Ѿ���ʼִ�������������
		downListDlg->m_processList.SetItemText(nIteam,3,_T("��������"));
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

		// ����һ���Ự
		HINTERNET hSession = WinHttpOpen(NULL, WINHTTP_ACCESS_TYPE_NO_PROXY, NULL, NULL, 0);
		DWORD dwReadBytes, dwSizeDW = sizeof(dwSizeDW), dwContentSize, dwIndex = 0;
		// ����һ������
		HINTERNET hConnect = WinHttpConnect(hSession, lpUrlComponents.lpszHostName, lpUrlComponents.nPort, 0);
		// ����һ�������Ȳ�ѯ���ݵĴ�С
		HINTERNET hRequest = WinHttpOpenRequest(hConnect, L"HEAD", lpUrlComponents.lpszUrlPath, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH);
		WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
		WinHttpReceiveResponse(hRequest, 0);
		WinHttpQueryHeaders(hRequest, WINHTTP_QUERY_CONTENT_LENGTH | WINHTTP_QUERY_FLAG_NUMBER, NULL, &dwContentSize, &dwSizeDW, &dwIndex);
		WinHttpCloseHandle(hRequest);

		// ����һ�����󣬻�ȡ����
		hRequest = WinHttpOpenRequest(hConnect, L"GET", lpUrlComponents.lpszUrlPath, L"HTTP/1.1", WINHTTP_NO_REFERER, WINHTTP_DEFAULT_ACCEPT_TYPES, WINHTTP_FLAG_REFRESH);
		WinHttpSendRequest(hRequest, WINHTTP_NO_ADDITIONAL_HEADERS, 0, WINHTTP_NO_REQUEST_DATA, 0, 0, 0);
		WinHttpReceiveResponse(hRequest, 0);

		// �ֶλص���ʾ����
		DWORD BUF_LEN = 1024, ReadedLen = 0;
		BYTE *pBuffer = NULL;
		pBuffer = new BYTE[BUF_LEN];

		HANDLE hFile = CreateFileW(FileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		//-----------------------------------------------------------
		//�����ļ���С
		WCHAR wStr[30]={0};
		DWORD totalNum= (dwContentSize/1024);
		_i64tot_s(dwContentSize,wStr,30,10);
		CString totalSize=wStr;
		if(totalNum==0){//С��1k
			downListDlg->m_processList.SetItemText(nIteam,2,totalSize+L"B");
		}else if(totalNum>=1000){//���ڵ���1MB
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

			// д���ļ�
			WriteFile(hFile, pBuffer, dwReadBytes, &dwReadBytes, NULL);
			// ���Ȼص�
			DownLoadCallBackFun(dwContentSize, ReadedLen);

		}

		CloseHandle(hFile);
		delete pBuffer;


		/*
		// һ����д�������ļ�
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
		//��������������ɺ���ʾ
 		downListDlg->m_processList.SetItemText(nIteam,3,_T("�������"));
		//��һ��ת������
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
	CMenu m_menu;				//�б�˵�
	//CMyDownLoadListDlg m_downListDlg;	//���������б�
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




