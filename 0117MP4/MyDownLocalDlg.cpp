// MyDownLocalDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "MyDownLocalDlg.h"
#include "0117MP4Dlg.h"
#include "Packdef.h"
#include "MyTools.h"
#include "afxdialogex.h"


// CMyDownLocalDlg 对话框

IMPLEMENT_DYNAMIC(CMyDownLocalDlg, CDialogEx)

CMyDownLocalDlg::CMyDownLocalDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMyDownLocalDlg::IDD, pParent)
{

}

CMyDownLocalDlg::~CMyDownLocalDlg()
{
}

void CMyDownLocalDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_finishedLocalLst);
}


BEGIN_MESSAGE_MAP(CMyDownLocalDlg, CDialogEx)
	ON_LBN_DBLCLK(IDC_LIST1, &CMyDownLocalDlg::OnLbnDblclkList1)
END_MESSAGE_MAP()


// CMyDownLocalDlg 消息处理程序
//从本地文件夹中查找视频
void CMyDownLocalDlg::SerachLocalVideoes(CString filePath,vector<CString>& fileNames)
{
	//查找格式
	CString format[6]={_T("\\*.mp4"),_T("\\*.flv"),_T("\\*.3gp"),_T("\\*.avi"),_T("\\*.mov"),_T("\\*.wmv")};

	for(int i=0;i<6;i++){
		CString filePathx;
		filePathx=filePath+format[i];
		WIN32_FIND_DATA FindFileData;
		HANDLE hand=::FindFirstFile(filePathx,&FindFileData);
		if(INVALID_HANDLE_VALUE==hand)
		{
			continue;
		}
		while(true)
		{
			if(FILE_ATTRIBUTE_DIRECTORY==FindFileData.dwFileAttributes )
			{
				if(FindFileData.cFileName[0]!='.')
				{
					CString name=filePath+L"\\"+FindFileData.cFileName;
					//this->m_nameTofilePathsMap[FindFileData.cFileName]=name;
					this->SerachLocalVideoes(name,fileNames);
				}

			}else
			{
				fileNames.push_back(FindFileData.cFileName);
				CString name=filePath+L"\\"+FindFileData.cFileName;
				this->m_nameTofilePathsMap[FindFileData.cFileName]=name;

			}
			if(!FindNextFile(hand,&FindFileData))
				break;
		}
		FindClose(hand);
	}
}

void CMyDownLocalDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	int index=m_finishedLocalLst.GetCurSel();
	if(index==-1)
		return;
	CString vName;
	m_finishedLocalLst.GetText(index,vName);
	if(vName==_T(""))
		return;
	CString realName=CMyTools::GetClearFormatName(vName);
	CMy0117MP4Dlg*pthis=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	if(pthis->m_listDlg.m_listName.FindString(-1,realName)==LB_ERR)
		pthis->m_listDlg.m_listName.AddString(realName);
	pthis->m_listDlg.m_nameToPathMap[realName]=m_nameTofilePathsMap[vName];
	//将路径改为本地路径
	pthis->m_listDlg.m_videoPath=m_nameTofilePathsMap[vName];
	pthis->m_listDlg.m_playingName=realName;
	//先停止当前视频
	pthis->OnStnClickedStopBu();
	//改变为播放状态
	pthis->m_isPlayBit=true;
	pthis->OnStnClickedPlayBu();
	pthis->ShowWindow(SW_SHOWNORMAL);
	m_finishedLocalLst.SetCurSel(-1);
}


BOOL CMyDownLocalDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	return TRUE;  // return TRUE unless you set the focus to a control

}

bool CMyDownLocalDlg::ShowVideos()
{
	m_finishedLocalLst.ResetContent();
	vector<CString> fileNames;
	SerachLocalVideoes(theApp.g_HistVideoPath,fileNames);
	if(fileNames.size()>0)
	{
		for(unsigned i=0;i<fileNames.size();i++)
		{
			m_finishedLocalLst.AddString(fileNames[i]);
		}
	}
	return true;
}