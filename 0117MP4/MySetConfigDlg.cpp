// MySetConfigDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MySetConfigDlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "SelectFolderDlg.h"
// CMySetConfigDlg 对话框

IMPLEMENT_DYNAMIC(CMySetConfigDlg, CDialogEx)

CMySetConfigDlg::CMySetConfigDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMySetConfigDlg::IDD, pParent)
{

}

CMySetConfigDlg::~CMySetConfigDlg()
{
}

void CMySetConfigDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_VideoDownloadPathEdit);
	DDX_Control(pDX, IDC_EDIT3, m_VideoHistPathEdit);
	DDX_Control(pDX, IDC_EDIT4, m_ScreenShotPathEdit);
}


BEGIN_MESSAGE_MAP(CMySetConfigDlg, CDialogEx)
	ON_BN_CLICKED(IDC_VIDEODOWNPATH, &CMySetConfigDlg::OnBnClickedVideodownpath)
	ON_BN_CLICKED(IDC_BUTTON8, &CMySetConfigDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_SCREENSHOTPATH, &CMySetConfigDlg::OnBnClickedScreenshotpath)
	ON_BN_CLICKED(IDC_SAVEALLSET, &CMySetConfigDlg::OnBnClickedSaveallset)
	ON_BN_CLICKED(IDC_CANCELSET, &CMySetConfigDlg::OnBnClickedCancelset)
END_MESSAGE_MAP()


// CMySetConfigDlg 消息处理程序


void CMySetConfigDlg::OnBnClickedVideodownpath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString VideoDownPath = CSelectFolderDlg::SerachFolder(_T("选择视频下载保存路径:"));
	if(VideoDownPath != _T(""))
		m_VideoDownloadPathEdit.SetWindowText(VideoDownPath);
	UpdateData(FALSE);
}


void CMySetConfigDlg::OnBnClickedButton8()
{
	// TODO: 在此添加控件通知处理程序代码
	CString VideoHistPath = CSelectFolderDlg::SerachFolder(_T("选择视频查找路径:"));
	if(VideoHistPath != _T(""))
		m_VideoHistPathEdit.SetWindowText(VideoHistPath);
	UpdateData(FALSE);
}


void CMySetConfigDlg::OnBnClickedScreenshotpath()
{
	// TODO: 在此添加控件通知处理程序代码
	CString ScreenShotPath = CSelectFolderDlg::SerachFolder(_T("选择截图保存路径:"));
	if(ScreenShotPath != _T(""))
		m_ScreenShotPathEdit.SetWindowText(ScreenShotPath);
	UpdateData(FALSE);
}


void CMySetConfigDlg::OnBnClickedSaveallset()
{
	// TODO: 在此添加控件通知处理程序代码
	CString VideoDownPath;
	CString VideoHistPath;
	CString ScreenShotPath;
	m_VideoDownloadPathEdit.GetWindowText(VideoDownPath);
	m_VideoHistPathEdit.GetWindowText(VideoHistPath);
	m_ScreenShotPathEdit.GetWindowText(ScreenShotPath);
	_tcscpy_s(theApp.g_DownLoadVideoPath,VideoDownPath.GetBuffer());
	_tcscpy_s(theApp.g_HistVideoPath,VideoHistPath.GetBuffer());
	_tcscpy_s(theApp.g_ScreenSnapShotPath,ScreenShotPath.GetBuffer());
	theApp.SetVideoDown(VideoDownPath);
	theApp.SetVideoHist(VideoHistPath);
	theApp.SetScreenShot(ScreenShotPath);
	if(theApp.WriteConfig())
		MessageBox(_T("已保存！"));
	else
		MessageBox(_T("保存失败！"));
}


void CMySetConfigDlg::OnBnClickedCancelset()
{
	// TODO: 在此添加控件通知处理程序代码
	CString VideoDownPath(theApp.g_DownLoadVideoPath);
	CString VideoHistPath(theApp.g_HistVideoPath);
	CString ScreenShotPath(theApp.g_ScreenSnapShotPath);
	m_VideoDownloadPathEdit.SetWindowText(VideoDownPath);
	m_VideoHistPathEdit.SetWindowText(VideoHistPath);
	m_ScreenShotPathEdit.SetWindowText(ScreenShotPath);
	UpdateData(FALSE);
	this->ShowWindow(SW_HIDE);
}


BOOL CMySetConfigDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	this->SetWindowText(_T("修改配置"));
	OnBnClickedCancelset();
	return TRUE;  // return TRUE unless you set the focus to a control
}
