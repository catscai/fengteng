
// 0117MP4Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "0117MP4.h"
#include "0117MP4Dlg.h"
#include "afxdialogex.h"
#include "Packdef.h"
#include "MyTools.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy0117MP4Dlg 对话框



CMy0117MP4Dlg::CMy0117MP4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMy0117MP4Dlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_playBit=NULL;
	m_pauseBit=NULL;
	m_isPlayBit=true;
}

void CMy0117MP4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Control(pDX, IDC_SLIDER1, m_PlaySlider);
	//m_PlaySlider
	DDX_Control(pDX, IDB_PLAY_BU, m_PlayButton);
	DDX_Control(pDX, IDC_SLIDER_PROCESS, m_sliderProcess);
	DDX_Control(pDX, IDC_SLIDER_VOLUME, m_sliderVolume);
	//DDX_Control(pDX, IDC_EDIT1, m_playingName);
	DDX_Control(pDX, IDC_STATIC_PLAYEND, m_PlayMaxTime);
	DDX_Control(pDX, IDC_STATIC_PLAYBEGIN, m_PlayMinTime);
	DDX_Control(pDX, IDC_STATIC_PLAYNAME, m_PlayingName);
	DDX_Control(pDX, IDC_BUTTON10, m_buttonWord);
	DDX_Control(pDX, IDC_BUTTON9, m_buttonLogin);
	DDX_Control(pDX, IDC_BUTTON11, m_CollectButn);
	DDX_Control(pDX, IDC_BUTTON4, m_DownloadButn);
	DDX_Control(pDX, IDC_BUTTON6, m_SreenShotButn);
	DDX_Control(pDX, IDC_BUTTON7, m_SwitchListButn);
	DDX_Control(pDX, IDB_LAST_BU, m_LastPlay);
	DDX_Control(pDX, IDB_NEXT_BU, m_NextPlay);
	DDX_Control(pDX, IDB_STOP_BU, m_StopPlay);
}

BEGIN_MESSAGE_MAP(CMy0117MP4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDB_PLAY_BU, &CMy0117MP4Dlg::OnStnClickedPlayBu)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON7, &CMy0117MP4Dlg::OnBnClickedButton7)
	ON_STN_CLICKED(IDB_STOP_BU, &CMy0117MP4Dlg::OnStnClickedStopBu)
	ON_WM_TIMER()
	ON_WM_HSCROLL()
	ON_BN_CLICKED(IDC_BUTTON6, &CMy0117MP4Dlg::OnBnClickedButton6)
	ON_STN_CLICKED(IDB_NEXT_BU, &CMy0117MP4Dlg::OnStnClickedNextBu)
	ON_STN_CLICKED(IDB_LAST_BU, &CMy0117MP4Dlg::OnStnClickedLastBu)
	ON_BN_CLICKED(IDC_BUTTON9, &CMy0117MP4Dlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON10, &CMy0117MP4Dlg::OnBnClickedButton10)
	ON_MESSAGE(PUBLIC_WORD,&CMy0117MP4Dlg::OnPublicWord)
	ON_MESSAGE(LOGIN_SUCCESS_MEG,&CMy0117MP4Dlg::OnLogingSuccess)
	ON_MESSAGE(LOGIN_FAILTURE_MEG,&CMy0117MP4Dlg::OnLogingFailture)

	ON_BN_CLICKED(IDC_BUTTON4, &CMy0117MP4Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON11, &CMy0117MP4Dlg::OnBnClickedButton11)
	ON_WM_MOVE()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CMy0117MP4Dlg 消息处理程序
//收到公告消息
LRESULT CMy0117MP4Dlg::OnPublicWord(WPARAM w, LPARAM l)
{
	char* content=(char*)w;
	WCHAR* Wt=CMyTools::EnCodeUtfToWCHAR(content);
	CString publicWord=Wt;
	delete[] Wt;
	//设置公告内容
	m_wordDlg.m_publicBoard.SetWindowText(publicWord);
	//改变公告按钮颜色 用来表示有新的系统公告
	m_buttonWord.SetWindowText(_T("新公告"));
	return 0;

}
//登录成功消息
LRESULT CMy0117MP4Dlg::OnLogingSuccess(WPARAM w, LPARAM l)
{
	char* username=(char*)w;
	WCHAR* wName=CMyTools::EnCodeUtfToWCHAR(username);
	CString UserName(wName);
	delete[] wName;
	m_buttonLogin.SetWindowText(UserName);
	m_loginDlg.ShowWindow(SW_HIDE);
	return 0;
}
LRESULT CMy0117MP4Dlg::OnLogingFailture(WPARAM w, LPARAM l)
{
	AfxMessageBox(_T("账号或密码不正确"));
	return 0;
}
BOOL CMy0117MP4Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	//设置图标
	HICON myIcon=AfxGetApp()->LoadIcon(IDI_ICON1);
	skinppLoadSkin("skin\\Devoir.ssk");
	SetIcon(myIcon, TRUE);			// 设置大图标
	SetIcon(myIcon, FALSE);		// 设置小图标
	this->SetWindowText(_T("风腾视频"));
	//// TODO: 在此添加额外的初始化代码
	//设置焦点
	this->SetFocus();
	//开启UDP服务器
	theApp.getUDPMediator()->OpenServer();
	m_brush.CreateSolidBrush(RGB(158,158,158));
	//加载播放暂停按钮图片
	m_playBit=::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_PLAY_BU));
	m_pauseBit=::LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_PAUSE_BU));
	//创建列表窗口,显示
	m_listDlg.Create(IDD_MYCOMDLG,NULL);
	m_listDlg.SetWindowText(_T(""));
	CRect rect;
	this->GetWindowRect(&rect);
	rect.top+=50;
	rect.bottom+=50;
	rect.right+=100;
	rect.left+=116;
	this->MoveWindow(rect);
	CRect listRect;
	this->GetWindowRect(&listRect);
	m_listDlg.MoveWindow(listRect.right + 16,listRect.top,350,654);
	m_listDlg.ShowWindow(SW_SHOW);
	//OnBnClickedButton7();
	//theApp.SetDialogBkColor(corolDlg);
	//设置进度条相关
	m_sliderProcess.SetRange(0,SLIDER_PLAY_RANGE);
	m_sliderProcess.SetPos(0);
	m_sliderVolume.SetRange(0,MAX_PLAY_VOLUME);
	m_sliderVolume.SetPos(DEF_PLAY_VOLUME);
	m_CurrentVolume = DEF_PLAY_VOLUME;	//记录音量
	//初始化正在播放名称
	m_PlayingName.SetWindowText(_T(""));
	m_PlayMaxTime.SetWindowText(_T(""));
	m_PlayMinTime.SetWindowText(_T(""));
	m_isSetMaxTime=false;
	//设置创建登录，注册窗口名称
	m_loginDlg.Create(IDD_LOGINDLG,NULL);
	m_loginDlg.SetWindowText(_T("登录"));
	m_loginDlg.SetWindowPos(GetDlgItem(IDD_MY0117MP4_DIALOG),-1,0,0,0,3);
	m_registerDlg.Create(IDD_REGISTER,NULL);
	m_registerDlg.SetWindowText(_T("用户注册"));
	m_registerDlg.SetWindowPos(GetDlgItem(IDD_MY0117MP4_DIALOG),-1,0,0,0,3);
	//设置公告窗口
	m_wordDlg.Create(IDD_PUBLICWORD,NULL);
	m_wordDlg.SetWindowText(_T("公告"));
	m_wordDlg.SetWindowPos(GetDlgItem(IDD_MY0117MP4_DIALOG),-1,0,0,0,3);
	//初始化 播放本地视频
	m_PlayNetVideoCount=0;
	//创建收藏窗口
	m_collectDlg.Create(IDD_COLLECT_DLG,NULL);
	m_collectDlg.SetWindowText(_T("我的收藏"));
	m_collectDlg.SetWindowPos(GetDlgItem(IDD_MY0117MP4_DIALOG),-1,0,0,0,3);
	CRect rectx;
	m_collectDlg.GetWindowRect(&rectx);
	rectx.left+=500;
	rectx.right+=500;
	m_collectDlg.MoveWindow(rectx);
	//得到当前窗口位置、和宽高
	this->GetWindowRect(&m_rect);
	//得到播放的picture控件的位置
	GetDlgItem(IDC_STATIC_PIC)->GetWindowRect(&m_rectPic);
	ScreenToClient(&m_rectPic);
	m_IsMaxPicture = false;
	m_picBit1.LoadBitmap(IDB_BLACKPLAY);
	m_picBit2.LoadBitmap(IDB_MAX_BACKPIC);
	m_picBit3.LoadBitmap(IDB_MAX_BLACK);
	//设置直播窗口
	//m_streamDlg.Create(IDD_PLAYING);
	//m_streamDlg.SetWindowText(_T("直播大厅"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMy0117MP4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMy0117MP4Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMy0117MP4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



HBRUSH CMy0117MP4Dlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor ==CTLCOLOR_DLG||pWnd==GetDlgItem(IDC_SLIDER_PROCESS)||pWnd==GetDlgItem(IDC_SLIDER_VOLUME))
	{ 
		return m_brush;
	}
	if(GetDlgItem(IDC_STATIC_PLAYNAME)==pWnd){
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(158,158,158));
		return m_brush;
	}
	if(pWnd==GetDlgItem(IDC_STATIC_PLAYEND)||pWnd==GetDlgItem(IDC_STATIC_PLAYBEGIN)){
		pDC->SetTextColor(RGB(0,0,0));
		pDC->SetBkColor(RGB(158,158,158));
		return m_brush;
	}
	return hbr;
}


void CMy0117MP4Dlg::OnStnClickedPlayBu()
{
	// TODO: 在此添加控件通知处理程序代码http://videos.fjhps.com/20180420/jKeEMWe0/index.m3u8
	//m_listDlg.m_videoPath = _T("http://v3-dy-y.ixigua.com/0d523e1e6fa62fd85e255466b599c78b/5b4ac0b0/video/m/220c9f7e5da64a14d598cbfc5f9d15e24dd1157708600001ba2e5d8c79c/");
	//位图切换
	if(m_isPlayBit)
	{
		if(m_listDlg.m_videoPath!=_T(""))
		{
			if(m_listDlg.m_videoManager){
				HWND nPlayHwnd=GetDlgItem(IDC_STATIC_PIC)->GetSafeHwnd();
				if(!nPlayHwnd)
					return;
				m_listDlg.m_videoManager->PlayNetOrLocal(m_listDlg.m_videoPath,nPlayHwnd);
				//添加到正在播放条中
				m_PlayingName.SetWindowText(m_listDlg.m_playingName);
				//重置MaxTime设置开关
				m_isSetMaxTime=false;
			}else
				return;
		}else{
			return ;
		}
		m_PlayButton.SetBitmap(m_pauseBit);
		m_isPlayBit=false;
		SetTimer(PLAY_PROCESS_TIMER,100,NULL);
		m_listDlg.m_videoManager->SetPlayerVolume(m_CurrentVolume);
	}
	else{
		if(m_listDlg.m_videoManager){
			m_listDlg.m_videoManager->PauseVideo();
		}else
			return;
		m_PlayButton.SetBitmap(m_playBit);
		m_isPlayBit=true;
	}
}

void CMy0117MP4Dlg::OnBnClickedButton7()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_listDlg.IsWindowVisible())
	{
		m_listDlg.ShowWindow(SW_HIDE);
	}else
	{
		this->GetWindowRect(m_rect);
		m_listDlg.MoveWindow(m_rect.left + m_rect.Width(),m_rect.top,350,654);
		m_listDlg.ShowWindow(SW_SHOW);
	}
}


void CMy0117MP4Dlg::OnStnClickedStopBu()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_listDlg.m_videoManager){
		m_listDlg.m_videoManager->StopVideo();
		KillTimer(PLAY_PROCESS_TIMER);
		//变回播放图标
		m_PlayButton.SetBitmap(m_playBit);
		m_isPlayBit=true;
		//重置播放滑块
		m_sliderProcess.SetPos(0);
		//清除正在播放视频文字
		m_PlayingName.SetWindowText(_T(""));
		//在线播放计数重置
		m_PlayNetVideoCount=0;
		m_PlayMinTime.SetWindowText(_T("0:0:0"));
		m_PlayMaxTime.SetWindowText(_T("0:0:0"));
		UpdateData(FALSE);
	}
}

void CMy0117MP4Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	long long totalTime=m_listDlg.m_videoManager->GetTotalPlayTimeL();
	long long currTime=m_listDlg.m_videoManager->GetCurrentPlayTimeL();
	if(totalTime > 0 && currTime/1000 == totalTime/1000){
			if(m_PlayNetVideoCount>0)
			{//正在播放的是在线视频所以要查找下一段 视频分段
				int nCount=m_listDlg.m_movieNameToLinkMap[m_listDlg.m_playingName].size()-1;
				if(m_PlayNetVideoCount<nCount){
					m_PlayNetVideoCount++;

					string link=m_listDlg.m_movieNameToLinkMap[m_listDlg.m_playingName][m_PlayNetVideoCount];
					char nlink[MAX_MOVIE_LINK]={0};
					strcpy_s(nlink,link.c_str());
					WCHAR*wStr=CMyTools::EnCodeUtfToWCHAR(nlink);
					CString Link(wStr);

					m_listDlg.m_videoPath=Link;
					m_isPlayBit=true;
					this->OnStnClickedPlayBu();
		
				}
			}
			OnStnClickedStopBu();

		}
	if(nIDEvent==PLAY_PROCESS_TIMER){
		long long nPos = 0;

		if(totalTime)
			nPos= currTime*1000/totalTime;

		if(!m_isSetMaxTime){
			CString MaxTime=m_listDlg.m_videoManager->GetTotalPlayTime();
			if(MaxTime!=_T("")){
				m_PlayMaxTime.SetWindowText(MaxTime);
				m_isSetMaxTime=true;
			}
		}
		if(m_IsMaxPicture == false){
			m_PlayMinTime.SetWindowText(m_listDlg.m_videoManager->GetCurrentPlayTime());
			m_sliderProcess.SetPos(static_cast<int>(nPos));
		}
		//UpdateData(FALSE);
	}
	
	CDialogEx::OnTimer(nIDEvent);
}


void CMy0117MP4Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if(pScrollBar->GetSafeHwnd()==m_sliderProcess.GetSafeHwnd()){
		int ntime=m_sliderProcess.GetPos();
		m_listDlg.m_videoManager->SetCurrentPlayTime(ntime);
	}
	if(pScrollBar->GetSafeHwnd()==m_sliderVolume.GetSafeHwnd()){
		m_CurrentVolume = m_sliderVolume.GetPos();
		m_listDlg.m_videoManager->SetPlayerVolume(m_CurrentVolume);
	}
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
}

//截屏
void CMy0117MP4Dlg::OnBnClickedButton6()
{
	// TODO: 在此添加控件通知处理程序代码
	//获取当前时间
	SYSTEMTIME nCT;
	GetLocalTime(&nCT);
	CString nfileName;
	nfileName.Format(_T("%ld%ld%ld%ld%ld%ld%ld"),nCT.wYear,nCT.wMonth,nCT.wDay,nCT.wHour,nCT.wMinute,nCT.wSecond,nCT.wMilliseconds);
	CString path=theApp.g_ScreenSnapShotPath;
	path+=_T("\\")+nfileName+g_ScreenSnapShotSty;
	nfileName=path;
	char nfilePath[MAX_PATH]={0};
	char*ntemp=CMyTools::EnCodeWCHARToUtf(nfileName.GetBuffer(0));
	strcpy_s(nfilePath,MAX_PATH,ntemp);
	m_listDlg.m_videoManager->ScreenSnapShot(nfilePath);
	delete[] ntemp;
}

//播放下一个
void CMy0117MP4Dlg::OnStnClickedNextBu()
{
	// TODO: 在此添加控件通知处理程序代码libvlc_Ended
	//如果播放列表为空或当前没有播放视频
	if(m_listDlg.m_nameToPathMap.empty()||libvlc_Playing!=m_listDlg.m_videoManager->GetPlayerStatus()){
		return;
	}
	CString nPlayingName=_T("");
	//得到正在播放视频名称
	m_PlayingName.GetWindowText(nPlayingName);
	int nindex=-1;
	//得到正在播放视频在播放列表中的下标
	nindex=m_listDlg.m_listName.FindString(-1,nPlayingName);
	if(nindex<0||nindex>=m_listDlg.m_listName.GetCount()-1)
		return;
	CString nWillPlay=_T("");
	//得到下一个视频名称
	m_listDlg.m_listName.GetText(nindex+1,nWillPlay);
	if(nWillPlay!=_T("")){
		//设置路径为下一个视频的路径
		m_listDlg.m_videoPath=m_listDlg.m_nameToPathMap[nWillPlay];
		//停止当前播放 然后播放下一个
		m_listDlg.m_playingName=nWillPlay;
		OnStnClickedStopBu();
		m_isPlayBit=true;
		OnStnClickedPlayBu();
	}
}

//播放上一个
void CMy0117MP4Dlg::OnStnClickedLastBu()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_listDlg.m_nameToPathMap.empty()||libvlc_Playing!=m_listDlg.m_videoManager->GetPlayerStatus()){
		return;
	}
	CString nPlayingName=_T("");
	//得到正在播放视频名称
	m_PlayingName.GetWindowText(nPlayingName);
	int nindex=-1;
	//得到正在播放视频在播放列表中的下标
	nindex=m_listDlg.m_listName.FindString(-1,nPlayingName);
	if(nindex<=0)
		return;
	CString nWillPlay=_T("");
	//得到上一个视频名称
	m_listDlg.m_listName.GetText(nindex-1,nWillPlay);
	if(nWillPlay!=_T("")){
		//设置路径为上一个视频的路径
		m_listDlg.m_videoPath=m_listDlg.m_nameToPathMap[nWillPlay];
		//停止当前播放 然后播放上一个
		m_listDlg.m_playingName=nWillPlay;
		OnStnClickedStopBu();
		m_isPlayBit=true;
		OnStnClickedPlayBu();
	}
}

void CMy0117MP4Dlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	m_collectDlg.DestroyWindow();
	DestroyIcon(m_hIcon);
	if(m_listDlg.m_videoManager)
		m_listDlg.m_videoManager->StopVideo();
	DeleteObject(m_pauseBit);
	DeleteObject(m_playBit);
	m_brush.DeleteObject();
	m_pauseBit = NULL;
	m_playBit = NULL;
	CLOSEINFO info;
	info.RqType = CLOSE_CLIENT;
	theApp.getUDPMediator()->SendData((char*)&info,sizeof(info));
	theApp.getUDPMediator()->CloseServer();

}

BOOL CMy0117MP4Dlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->hwnd != this->m_listDlg.m_editVideoName.GetSafeHwnd()&&pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		OnStnClickedPlayBu();
		return FALSE;
	}
	if(pMsg->message == WM_KEYUP&&pMsg->wParam == VK_SPACE)
	{
		//空格控制播放或者暂停
		return FALSE;
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN)
	{
		//空格控制播放或者暂停
		return FALSE;
	}
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		//if(m_IsMaxPicture)
		//{
		//	this->MoveWindow(m_rect);
		//	GetDlgItem(IDC_STATIC_PIC)->MoveWindow(m_rectPic);
		//	((CStatic*)GetDlgItem(IDC_STATIC_PIC))->SetBitmap((HBITMAP)m_picBit1);
		//	RecoverAllCtrl();
		//	OnBnClickedButton7();
		//	m_IsMaxPicture = false;
		//}
		return FALSE;
	}
	//return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

//弹出登录窗口
void CMy0117MP4Dlg::OnBnClickedButton9()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_loginDlg.IsWindowVisible())
	{
		m_loginDlg.ShowWindow(SW_HIDE);
	}else
	{
		m_loginDlg.ShowWindow(SW_SHOW);
	}
}


//弹出公告窗口
void CMy0117MP4Dlg::OnBnClickedButton10()
{
	// TODO: 在此添加控件通知处理程序代码
	m_wordDlg.ShowWindow(SW_SHOW);
	m_buttonWord.SetWindowText(_T("公告"));
}


//下载当前播放视频
void CMy0117MP4Dlg::OnBnClickedButton4()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	CString vName;
	this->m_PlayingName.GetWindowText(vName);
	if(vName==_T(""))
		return;
	//在map中找到url
	CString urlc=this->m_listDlg.m_nameToPathMap[vName];
	this->m_listDlg.m_listName.DownLoadVideoInUrl(urlc,vName);
}

//点击收藏
void CMy0117MP4Dlg::OnBnClickedButton11()
{
	// TODO: 在此添加控件通知处理程序代码
	if(m_collectDlg.IsWindowVisible())
	{
		m_collectDlg.ShowWindow(SW_HIDE);
	}else
	{
		m_collectDlg.ShowWindow(SW_SHOW);
	}
}


void CMy0117MP4Dlg::OnMove(int x, int y)
{
	CDialogEx::OnMove(x, y);

	// TODO: 在此处添加消息处理程序代码
	//this->GetWindowRect(m_rect);
	//m_listDlg.MoveWindow(m_rect.left + m_rect.Width(),m_rect.top,350,654);
	//if(m_listDlg.GetSafeHwnd()){
	//	m_listDlg.SetWindowPos(this,x,y+m_rect.Width(),350,654,SWP_SHOWWINDOW  );
	//	m_listDlg.ShowWindow(SW_SHOW);
	//}
}


void CMy0117MP4Dlg::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);
	if(nType == SIZE_MAXIMIZED)
	{
		HideAllCtrl();
		CRect rect;
		GetDesktopWindow()->GetWindowRect(&rect);
		GetDlgItem(IDC_STATIC_PIC)->MoveWindow(rect);
		if(m_isPlayBit)
			((CStatic*)GetDlgItem(IDC_STATIC_PIC))->SetBitmap((HBITMAP)m_picBit2);
		else
			((CStatic*)GetDlgItem(IDC_STATIC_PIC))->SetBitmap((HBITMAP)m_picBit3);
		
		//OnBnClickedButton7();
		m_IsMaxPicture = true;
	}
	if(m_IsMaxPicture == true && nType == SIZE_RESTORED)
	{
		GetDlgItem(IDC_STATIC_PIC)->MoveWindow(m_rectPic);
		((CStatic*)GetDlgItem(IDC_STATIC_PIC))->SetBitmap((HBITMAP)m_picBit1);
		RecoverAllCtrl();
		//OnBnClickedButton7();
		m_IsMaxPicture = false;
	}
	// TODO: 在此处添加消息处理程序代码
}

bool   CMy0117MP4Dlg::HideAllCtrl()
{
	m_PlayButton.ShowWindow(SW_HIDE);
	m_PlayingName.ShowWindow(SW_HIDE);
	m_PlayMaxTime.ShowWindow(SW_HIDE);
	m_PlayMinTime.ShowWindow(SW_HIDE);
	m_buttonWord.ShowWindow(SW_HIDE);
	m_buttonLogin.ShowWindow(SW_HIDE);
	m_sliderProcess.ShowWindow(SW_HIDE);
	m_sliderVolume.ShowWindow(SW_HIDE);
	m_CollectButn.ShowWindow(SW_HIDE);
	m_DownloadButn.ShowWindow(SW_HIDE);
	m_SreenShotButn.ShowWindow(SW_HIDE);
	m_SwitchListButn.ShowWindow(SW_HIDE);
	m_LastPlay.ShowWindow(SW_HIDE);
	m_NextPlay.ShowWindow(SW_HIDE);
	m_StopPlay.ShowWindow(SW_HIDE);
	return true;
}
bool   CMy0117MP4Dlg::RecoverAllCtrl()
{
	m_PlayButton.ShowWindow(SW_SHOW);
	m_PlayingName.ShowWindow(SW_SHOW);
	m_PlayMaxTime.ShowWindow(SW_SHOW);
	m_PlayMinTime.ShowWindow(SW_SHOW);
	m_buttonWord.ShowWindow(SW_SHOW);
	m_buttonLogin.ShowWindow(SW_SHOW);
	m_sliderProcess.ShowWindow(SW_SHOW);
	m_sliderVolume.ShowWindow(SW_SHOW);
	m_CollectButn.ShowWindow(SW_SHOW);
	m_DownloadButn.ShowWindow(SW_SHOW);
	m_SreenShotButn.ShowWindow(SW_SHOW);
	m_SwitchListButn.ShowWindow(SW_SHOW);
	m_LastPlay.ShowWindow(SW_SHOW);
	m_NextPlay.ShowWindow(SW_SHOW);
	m_StopPlay.ShowWindow(SW_SHOW);
	return true;
}