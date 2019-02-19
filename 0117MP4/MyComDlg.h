#pragma once


// CMyComDlg 对话框
#include "afxcmn.h"
#include "afxwin.h"
#include "resource.h"
#include "0117MP4.h"
#include <map>
#include <string>
#include <vector>
#include "playlistbox.h"
#include "SerachDlg.h"
using namespace std;

class CMyComDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMyComDlg)

public:
	CMyComDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMyComDlg();

// 对话框数据
	enum { IDD = IDD_MYCOMDLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CBrush			m_BrushBk;	//背景画刷
	CListBox		m_listReferVideo;	//推荐列表
	VideoManager*	m_videoManager;
	CString			m_videoPath;	//当前播放路径
	CString			m_playingName;	//正在播放的视频名字
	CEdit			m_editVideoName;
	map<CString,CString>		m_nameToPathMap;
	map<CString,vector<string>> m_movieNameToLinkMap;	//名称对应链接
	CSerachDlg		m_SerachDlg;		//搜索窗口
	PlayListBox		m_listName;
	unsigned		m_moviepos;		//接受服务器推荐的视频数目
public:
	void PlayLocation(CString movieName);
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnLbnDblclkList1();
	afx_msg void OnLbnDblclkList2();
	afx_msg LRESULT OnMovieInfo(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSerachMovieRs(WPARAM w, LPARAM l);
	afx_msg LRESULT OnSerachMovieInfoRs(WPARAM w, LPARAM l);
	/*afx_msg void OnNMRClick(NMHDR *pNMHDR, LRESULT *pResult);*/
	afx_msg void OnDestroy();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnTttDownLoad();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnStnClickedLoadmore();
	afx_msg void OnStnClickedCleanlist();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
};
