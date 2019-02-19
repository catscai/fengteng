#include "stdafx.h"
#include "MyComDlg.h"
#include "0117MP4Dlg.h"
#include "Packdef.h"
#include "MyTools.h"

IMPLEMENT_DYNAMIC(CMyComDlg, CDialogEx)
CMyComDlg::CMyComDlg(CWnd* pParent /*= NULL*/)
{
	m_videoManager=NULL;
}
CMyComDlg::~CMyComDlg()
{
}
void CMyComDlg::DoDataExchange(CDataExchange* pDX)
{

	/*DDX_Control(pDX, IDC_LIST1, m_listName);*/
	DDX_Control(pDX, IDC_EDIT1, m_editVideoName);
	DDX_Control(pDX, IDC_LIST2, m_listReferVideo);
	//DDX_Control(pDX, IDC_LIST3, m_serachList);
	DDX_Control(pDX, IDC_LIST1, m_listName);
}
BEGIN_MESSAGE_MAP(CMyComDlg, CDialogEx)
	/*ON_NOTIFY_REFLECT(NM_RCLICK, &CMyComDlg::OnNMRClick)*/
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_BUTTON3, &CMyComDlg::OnBnClickedButton3)
	ON_EN_CHANGE(IDC_EDIT1, &CMyComDlg::OnEnChangeEdit1)
	//ON_NOTIFY(NM_DBLCLK,IDC_LIST1 ,&CMyComDlg::OnDblclkListData)
	ON_LBN_DBLCLK(IDC_LIST1, &CMyComDlg::OnLbnDblclkList1)
	ON_LBN_DBLCLK(IDC_LIST2, &CMyComDlg::OnLbnDblclkList2)
	ON_MESSAGE(MOVIEINFO_MEG,&CMyComDlg::OnMovieInfo)
	ON_MESSAGE(SERACH_MOVIENAME_MEG,&CMyComDlg::OnSerachMovieRs)
	ON_MESSAGE(SERACH_MOVIEINFO_MEG,&CMyComDlg::OnSerachMovieInfoRs)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BUTTON1, &CMyComDlg::OnBnClickedButton1)
	ON_COMMAND(ID_TTT_32779, &CMyComDlg::OnTttDownLoad)
	ON_STN_CLICKED(IDC_LOADMORE, &CMyComDlg::OnStnClickedLoadmore)
	ON_STN_CLICKED(IDC_CLEANLIST, &CMyComDlg::OnStnClickedCleanlist)
	ON_WM_SETFOCUS()
END_MESSAGE_MAP()

LRESULT CMyComDlg::OnSerachMovieInfoRs(WPARAM w, LPARAM l)
{
	SERACHMOVIERS*info=(SERACHMOVIERS*)w;
	CString movieName;
	WCHAR*wStr = CMyTools::EnCodeUtfToWCHAR(info->movieName);
	movieName=wStr;
	delete[] wStr;
	/*if(LB_ERR==m_listName.FindString(-1,movieName))
		m_listName.AddString(movieName);*/
	if(m_movieNameToLinkMap.find(movieName)==m_movieNameToLinkMap.end()){
		vector<string> vec;
		string videoType;
		if(info->VqType==VIDEOTYPE_MOVIE)
			videoType="movie";
		else
			videoType="tv";
		vec.push_back(videoType);
		for(int i=0;i<info->linksNum;i++)
		{
			string ss(info->links[i].link);
			vec.push_back(ss);
		}
		m_movieNameToLinkMap[movieName]=vec;
	}else if(LB_ERR==m_listReferVideo.FindString(-1,movieName)){
		vector<string> vec=m_movieNameToLinkMap[movieName];
		for(int i=0;i<info->linksNum;i++)
		{
			string ss(info->links[i].link);
			vec.push_back(ss);
		}
		m_movieNameToLinkMap[movieName]=vec;
	}
	string type=m_movieNameToLinkMap[movieName][0];
	if(strcmp(type.c_str(),"tv")==0){
		for(unsigned int i=1;i<m_movieNameToLinkMap[movieName].size();i++)
		{
			WCHAR ss[10]={0};_itow_s(i,ss,10);
			CString sortName(ss);
			sortName+=L"-"+movieName;
			if(m_nameToPathMap.find(sortName)!=m_nameToPathMap.end())
				break;
			m_listName.AddString(sortName);
			string sortlink=m_movieNameToLinkMap[movieName][i];
			char templink[MAX_MOVIE_LINK]={0};
			strcpy_s(templink,sortlink.c_str());
			WCHAR* wStr=CMyTools::EnCodeUtfToWCHAR(templink);
			CString wSortLink(wStr);
			delete[] wStr;
			m_nameToPathMap[sortName]=wSortLink;

		}
		//设置当前正在播放名字
		m_playingName=L"1-"+movieName;
	}else
	{//如果是电影类型的视频
		if(LB_ERR==m_listName.FindString(-1,movieName)){
			WCHAR* wLink = CMyTools::EnCodeUtfToWCHAR(info->links[0].link);
			CString movieLink(wLink);
			m_nameToPathMap[movieName] = movieLink;
			m_listName.AddString(movieName);
		}
	}
	UpdateData(FALSE);
	return 0;
}
LRESULT CMyComDlg::OnSerachMovieRs(WPARAM w, LPARAM l)
{
	SERACHRS*serachRs=(SERACHRS*)w;
	if(serachRs->realNum==0)
		return 0;
	CString movName;
	for(int i=0;i<serachRs->realNum;i++)
	{
		WCHAR*wStr=CMyTools::EnCodeUtfToWCHAR(serachRs->movieNames[i].movieName);
		movName=wStr;
		delete[] wStr;
		m_SerachDlg.m_SerachLst.AddString(movName);
	}
	//设置默认所选项 第一行
	m_SerachDlg.m_SerachLst.SetFocus();
	m_SerachDlg.UpdateData(FALSE);
	//m_SerachDlg.m_SerachLst.ShowWindow(SW_SHOW);
	return 0;
}
LRESULT CMyComDlg::OnMovieInfo(WPARAM w, LPARAM l)
{
	char*temp=(char*)w;
	MOVIEINFO*info=(MOVIEINFO*)temp;
	WCHAR *wStr=CMyTools::EnCodeUtfToWCHAR(info->movieName);
	CString movieName(wStr);
	delete[] wStr;
	++m_moviepos;
	if(LB_ERR==m_listReferVideo.FindString(-1,movieName)){
		m_listReferVideo.AddString(movieName);
		vector<string> vec;
		string videoType;
		if(info->VqType==VIDEOTYPE_MOVIE)
			videoType="movie";
		else
			videoType="tv";
		vec.push_back(videoType);
		for(int i=0;i<info->linksNum;i++)
		{
			string ss(info->links[i].link);
			vec.push_back(ss);
		}
		m_movieNameToLinkMap[movieName]=vec;
	}else{
		vector<string> vec=m_movieNameToLinkMap[movieName];
		for(int i=0;i<info->linksNum;i++)
		{
			string ss(info->links[i].link);
			vec.push_back(ss);
		}
		m_movieNameToLinkMap[movieName]=vec;
	}
	UpdateData(FALSE);
	return 0;
}
HBRUSH CMyComDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
	if(nCtlColor==CTLCOLOR_DLG)
	{
		return m_BrushBk;
	}
	if(GetDlgItem(IDC_LIST1)==pWnd||GetDlgItem(IDC_LIST2)==pWnd)
	{
		pDC->SetTextColor(RGB(255,255,255));
		pDC->SetBkColor(RGB(158,158,158));
		return m_BrushBk;
	}
	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}


BOOL CMyComDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_listReferVideo.SetHorizontalExtent(500);
	m_listName.SetHorizontalExtent(500);
	m_SerachDlg.Create(IDD_SERACH_DLG,this);
	//m_listName.m_SetConfigDlg.SetWindowPos(GetDlgItem(IDD_MYCOMDLG),-1,0,0,0,3);
	//m_listName.m_downTaskDlg.SetWindowPos(GetDlgItem(IDD_MYCOMDLG),-1,0,0,0,3);
	m_SerachDlg.SetWindowPos(GetDlgItem(IDD_MYCOMDLG),-1,0,0,0,3);
	m_BrushBk.CreateSolidBrush(RGB(158,158,158));
	m_videoPath=_T("");
	m_videoManager=theApp.getVideoManager();
	m_listName.SetPlayListComDlg(this);
	m_moviepos = 0;
	/*m_menu.LoadMenu(IDR_MENU1);*/
	return TRUE;  // return TRUE unless you set the focus to a control

}

void CMyComDlg::OnBnClickedButton3()
{
	// TODO: 在此添加控件通知处理程序代码
	TCHAR BASED_CODE szFilter[] = _T("Video Files All Files (*.*)|*.*||");
	 CFileDialog fileDlg (TRUE, _T("Video file"), _T(""), OFN_FILEMUSTEXIST, szFilter, this);
	 if(fileDlg.DoModal() == IDOK)
	 {
	  m_videoPath = fileDlg.GetPathName();
	 }
	 //m_editVideoName.SetWindowText(m_videoPath);
	 if(m_videoPath){
		 TCHAR* temp=(m_videoPath.GetBuffer(0)+m_videoPath.GetLength());
		 while(*temp!='\\'){
			if(temp==m_videoPath.GetBuffer(0)){
				temp--;
				break;
			}
			temp--;
		 }
		 temp++;
		 CString Name(temp);
		 //检验列表中是否已经存在该视频
		 if( LB_ERR == m_listName.FindString(-1,Name))
		{  
			m_listName.AddString(Name);
		 }
		 if(m_nameToPathMap[Name].IsEmpty()){
			 //添加到名字->路径map中
			 m_nameToPathMap[Name]=m_videoPath;
		 }
	 }
	 m_playingName=CMyTools::GetPlayingName(m_videoPath);
	 UpdateData(FALSE);
}

//当文本输入框内容发生改变时就会触发消息
void CMyComDlg::OnEnChangeEdit1()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
	// TODO:  在此添加控件通知处理程序代码
	//CString serachName;
	//m_editVideoName.GetWindowText(serachName);
	//if(serachName==_T(""))
	//	return;
	//SERACHRQ serachRq;
	//serachRq.RqType=SERACH_MOVIE_RQ;
	//char*temp=CMyTools::EnCodeWCHARToUtf(serachName.GetBuffer());
	//strcpy_s(serachRq.movieName,temp);
	//delete[] temp;
	//theApp.getUDPMediator()->SendData((char*)&serachRq,sizeof(serachRq));
	//CRect rect;
	//this->GetWindowRect(&rect);
	//m_SerachDlg.MoveWindow(rect.left+12,rect.top + 100,200,282);
	//m_SerachDlg.ShowWindow(SW_SHOWNOACTIVATE);
	//m_SerachDlg.SendMessage(WM_KILLFOCUS);
	//m_editVideoName.SetFocus();
}




void CMyComDlg::OnLbnDblclkList1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp=_T("");
	int nres=m_listName.GetCurSel();
	if(nres<0)
		return;
	m_listName.GetText(nres,temp);
	if(temp!=_T("")){
		m_videoPath=m_nameToPathMap[temp];
		CMy0117MP4Dlg* pMainWnd=NULL;
		pMainWnd=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
		if(m_videoPath==_T(""))
		{
			//如果电影映射中也没有
			if(m_movieNameToLinkMap.find(temp)==m_movieNameToLinkMap.end()){
				m_listName.SetCurSel(-1);
				AfxMessageBox(_T("视频已不存在"));
				m_listName.DeleteString(nres);
				UpdateData(FALSE);
				return;
			}
			char location[MAX_MOVIE_LINK]={0};
			strcpy_s(location,m_movieNameToLinkMap[temp][1].c_str());
			WCHAR*wStr=CMyTools::EnCodeUtfToWCHAR(location);
			CString videoLoc(wStr);
			delete[] wStr;
			m_videoPath=videoLoc;
		}
		//if(m_videoPath==)
		m_playingName=temp;
		//先停止当前视频
		pMainWnd->OnStnClickedStopBu();
		//改变为播放状态
		pMainWnd->m_isPlayBit=true;
		pMainWnd->OnStnClickedPlayBu();

	}
	//在每次选完视频之后 将鼠标光标移开
	m_listName.SetCurSel(-1);
}


void CMyComDlg::OnLbnDblclkList2()
{
	// TODO: 在此添加控件通知处理程序代码
	CString temp=_T("");
	int nres=m_listReferVideo.GetCurSel();
	if(nres<0)
		return;
	m_listReferVideo.GetText(nres,temp);
	CMy0117MP4Dlg* pMainWnd=NULL;
	pMainWnd=(CMy0117MP4Dlg*)theApp.m_pMainWnd;
	CString videoLoc;
	if(temp!=_T("")){
		if(m_movieNameToLinkMap.find(temp)==m_movieNameToLinkMap.end()){
				m_listName.SetCurSel(-1);
				AfxMessageBox(_T("视频已不存在"));
				m_listReferVideo.DeleteString(nres);
				UpdateData(FALSE);
				return;
			}
		if(m_nameToPathMap.find(temp)!=m_nameToPathMap.end())
		{
			m_videoPath=m_nameToPathMap[temp];
		}else{
			char link[MAX_MOVIE_LINK]={0};
			strcpy_s(link,m_movieNameToLinkMap[temp][1].c_str());
			WCHAR* wStr=CMyTools::EnCodeUtfToWCHAR(link);
			videoLoc=wStr;
			delete[] wStr;
			m_videoPath=videoLoc;
		}
		//如果播放的是电视剧则将每一集都添加到播放列表
		string type=m_movieNameToLinkMap[temp][0];
	if(strcmp(type.c_str(),"tv")==0){
		for(unsigned int i=1;i<m_movieNameToLinkMap[temp].size();i++)
		{
			WCHAR ss[10]={0};_itow_s(i,ss,10);
			CString sortName(ss);
			sortName+=L"-"+temp;
			if(m_nameToPathMap.find(sortName)!=m_nameToPathMap.end())
				break;
			m_listName.AddString(sortName);
			string sortlink=m_movieNameToLinkMap[temp][i];
			char templink[MAX_MOVIE_LINK]={0};
			strcpy_s(templink,sortlink.c_str());
			WCHAR* wStr=CMyTools::EnCodeUtfToWCHAR(templink);
			CString wSortLink(wStr);
			delete[] wStr;
			m_nameToPathMap[sortName]=wSortLink;

		}
		//设置当前正在播放名字
		m_playingName=L"1-"+temp;
	}else if(strcmp(type.c_str(),"movie")==0)
	{//如果是电影则将 电影名字添加到播放列表
		if(m_nameToPathMap.find(temp)==m_nameToPathMap.end())
		{
			m_listName.AddString(temp);
			m_nameToPathMap[temp]=videoLoc;
		}
		//将电影标志置为1
		pMainWnd->m_PlayNetVideoCount=1;
		////设置当前正在播放名字
		//m_playingName=temp;
	}
		////先停止当前视频
		//pMainWnd->OnStnClickedStopBu();
		////改变为播放状态
		//pMainWnd->m_isPlayBit=true;
		//pMainWnd->OnStnClickedPlayBu();
		
	}
	
	//在每次选完视频之后 将鼠标光标移开
	m_listReferVideo.SetCurSel(-1);
}


void CMyComDlg::OnDestroy()
{
	CDialogEx::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	/*map<CString,vector<string>*>::iterator ite=m_movieNameToLinkMap.begin();
	while(ite!=m_movieNameToLinkMap.end())
	{
		ite->second->clear();
		delete ite->second;
		ite->second=NULL;
		++ite;
	}*/
	m_BrushBk.DeleteObject();
	m_movieNameToLinkMap.clear();
}

//搜索视频
void CMyComDlg::OnBnClickedButton1()
{
	// TODO: 在此添加控件通知处理程序代码
	CString serachName;
	m_editVideoName.GetWindowText(serachName);
	if(serachName==_T(""))
		return;
	SERACHRQ serachRq;
	serachRq.RqType=SERACH_MOVIE_RQ;
	char*temp=CMyTools::EnCodeWCHARToUtf(serachName.GetBuffer());
	strcpy_s(serachRq.movieName,temp);
	delete[] temp;
	theApp.getUDPMediator()->SendData((char*)&serachRq,sizeof(serachRq));
	if(!m_SerachDlg.IsWindowVisible()){
		CRect rect;
		this->GetWindowRect(&rect);
		m_SerachDlg.MoveWindow(rect.left+12,rect.top + 100,200,282);
		m_SerachDlg.ShowWindow(SW_SHOWNOACTIVATE);
	}
}


void CMyComDlg::OnTttDownLoad()
{
	// TODO: 在此添加命令处理程序代码
}


BOOL CMyComDlg::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if(pMsg->hwnd != m_listName.GetSafeHwnd())
	{
		if(pMsg->message == WM_RBUTTONDOWN || pMsg->message == WM_RBUTTONUP)
			return TRUE;
	}
	if(pMsg->hwnd == m_editVideoName.GetSafeHwnd() && pMsg->message==WM_KEYUP && pMsg->wParam==VK_RETURN)
	{
		OnBnClickedButton1();
		return TRUE;
	}
	if(pMsg->message==WM_KEYDOWN && pMsg->wParam==VK_RETURN){
		//OnStnClickedPlayBu();
		return FALSE;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}


void CMyComDlg::OnStnClickedLoadmore()
{
	// TODO: 在此添加控件通知处理程序代码
	LOADMORE info;
	info.RqType = RQ_LOADMORE_MOVIES;
	info.moviepos = m_moviepos;
	theApp.getUDPMediator()->SendData((char*)&info,sizeof(LOADMORE));
}


void CMyComDlg::OnStnClickedCleanlist()
{
	// TODO: 在此添加控件通知处理程序代码
	int count=this->m_listName.GetCount();
	for(int i=count-1;i>=0;i--)
	{
		this->m_listName.DeleteString(i);
	}
	this->m_nameToPathMap.clear();
}


void CMyComDlg::OnSetFocus(CWnd* pOldWnd)
{
	CDialogEx::OnSetFocus(pOldWnd);

	// TODO: 在此处添加消息处理程序代码
	this->m_SerachDlg.m_SerachLst.ResetContent();
	this->m_SerachDlg.ShowWindow(SW_HIDE);
}
