
// 0117MP4.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "0117MP4.h"
#include "0117MP4Dlg.h"
#include "UDPMediator.h"
#include <time.h>
#pragma comment(lib,"lib\\SkinPPWTL.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMy0117MP4App

BEGIN_MESSAGE_MAP(CMy0117MP4App, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CMy0117MP4App ����

CMy0117MP4App::CMy0117MP4App()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CMy0117MP4App ����

CMy0117MP4App theApp;


// CMy0117MP4App ��ʼ��

BOOL CMy0117MP4App::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ���Windows Native���Ӿ����������Ա��� MFC �ؼ�����������
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));
	/*skin\\Aura.ssk*/
	/*skin\\bOzen.ssk*/
	/*skin\\Devoir.ssk*/
	/*skin\\Mako.ssk*/
	/*skin\\RedCopper.ssk*/
	/*skin\\Royale.ssk*/
	/*skin\\SlickOS2.ssk*/
	/*skin\\thinblue.ssk*/
	/*skin\\XP-Home.ssk*/
	/*skin\\XP-Metallic.ssk*/
	
	m_videoManager = new VideoManager;
	m_pUDPMediator = new UDPMediator;
	//��ʼ��m_videoManager
	m_videoManager->InitPlayer();
	//����װ��ͼ���ļ���
	if(!PathIsDirectory(g_AppPath)){
		CreateDirectory(g_AppPath,NULL);
	}
	if(!PathIsDirectory(_T("C:\\fengteng\\screenshot"))){
		CreateDirectory(_T("C:\\fengteng\\screenshot"),NULL);
	}
	if(!PathIsDirectory(_T("C:\\fengteng\\video"))){
		CreateDirectory(_T("C:\\fengteng\\video"),NULL);
	}
	//��ȡ�����ļ�
	if(this->ReadConfig())
	{
		CString VideoDownPath = this->GetVideoDown();
		CString VideoHistPath = this->GetVideoHist();
		CString ScreenShotPath = this->GetScreenShot();
		_tcscpy_s(g_DownLoadVideoPath,VideoDownPath.GetBuffer());
		_tcscpy_s(g_HistVideoPath,VideoHistPath.GetBuffer());
		_tcscpy_s(g_ScreenSnapShotPath,ScreenShotPath.GetBuffer());
	}else
	{
		CString VideoDownPath = _T("C:\\fengteng\\video");
		CString VideoHistPath = _T("C:\\fengteng\\video");
		CString ScreenShotPath = _T("C:\\fengteng\\screenshot");
		_tcscpy_s(g_DownLoadVideoPath,VideoDownPath.GetBuffer());
		_tcscpy_s(g_HistVideoPath,VideoHistPath.GetBuffer());
		_tcscpy_s(g_ScreenSnapShotPath,ScreenShotPath.GetBuffer());
	}
	//�������������
	srand(0);
	//_CrtSetBreakAlloc(354); 
	CMy0117MP4Dlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}
	else if (nResponse == -1)
	{
		TRACE(traceAppMsg, 0, "����: �Ի��򴴽�ʧ�ܣ�Ӧ�ó���������ֹ��\n");
		TRACE(traceAppMsg, 0, "����: ������ڶԻ�����ʹ�� MFC �ؼ������޷� #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS��\n");
	}

	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

bool CMy0117MP4App::ReadConfig()
{
	return m_ReadConfig.ReadConfig();
}
bool CMy0117MP4App::WriteConfig()
{
	return m_WriteConfig.WriteConfig();
}
CString CMy0117MP4App::GetVideoDown()
{
	string path = m_ReadConfig.GetVideoDown();
	WCHAR* wStr = CMyTools::EnCodeUtfToWCHAR(const_cast<char*>(path.c_str()));
	CString VideoDown(wStr);
	delete[] wStr;
	wStr = NULL;
	return VideoDown;
}
CString CMy0117MP4App::GetVideoHist()
{
	string path = m_ReadConfig.GetVideoHist();
	WCHAR* wStr = CMyTools::EnCodeUtfToWCHAR(const_cast<char*>(path.c_str()));
	CString VideoHist(wStr);
	delete[] wStr;
	wStr = NULL;
	return VideoHist;
}
CString CMy0117MP4App::GetScreenShot()
{
	string path = m_ReadConfig.GetScreenShot();
	WCHAR* wStr = CMyTools::EnCodeUtfToWCHAR(const_cast<char*>(path.c_str()));
	CString ScreenShot(wStr);
	delete[] wStr;
	wStr = NULL;
	return ScreenShot;
}
bool CMy0117MP4App::SetVideoDown(CString VideoDown)
{
	char* str = CMyTools::EnCodeWCHARToUtf(VideoDown.GetBuffer());
	string videodown(str);
	delete[] str;
	str = NULL;
	return m_WriteConfig.SetVideoDown(videodown);
}
bool CMy0117MP4App::SetVideoHist(CString VideoHist)
{
	char* str = CMyTools::EnCodeWCHARToUtf(VideoHist.GetBuffer());
	string videohist(str);
	delete[] str;
	str = NULL;
	return m_WriteConfig.SetVideoHist(videohist);
}
bool CMy0117MP4App::SetScreenShot(CString ScreenShot)
{
	char* str = CMyTools::EnCodeWCHARToUtf(ScreenShot.GetBuffer());
	string screenshot(str);
	delete[] str;
	str = NULL;
	return m_WriteConfig.SetScreenShot(screenshot);
}

int CMy0117MP4App::ExitInstance()
{
	// TODO: �ڴ����ר�ô����/����û���
	if(m_videoManager){
		delete m_videoManager;
		m_videoManager=NULL;
	}
	if(m_pUDPMediator){
		delete m_pUDPMediator;
		m_pUDPMediator=NULL;
	}
	skinppExitSkin();
	return CWinApp::ExitInstance();
}
